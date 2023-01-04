/*
** EPITECH PROJECT, 2022
** server
** File description:
** MainLobby
*/

#include "MainLobby.hpp"

MainLobby::MainLobby(std::shared_ptr<OneQueu<packet_t>> &MainLobbyQueue, std::shared_ptr<HandleUuid<packet_t>> &HandleUuid, uuid_t &MainLobbyUuid) : _HandleUuid(HandleUuid), _MainLobbyQueue(MainLobbyQueue), _Pool(5, true, false)
{

    this->_Send = std::make_shared<SendPacket<packet_t>>();
    this->_UsrGoBackMainLobby = std::make_shared<utils::SafeQueue<std::variant<Uuid, LobbyStop>>>();
    uuid_copy(this->_MainLobbyUuid, MainLobbyUuid);

    this->_manage_message_from_server.insert({packet_t::type_e::P_CREATE_LOBBY, &MainLobby::_CreateOneLobby});
    this->_manage_message_from_server.insert({packet_t::type_e::P_JOIN_LOBBY, &MainLobby::_AddNewUsrToLobby});
}

OnePacketQueue<packet_t> MainLobby::GetPacketOnQueue(std::shared_ptr<OneQueu<packet_t>> queue)
{
    OnePacketQueue<packet_t> P;

    std::unique_lock<std::mutex> lk(queue.get()->MutexCv);
    queue.get()->Cv.get()->wait(lk, [&, queue]
                                { return (!queue.get()->IsQueueEmpty()); });
    queue.get()->GetOnQueu(P);
    lk.unlock();
    return P;
}

OnePacketQueue<packet_t> MainLobby::_GetPacketOnQueueGoBackMain()
{
    OnePacketQueue<packet_t> P;

    std::unique_lock<std::mutex> lk(this->_MainLobbyQueue.get()->MutexCv);
    this->_MainLobbyQueue.get()->Cv.get()->wait(lk, [&, this]
                                                { return (!this->_MainLobbyQueue.get()->IsQueueEmpty() or !this->_UsrGoBackMainLobby.get()->is_empty()); });
    if (!this->_MainLobbyQueue.get()->IsQueueEmpty())
        this->_MainLobbyQueue.get()->GetOnQueu(P);
    lk.unlock();
    return P;
}

bool MainLobby::_IsNewUser(OnePacketQueue<packet_t> &P) const
{
    return (this->_MainLobbyQueue.get()->IsUuidInThisQueue(P.Data.senderUuid, P.e.addrclient) == 0);
}

void MainLobby::_HandleNewUser(OnePacketQueue<packet_t> &P)
{
    uuid_t new_uuid;

    this->_MainLobbyQueue.get()->GenerateNewUuidUsr(new_uuid, P.e.addrclient);
    {
        uuid_copy(P.Data.senderUuid, new_uuid);
        this->_Send.get()->SendToHandleError(P);
    }
    std::vector<std::pair<Uuid, size_t>> AllActivateLobby = this->_HandleUuid.get()->GetAllUuidActivateLobby();
    packet_t NewLobby = {};
    NewLobby.packet_type = packet_t::P_CREATE_LOBBY;
    for (const auto &I : AllActivateLobby)
    {
        uuid_copy(NewLobby.body_t.list_lobby.lobby_uuid, I.first.uuid);
        NewLobby.body_t.list_lobby.index = I.second;
        this->_Send.get()->SendNoMutex(P.e.Socket, P.e.addrclient, NewLobby);
    }
    // {
    // if (this->_HandleUuid.get()->GetNumberActiveQueue() == 1)
    // _CreateOneLobby(P);
    // uuid_copy(P.Data.senderUuid, new_uuid);
    // _AddNewUsrToLobby(P);
    // }
}

