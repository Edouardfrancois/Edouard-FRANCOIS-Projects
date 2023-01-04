/*
** EPITECH PROJECT, 2022
** server
** File description:
** Lobby
*/

#ifndef LOBBY_HPP_
#define LOBBY_HPP_

#include <variant>

#include "HandleUuid.hpp"
#include "Packet.hpp"
#include "Game.hpp"
#include "EntityId.hpp"

struct LobbyStop
{
    /**
     * @brief Construct a new Lobby Stop object
     *
     * @param GiveLobby
     */
    LobbyStop(const uuid_t &GiveLobby)
    {
        uuid_copy(Lobby, GiveLobby);
    }
    uuid_t Lobby;
};

class Lobby
{
public:
    Lobby(std::shared_ptr<OneQueu<packet_t>> &_MyQueu, std::shared_ptr<SendPacket<packet_t>> &Send, std::shared_ptr<utils::SafeQueue<std::variant<Uuid, LobbyStop>>> &_UsrGoBackMainLobby, std::shared_ptr<std::condition_variable> Cv);

private:
    /**
     * @brief Init The Game
     *
     * @param P
     */
    void _InitGame(const OnePacketQueue<packet_t> &P);
    /**
     * @brief Destroy The Game
     *
     */
    void _DestroyGame();
    /**
     * @brief Start The Game
     *
     * @param P
     */
    void _StartGame(const OnePacketQueue<packet_t> &P);

public:
    /**
     * @brief Run The Lobby
     *
     */
    void Run();
    /**
     * @brief Destroy the Lobby object
     *
     */
    ~Lobby();

protected:
private:
    std::shared_ptr<utils::SafeQueue<std::variant<Uuid, LobbyStop>>> _UsrGoBackMainLobby;
    std::shared_ptr<std::condition_variable> _CvGobackMainLobby;
    std::shared_ptr<OneQueu<packet_t>> _MyQueu;
    std::unique_ptr<Game> _Game;
    std::shared_ptr<SendPacket<packet_t>> _Send;
    uuid_t _LobbyUuid;
};

#endif /* !LOBBY_HPP_ */
