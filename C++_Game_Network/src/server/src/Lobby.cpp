/*
** EPITECH PROJECT, 2022
** server
** File description:
** Lobby
*/

#include <cstdio>

#include "MainLobby.hpp"
#include "Lobby.hpp"

Lobby::Lobby(std::shared_ptr<OneQueu<packet_t>> &MyQueu, std::shared_ptr<SendPacket<packet_t>> &Send, std::shared_ptr<utils::SafeQueue<std::variant<Uuid, LobbyStop>>> &UsrGoBackMainLobby, std::shared_ptr<std::condition_variable> Cv) : _UsrGoBackMainLobby(UsrGoBackMainLobby), _CvGobackMainLobby(Cv), _MyQueu(MyQueu), _Send(Send)
{
    uuid_copy(this->_LobbyUuid, MyQueu.get()->GetUuidOfLobby());
}

void Lobby::_InitGame(const OnePacketQueue<packet_t> &P)
{
    this->_Game = std::make_unique<Game>(this->_MyQueu, P, this->_LobbyUuid);
}

void Lobby::_DestroyGame()
{
    this->_Game.reset();
}

void Lobby::_StartGame(const OnePacketQueue<packet_t> &P)
{
    packet_t PacketBeginGame = {};
    uuid_copy(PacketBeginGame.lobbyUuid, this->_LobbyUuid);
    PacketBeginGame.packet_type = packet_t::T_BEGIN_GAME;
    PacketBeginGame.body_t.screen_size.x = 1500;
    PacketBeginGame.body_t.screen_size.y = 900;
    this->_MyQueu.get()->SendPacketToAllUsr(P.e.Socket, PacketBeginGame);
    _InitGame(P);
    this->_Game.get()->Run();
}

void DisplayUuid(uuid_t &toDisplay)
{
    char str[37] = {};
    uuid_unparse_lower(toDisplay, str);
    std::cerr << "[DEBUG] Diplsay: " << str << " Run." << std::endl;
}

void Lobby::Run()
{
    {
        char struuidLobby[37] = {};
        uuid_unparse_lower(this->_LobbyUuid, struuidLobby);
        std::cerr << "[Info] Lobby: " << struuidLobby << " Run." << std::endl;
    }
    while (1)
    {
        OnePacketQueue<packet_t> P = MainLobby::GetPacketOnQueue(this->_MyQueu);
        std::printf("In Lobby!\n");
        if (P.Data.packet_type == packet_t::T_CONNECTION)
        {
            uuid_copy(P.Data.lobbyUuid, this->_LobbyUuid);
            this->_Send.get()->SendToHandleErrorNoMutex(P);
            continue;
        }
        else if (P.Data.packet_type == packet_t::T_BEGIN_GAME)
        {
            _StartGame(P);
            break;
        }
        else if (P.Data.packet_type == packet_t::P_LEAVE_LOBBY)
        {
            std::memset(&P.Data.lobbyUuid, 0, sizeof(uuid_t));
            this->_Send.get()->SendTo(P);
            std::variant<Uuid, LobbyStop> UsrGoBackMainLobby(this->_MyQueu.get()->GetUuidByUuidT(P.Data.senderUuid));
            this->_UsrGoBackMainLobby.get()->add(UsrGoBackMainLobby);
            this->_MyQueu.get()->RemouveThatUsrFromThisQueue(P.Data.senderUuid);
            this->_CvGobackMainLobby.get()->notify_one();
            if (this->_MyQueu.get()->GetNumberOfUsr() == 0)
                break;
            {
                packet_t UsrDeconnect = {};
                UsrDeconnect.packet_type = packet_t::P_USR_LEAVE_LOBBY;
                uuid_copy(UsrDeconnect.body_t.lobby_disconned_usr.usruuid, P.Data.senderUuid);
                this->_MyQueu.get()->SendPacketToAllUsr(P.e.Socket, UsrDeconnect);
            }
        }
    }
    _DestroyGame();
    this->_MyQueu.get()->DesactiveQueue();
    std::variant<Uuid, LobbyStop> StopToQueue(LobbyStop(this->_LobbyUuid));
    this->_UsrGoBackMainLobby.get()->add(StopToQueue);
    {
        char struuidLobby[37] = {};
        uuid_unparse_lower(this->_LobbyUuid, struuidLobby);
        std::cerr << "[Info] Lobby: " << struuidLobby << " Stop." << std::endl;
    }
}

Lobby::~Lobby()
{
}
