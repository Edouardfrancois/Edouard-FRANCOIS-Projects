/*
** EPITECH PROJECT, 2022
** server
** File description:
** GameManagement
*/

#include <unistd.h>
#include "GameManagement.hpp"

GameManagement::GameManagement() : _Pool(2, false, false)
{
    uuid_t MainLobbyUuid = {};
    size_t index = 0;

    std::memset(&MainLobbyUuid, 0, sizeof(uuid_t));
    this->_HandleServ = std::make_unique<HandleServer>();
    this->_HandleUuid = std::make_shared<HandleUuid<packet_t>>();
    this->_MainLobbyQueue = this->_HandleUuid.get()->CreateQueu(MainLobbyUuid, index);
    this->_MainLobby = std::make_unique<MainLobby>(this->_MainLobbyQueue, this->_HandleUuid, MainLobbyUuid);
    this->_Pool.attributeTasks(std::bind(&HandleServer::RunServer, this->_HandleServ.get(), this->_HandleUuid));
    this->_Pool.attributeTasks(std::bind(&MainLobby::Run, this->_MainLobby.get()));
}

GameManagement::~GameManagement()
{
    sleep(1);
}