bool MainLobby::_AddNewUsrToLobby(OnePacketQueue<packet_t> &P)
{
    uuid_t LobbyUuid = {};
    char StrUsrUuid[37] = {};
    char StrLoobyUuid[37] = {};

    if (uuid_compare(LobbyUuid, P.Data.body_t.list_lobby.lobby_uuid) == 0)
    {
        {
            uuid_unparse_lower(P.Data.senderUuid, StrUsrUuid);
            uuid_unparse_lower(P.Data.body_t.list_lobby.lobby_uuid, StrLoobyUuid);
            std::cout << "[Warning] " << StrUsrUuid << " Can't connect to " << StrLoobyUuid << " Reson: Want to join main lobby." << std::endl;
        }
        P.Data.packet_type = packet_t::T_ERROR_P_CANT_JOIN_THIS_LOBBY;
        this->_Send.get()->SendToHandleError(P);
        return true;
    }
    uuid_copy(LobbyUuid, P.Data.body_t.list_lobby.lobby_uuid);
    int NbPlayINThisLobby = this->_HandleUuid.get()->GetNumberUuidInThisQueu(LobbyUuid);
    {
        if (NbPlayINThisLobby == -1)
        {
            {
                uuid_unparse_lower(P.Data.senderUuid, StrUsrUuid);
                uuid_unparse_lower(P.Data.body_t.list_lobby.lobby_uuid, StrLoobyUuid);
                std::cout << "[Warning] " << StrUsrUuid << " Can't connect to " << StrLoobyUuid << " Reson: Lobby Don't Exist." << std::endl;
            }
            P.Data.packet_type = packet_t::T_ERROR_P_LOBBY_DON_T_EXIST;
            this->_Send.get()->SendToHandleError(P);
            return true;
        }
        else if (NbPlayINThisLobby == 4)
        {
            P.Data.packet_type = packet_t::T_ERR0R_LOBBY_FULL;
            this->_Send.get()->SendToHandleError(P);
            uuid_unparse_lower(P.Data.senderUuid, StrUsrUuid);
            uuid_unparse_lower(LobbyUuid, StrLoobyUuid);
            std::cout << "[Warning] " << StrUsrUuid << " Can't connect to " << StrLoobyUuid << " Reson: Lobby Full" << std::endl;
            P.Data.packet_type = packet_t::T_ERROR_P_LOBBY_FULL;
            this->_Send.get()->SendToHandleError(P);
            return true;
        }
        this->_MainLobbyQueue.get()->RemouveThatUsrFromThisQueue(P.Data.senderUuid);
        {
            packet_t NewUsrInThisLobby = {};
            NewUsrInThisLobby.packet_type = packet_t::P_USR_JOIN;
            uuid_copy(NewUsrInThisLobby.body_t.lobby_new_usr.usruuid, P.Data.senderUuid);
            NewUsrInThisLobby.body_t.lobby_new_usr.index = NbPlayINThisLobby;
            this->_HandleUuid.get()->SendPacketToAllUserLobby(P.e.Socket, LobbyUuid, NewUsrInThisLobby);
        }
    }
    P.Data.packet_type = packet_t::P_JOIN_SUCESS;
    uuid_copy(P.Data.lobbyUuid, LobbyUuid);
    P.Data.body_t.lobby_new_usr.index = NbPlayINThisLobby;
    this->_Send.get()->SendToHandleError(P);
    std::pair<std::mutex *, std::vector<Uuid> *> AllUsr = this->_HandleUuid.get()->GetAllUrsByThread(LobbyUuid);
    AllUsr.first->lock();
    {
        u_short index = 0;
        packet_t SayLocalUsr = {};
        SayLocalUsr.packet_type = packet_t::P_USR_JOIN;
        for (auto I = AllUsr.second->begin(); I != AllUsr.second->end(); ++I)
        {
            SayLocalUsr.body_t.lobby_new_usr.index = index;
            uuid_copy(SayLocalUsr.body_t.lobby_new_usr.usruuid, I.base()->uuid);
            this->_Send.get()->SendNoMutex(P.e.Socket, P.e.addrclient, SayLocalUsr);
        }
    }
    this->_HandleUuid.get()->AddThisUsrToThatUuidQueuLobby(LobbyUuid, P.Data.senderUuid, P.e.addrclient, false);
    AllUsr.first->unlock();
    return true;
}

