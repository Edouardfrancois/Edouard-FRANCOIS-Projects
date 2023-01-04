/*
** EPITECH PROJECT, 2022
** client
** File description:
** Lobby
*/

#include "Lobby.hpp"
#include "MyDisplay.hpp"
#include "buttonFunc.hpp"

#include <memory>

void LobbyPacket::ConnectToServer(std::shared_ptr<SendPacket<packet_t>> &Send)
{
    packet_t P = {};
    P.packet_type = packet_t::T_CONNECTION;
    Send.get()->SendTo(P);
}

/* **************************************************************************** */

void Lobby::_RegisterHandlersNetworkFunc()
{
    this->_manage_message_from_server.insert({packet_t::type_e::T_CONNECTION, &Lobby::_HandleConnection});
    this->_manage_message_from_server.insert({packet_t::type_e::T_ERROR, &Lobby::_ErrorFromServer});
    this->_manage_message_from_server.insert({packet_t::type_e::T_ERROR_P_LOBBY_ALL_READY_EXIST, &Lobby::_ErrorLoddyAllReadyExists});
    this->_manage_message_from_server.insert({packet_t::type_e::T_ERROR_P_CANT_JOIN_THIS_LOBBY, &Lobby::_ErrorJoinLobby});
    this->_manage_message_from_server.insert({packet_t::type_e::T_ERROR_P_LOBBY_DON_T_EXIST, &Lobby::_ErrorJoinLobby});
    this->_manage_message_from_server.insert({packet_t::type_e::T_ERROR_P_LOBBY_FULL, &Lobby::_ErrorJoinLobby});
    this->_manage_message_from_server.insert({packet_t::type_e::P_CREATE_LOBBY, &Lobby::_HandleLobbyCreate});
    this->_manage_message_from_server.insert({packet_t::type_e::P_USR_JOIN, &Lobby::_HandleLobbyJoin});
    this->_manage_message_from_server.insert({packet_t::type_e::P_JOIN_SUCESS, &Lobby::_HandleLobbyJoin});
    this->_manage_message_from_server.insert({packet_t::type_e::P_LEAVE_LOBBY, &Lobby::_HandleDeconnectLobby});
    this->_manage_message_from_server.insert({packet_t::type_e::P_USR_LEAVE_LOBBY, &Lobby::_HandleUsrLeaveLobby});
    this->_manage_message_from_server.insert({packet_t::type_e::P_LODDY_DESTRY, &Lobby::_HandleLobbyDestroy});
    this->_manage_message_from_server.insert({packet_t::type_e::T_BEGIN_GAME, &Lobby::_BeginGame});
}

Lobby::Lobby(std::shared_ptr<SendPacket<packet_t>> &Send) : _Send(Send)
{
    _RegisterHandlersNetworkFunc();
}

void Lobby::Run(bool &in_looby, MyDisplay &disp, uuid_t &my_uuid)
{
    if (this->_State == BEING_GAME)
    {
        in_looby = true;
        uuid_copy(my_uuid, _UuidClient);
    }
    // affichage des objets du menu (buttons/port setter...)
    //  those lines don't work. c:
    // std::cout << "hello" << std::endl;
    // disp.ite(this->_Regis);
}

void init()
{
}

/* **************************************************************************** */

void Lobby::_ErrorJoinLobby(const packet_t &P)
{
    std::cerr << "[Error]: Imposible to Join " << P.body_t.list_lobby.lobby_uuid << "." << std::endl;
}

void Lobby::_ErrorFromServer(__attribute__((__unused__)) const packet_t &P)
{
    std::cerr << "[Error]: Unexpected error from the server." << std::endl;
}

void Lobby::_ErrorLoddyAllReadyExists(const packet_t &P)
{
    std::cerr << "[Error]: Lobby " << P.body_t.list_lobby.lobby_uuid << " all ready exists." << std::endl;
}

/* **************************************************************************** */

void Lobby::_BeginGame(const packet_t &P)
{
    this->_State = BEING_GAME;
    std::cerr << "[Info]: Begin Game" << std::endl;
}

