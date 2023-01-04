/*
** EPITECH PROJECT, 2022
** client
** File description:
** Lobby
*/

#ifndef LOBBY_HPP_
#define LOBBY_HPP_

#include "registry.hpp"
#include "MyDisplay.hpp"
#include "Packet.hpp"

struct LobbyFromServer_s
{
    LobbyFromServer_s(){};
    LobbyFromServer_s(const uuid_t &ToCopy)
    {
        uuid_copy(this->uuid_of_lobby, ToCopy);
    }
    union
    {
        uuid_t uuid_of_lobby;
        uuid_t uuid_of_user;
    };
    u_short index;
};

using UsrInLobby = LobbyFromServer_s;

class LobbyPacket
{
public:
    LobbyPacket(){};
    ~LobbyPacket() = default;
    /**
     * @brief Send a packet Connection to the server
     *
     * @param Send
     */
    void ConnectToServer(std::shared_ptr<SendPacket<packet_t>> &Send);
};

class Lobby
{
public:
    /**
     * @brief Register All Network Function
     *
     */
    void _RegisterHandlersNetworkFunc();
    /**
     * @brief Construct a new Lobby object
     *
     * @param Send
     */
    Lobby(std::shared_ptr<SendPacket<packet_t>> &Send);
    /**
     * @brief Destroy the Lobby object
     *
     */
    ~Lobby();
    /**
     * @brief Run 1 time the lobby
     *
     * @param in_looby if true le lobby stop and game start
     * @param disp display struct
     * @param my_uuid uuid of the player
     */
    void Run(bool &in_looby, MyDisplay &disp, uuid_t &my_uuid);
    /**
     * @brief init lobby entity
     *
     */
    void init();

private:
    /**
     * @brief Handle When Begin the Game
     *
     * @param P
     */
    void _BeginGame(const packet_t &P);
    /**
     * @brief Erro When Want Join A lobby
     *
     */
    void _ErrorJoinLobby(const packet_t &P);
    /**
     * @brief Unexpected error from the server
     *
     */
    void _ErrorFromServer(const packet_t &P);

    /**
     * @brief Lobby all ready exist
     *
     * @param P
     */
    void _ErrorLoddyAllReadyExists(const packet_t &P);

private:
    /**
     * @brief Handle when a usr leave current lobby
     *
     * @param P
     */
    void _HandleUsrLeaveLobby(const packet_t &P);
    /**
     * @brief Handle when a lobby is destroyed
     *
     * @param P
     */
    void _HandleLobbyDestroy(const packet_t &P);
    /**
     * @brief Handle when you leave a lobby
     *
     * @param P
     */
    void _HandleDeconnectLobby(const packet_t &P);
    /**
     * @brief Handle when you join a lobby
     *
     * @param P
     */
    void _HandleLobbyJoin(const packet_t &P);
    /**
     * @brief Handle when a lobby is create
     *
     * @param P
     */
    void _HandleLobbyCreate(const packet_t &P);

    /**
     * @brief Handle connection packet
     *
     * @param P
     */
    void _HandleConnection(const packet_t &P);

public:
    /**
     * @brief If a packet is received this function is called
     *
     * @param Packet the packet from the server
     */
    void ManagePacket(const packet_t &Packet);

protected:
private:
    registry _Regis;
    std::shared_ptr<SendPacket<packet_t>> _Send;
    std::unordered_map<packet_t::type_e, std::function<void(Lobby &, const packet_t &)>> _manage_message_from_server;
    enum State
    {
        NOT_CONNECTED,
        HASK_FOR_CONNECTION,
        MAIN_LOBBY,
        CONNECTIO_REFUSED,
        BEING_GAME,
    } _State;
    std::vector<LobbyFromServer_s> _LobbyFromServer;
    std::vector<UsrInLobby> _UsrInLobby;
    LobbyPacket _PacketGenerator;
    uuid_t _UuidClient;
    uuid_t _MyCurrentLobbyId;
};

#endif /* !LOBBY_HPP_ */