bool MainLobby::_CreateOneLobby(OnePacketQueue<packet_t> &P)
{
    uuid_t uuidLobby = {};
    size_t index = 0;

    if ((this->_HandleUuid.get()->GetNumberActiveQueue() - 1) == 2)
    {
        P.Data.packet_type = packet_t::T_ERROR_P_MAX_LOBBY;
        this->_Send.get()->SendToHandleError(P);
        return true;
    }
    uuid_copy(uuidLobby, P.Data.body_t.list_lobby.lobby_uuid);
    std::shared_ptr<OneQueu<packet_t>> Queu;
    try
    {
        Queu = this->_HandleUuid.get()->CreateQueu(uuidLobby, index);
    }
    catch (std::runtime_error &e)
    {
        {
            char struuidUsr[37] = {};
            char struuidLobby[37] = {};
            uuid_unparse_lower(P.Data.senderUuid, struuidUsr);
            uuid_unparse_lower(uuidLobby, struuidLobby);
            std::cout << "[Waring] " << struuidLobby << " can't Create: " << struuidUsr << " All ready exist." << std::endl;
        }
        {
            P.Data.packet_type = packet_t::T_ERROR_P_LOBBY_ALL_READY_EXIST;
            this->_Send.get()->SendToHandleError(P);
        }
        return true;
    }

    if (index > this->_AllLobby.size())
    {
        std::shared_ptr<Lobby> NewLobby = std::make_shared<Lobby>(Queu, this->_Send, this->_UsrGoBackMainLobby, this->_MainLobbyQueue.get()->Cv);
        this->_AllLobby.push_back(NewLobby);
        this->_Pool.attributeTasks(std::bind(&Lobby::Run, NewLobby.get()));
    }
    else
    {
        this->_Pool.attributeTasks(std::bind(&Lobby::Run, this->_AllLobby.at(index - 1).get()));
    }
    {
        char struuidUsr[37] = {};
        char struuidLobby[37] = {};
        uuid_unparse_lower(P.Data.senderUuid, struuidUsr);
        uuid_unparse_lower(uuidLobby, struuidLobby);
        std::cout << "[Info] New Lobby: " << struuidLobby << " Create by: " << struuidUsr << "." << std::endl;
    }
    packet_t CreateLoobyPacket = {};
    CreateLoobyPacket.packet_type = packet_t::P_CREATE_LOBBY;
    CreateLoobyPacket.body_t.list_lobby.index = index - 1;
    uuid_copy(CreateLoobyPacket.body_t.list_lobby.lobby_uuid, uuidLobby);
    this->_MainLobbyQueue.get()->SendPacketToAllUsr(P.e.Socket, CreateLoobyPacket);
    uuid_copy(P.Data.lobbyUuid, uuidLobby);
    _AddNewUsrToLobby(P);
    return true;
}

void MainLobby::Run()
{
    char StrLobbyUuid[37] = {};
    uuid_unparse_lower(this->_MainLobbyUuid, StrLobbyUuid);

    while (1)
    {
        OnePacketQueue<packet_t> P = _GetPacketOnQueueGoBackMain();
        if (!this->_UsrGoBackMainLobby.get()->is_empty())
        {
            std::variant<Uuid, LobbyStop> UsrGoBackMainLobbyOrLobbyDestroy;
            Uuid *UsrGoBackMenue;
            this->_UsrGoBackMainLobby.get()->try_pop(UsrGoBackMainLobbyOrLobbyDestroy);
            if ((UsrGoBackMenue = std::get_if<Uuid>(&UsrGoBackMainLobbyOrLobbyDestroy)))
            {
                this->_HandleUuid.get()->AddThisUsrToThatUuidQueuLobby(this->_MainLobbyUuid, UsrGoBackMenue->uuid, UsrGoBackMenue->sockaddr, true);
                {
                    std::vector<std::pair<Uuid, size_t>> AllActivateLobby = this->_HandleUuid.get()->GetAllUuidActivateLobby();
                    packet_t NewLobby = {};
                    NewLobby.packet_type = packet_t::P_CREATE_LOBBY;
                    for (const auto &I : AllActivateLobby)
                    {
                        uuid_copy(NewLobby.body_t.list_lobby.lobby_uuid, I.first.uuid);
                        NewLobby.body_t.list_lobby.index = I.second;
                        this->_Send.get()->SendNoMutex(P.e.Socket, UsrGoBackMenue->sockaddr, NewLobby);
                    }
                }
            }
            else
            {
                LobbyStop S = std::get<LobbyStop>(UsrGoBackMainLobbyOrLobbyDestroy);
                packet_t LobbyDestroy = {};
                LobbyDestroy.packet_type = packet_t::P_LODDY_DESTRY;
                uuid_copy(LobbyDestroy.body_t.lobby_destroy.lobby_uuid, S.Lobby);
                this->_MainLobbyQueue.get()->SendPacketToAllUsr(P.e.Socket, LobbyDestroy);
            }
            continue;
        }
        else if (P.Data.packet_type == packet_t::P_LEAVE_LOBBY)
        {
            P.Data.packet_type = packet_t::T_ERROR;
            this->_Send.get()->SendToHandleError(P);
            continue;
        }
        // if (P.Data.packet_type != packet_t::T_CONNECTION)
        // {
        //     P.Data.packet_type = packet_t::T_ERROR;
        //     std::cout << "[Warning] " << StrLobbyUuid << " not Reconize Packet Type: " << P.Data.packet_type << std::endl;
        //     this->_Send.get()->SendToHandleError(P);
        //     continue;
        // }
        else if (_IsNewUser(P))
        {
            _HandleNewUser(P);
            continue;
        }
        else if (P.Data.packet_type >= packet_t::P_CREATE_LOBBY)
        {
            this->_manage_message_from_server[P.Data.packet_type](*this, P);
        }
        else
        {
            P.Data.packet_type = packet_t::T_ERROR;
            this->_Send.get()->SendTo(P);
        }

        // _AddNewUsrToLobby(P);
    }
}

MainLobby::~MainLobby()
{
}
