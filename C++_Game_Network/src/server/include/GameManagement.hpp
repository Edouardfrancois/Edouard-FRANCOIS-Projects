/*
** EPITECH PROJECT, 2022
** server
** File description:
** GameManagement
*/

#ifndef GAMEMANAGEMENT_HPP_
#define GAMEMANAGEMENT_HPP_

#include <memory>

#include "HandleUuid.hpp"
#include "HandleServer.hpp"
#include "ThreadPool.hpp"
#include "MainLobby.hpp"

class GameManagement
{
public:
    /**
     * @brief Construct a new Game Management object
     *
     */
    GameManagement();
    /**
     * @brief Destroy the Game Management object
     *
     */
    ~GameManagement();

protected:
private:
    std::shared_ptr<HandleUuid<packet_t>> _HandleUuid;
    std::shared_ptr<OneQueu<packet_t>> _MainLobbyQueue;
    std::unique_ptr<HandleServer> _HandleServ;
    std::unique_ptr<MainLobby> _MainLobby;
    ThreadPool _Pool;
};

#endif /* !GAMEMANAGEMENT_HPP_ */
