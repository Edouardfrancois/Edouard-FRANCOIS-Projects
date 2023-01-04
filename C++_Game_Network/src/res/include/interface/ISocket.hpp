/*
** EPITECH PROJECT, 2022
** LibSocket
** File description:
** ISocket
*/

#ifndef ISOCKET_HPP_
#define ISOCKET_HPP_

#include <sys/socket.h>

#include <cstdio>

namespace Networks
{
    class ISocket
    {
    public:
        ISocket(int domain = AF_INET, int type = SOCK_STREAM, int protocol = 0);
        int GetSocket() const { return this->_Socket; };
        ~ISocket();
    private:
        void _SetSocketNoBloking();
    private:
        int _Socket;
    };
};

#endif /* !ISOCKET_HPP_ */
