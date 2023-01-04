/*
** EPITECH PROJECT, 2022
** server
** File description:
** MainLobby
*/

#ifndef MAINLOBBY_HPP_
#define MAINLOBBY_HPP_

#include <memory>

#include "HandleUuid.hpp"
#include "SendPacket.hpp"
#include "HandleServer.hpp"
#include "ThreadPool.hpp"
#include "SafeQueue.hpp"
#include "Lobby.hpp"

class MainLobby
{
public:
    /**
     * @brief Construct a new Main Lobby object
     *
     * @param MainLobbyQueue
     * @param HandleUuid
     * @param MainLobbyUuid
     */
    MainLobby(std::shared_ptr<OneQueu<packet_t>> &MainLobbyQueue, std::shared_ptr<HandleUuid<packet_t>> &HandleUuid, uuid_t &MainLobbyUuid);
    /**
     * @brief Destroy the Main Lobby object
     *
     */
    ~MainLobby();
    /**
     * @brief Get the Packet On Queue object
     *
     * @param queue
     * @return OnePacketQueue<packet_t>
     */
    static OnePacketQueue<packet_t> GetPacketOnQueue(std::shared_ptr<OneQueu<packet_t>> queue);

private:
    /**
     * @brief Get the packet on the main queue
     *
     * @return OnePacketQueue<packet_t>
     */
    OnePacketQueue<packet_t> _GetPacketOnQueueGoBackMain();
    // void _CreateOneLobby(const uuid_t &CreateUsrUuid, uuid_t &UuidOffLobby);
    bool _IsNewUser(OnePacketQueue<packet_t> &P) const;
    /**
     * @brief Handle New User
     *
     * @param P
     */
    void _HandleNewUser(OnePacketQueue<packet_t> &P);

private:
    /**
     * @brief Add a new user in the lobby
     *
     * @param P
     * @return true
     * @return false
     */
    bool _AddNewUsrToLobby(OnePacketQueue<packet_t> &P);
    /**
     * @brief Create A new Lobby
     *
     * @param P
     * @return true
     * @return false
     */
    bool _CreateOneLobby(OnePacketQueue<packet_t> &P);

public:
    /**
     * @brief Run the Main Lobby and manage when a lobby is destroyed
     *
     */
    void Run();

protected:
private:
    std::unordered_map<packet_t::type_e, std::function<bool(MainLobby &, OnePacketQueue<packet_t> &)>> _manage_message_from_server;
    std::vector<std::shared_ptr<Lobby>> _AllLobby;
    std::shared_ptr<HandleUuid<packet_t>> _HandleUuid;
    std::shared_ptr<OneQueu<packet_t>> _MainLobbyQueue;
    std::shared_ptr<SendPacket<packet_t>> _Send;
    std::shared_ptr<utils::SafeQueue<std::variant<Uuid, LobbyStop>>> _UsrGoBackMainLobby;
    uuid_t _MainLobbyUuid;
    ThreadPool _Pool;
};

#endif /* !MAINLOBBY_HPP_ */
