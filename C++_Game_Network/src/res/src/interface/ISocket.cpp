/*
** EPITECH PROJECT, 2022
** LibSocket
** File description:
** ISocket
*/

#include <unistd.h>
#include <fcntl.h>

#include "SocketExeption.hpp"
#include "ISocket.hpp"

/**
 * @brief Construct a new Networks:: I Socket:: I Socket object
 *
 * @param domain
 * @param type
 * @param protocol
 */
Networks::ISocket::ISocket(int domain, int type, int protocol)
{
    if ((this->_Socket = socket(domain, type, protocol)) == -1)
        throw SocketExeption::ISocketError();
}

/**
 * @brief Set a socket no blocking
 *
 */
void Networks::ISocket::_SetSocketNoBloking()
{
    int flags = fcntl(this->GetSocket(), F_GETFL, 0);

    if (flags == -1)
        throw SocketExeption::ISocketSetNoBlockingError();
    if (fcntl(this->GetSocket(), F_SETFL, flags | O_NONBLOCK) == -1)
        throw SocketExeption::ISocketSetNoBlockingError();
}

/**
 * @brief Destroy the Networks:: I Socket:: I Socket object
 *
 */
Networks::ISocket::~ISocket()
{
    close(this->_Socket);
}