void Lobby::_HandleUsrLeaveLobby(const packet_t &P)
{
    this->_UsrInLobby.erase(std::remove_if(
                                this->_UsrInLobby.begin(), this->_UsrInLobby.end(),
                                [&](const UsrInLobby &x)
                                {
                                    if (uuid_compare(P.body_t.lobby_disconned_usr.usruuid, x.uuid_of_user) == 0)
                                        return true;
                                    else
                                        return false;
                                }),
                            this->_UsrInLobby.end());
    std::cout << "[Info]: Usr Leave Lobby" << std::endl;
}

void Lobby::_HandleLobbyDestroy(const packet_t &P)
{
    this->_LobbyFromServer.erase(std::remove_if(
                                     this->_LobbyFromServer.begin(), this->_LobbyFromServer.end(),
                                     [&](const LobbyFromServer_s &x)
                                     {
                                         if (uuid_compare(P.body_t.lobby_destroy.lobby_uuid, x.uuid_of_lobby) == 0)
                                             return true;
                                         else
                                             return false;
                                     }),
                                 this->_LobbyFromServer.end());
    std::cout << "[Info]: Lobby Destroy" << std::endl;
    {
        char UuidNewLobby[37] = {};
        uuid_unparse(P.body_t.lobby_destroy.lobby_uuid, UuidNewLobby);
    }
}

void Lobby::_HandleDeconnectLobby(const packet_t &P)
{
    uuid_copy(this->_MyCurrentLobbyId, P.lobbyUuid);
    this->_LobbyFromServer.clear();
    this->_UsrInLobby.clear();

    std::cout << "[Info]: Go back to Main Lobby" << std::endl;
}

void Lobby::_HandleLobbyJoin(const packet_t &P)
{
    if (P.packet_type == packet_t::P_USR_JOIN)
    {
        this->_UsrInLobby.push_back(UsrInLobby(P.body_t.lobby_new_usr.usruuid));
        {
            char UuidNewLobby[37] = {};
            uuid_unparse(P.body_t.lobby_new_usr.usruuid, UuidNewLobby);
            std::cout << "[Info]: Usr Join the lobby: " << UuidNewLobby << ". Index: " << P.body_t.lobby_new_usr.index << "." << std::endl;
        }
    }
    else
    {
        uuid_copy(this->_MyCurrentLobbyId, P.lobbyUuid);
        {
            char UuidNewLobby[37] = {};
            uuid_unparse(P.lobbyUuid, UuidNewLobby);
            std::cout << "[Info]: Join Lobby: " << UuidNewLobby << ". Index: " << P.body_t.list_lobby.index << "." << std::endl;
        }
    }
}

void Lobby::_HandleLobbyCreate(const packet_t &P)
{
    for (const auto &I : this->_LobbyFromServer)
    {
        if (uuid_compare(P.body_t.list_lobby.lobby_uuid, I.uuid_of_lobby) == 0)
            return;
    }
    struct LobbyFromServer_s NewLobby = {};
    uuid_copy(NewLobby.uuid_of_lobby, P.body_t.list_lobby.lobby_uuid);
    NewLobby.index = P.body_t.list_lobby.index;
    this->_LobbyFromServer.push_back(NewLobby);
    {
        char UuidNewLobby[37] = {};
        uuid_unparse(P.body_t.list_lobby.lobby_uuid, UuidNewLobby);
        std::cout << "[Info]: New Lobby: " << UuidNewLobby << ". Index: " << P.body_t.list_lobby.index << "." << std::endl;
    }
}

void Lobby::_HandleConnection(const packet_t &P)
{
    uuid_t EmptyUuid = {};

    if (uuid_compare(EmptyUuid, P.senderUuid) == 0)
    {
        std::cerr << "[Warning]: Imposible to connect." << std::endl;
        this->_State = CONNECTIO_REFUSED;
        return;
    }
    std::cout << "[Info]: Connect to the server." << std::endl;
    uuid_copy(this->_UuidClient, P.senderUuid);
    {
        char UuidStr[37] = {};
        uuid_unparse(this->_UuidClient, UuidStr);
        std::cout << "[Info]: UUID: " << UuidStr << std::endl;
    }
    this->_State = MAIN_LOBBY;
}

void Lobby::ManagePacket(const packet_t &Packet)
{
    try
    {
        this->_manage_message_from_server[Packet.packet_type](*this, Packet);
    }
    catch (const std::bad_function_call &e)
    {
        std::cerr << "[Warning]: Not Reconize Packet Type: " << Packet.packet_type << "." << std::endl;
    }
}

Lobby::~Lobby()
{
}
