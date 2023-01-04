/*
** EPITECH PROJECT, 2022
** LibSocket
** File description:
** Serveur
*/

#include <cstdio>
#include <unistd.h>
#include <algorithm>

#include "SocketExeption.hpp"
#include "Serveur.hpp"

Networks::Serveur::Serveur(int domain, int type, int protocol) : ISocket(domain, type, protocol), Networks::Select(GetSocket())
{
    if (type == SOCK_DGRAM)
        this->_Udp = true;
}

void Networks::Serveur::SetPortServeur(int port)
{
    bool _PortChange = false;

    memset(&this->_AddrServ, 0, sizeof(_AddrServ_u));
    errno = 0;
    this->_AddrServ.addrin.sin_family = AF_INET;
    this->_AddrServ.addrin.sin_addr.s_addr = INADDR_ANY;
    for (; port != 60000; ++port)
    {
        this->_AddrServ.addrin.sin_port = htons(port);
        if (bind(GetSocket(), (const struct sockaddr *)(&this->_AddrServ.addrin), sizeof(this->_AddrServ.addrin)) == 0)
            break;
        switch (errno)
        {
        case EACCES:
            throw SocketExeption::PortProtected();
        case EADDRINUSE:
            _PortChange = true;
            continue;
        default:
            throw SocketExeption::BindError();
        }
    }
    if (!this->_Udp)
        _Listen();
    if (_PortChange)
        throw SocketExeption::PortChange(port);
}

void Networks::Serveur::SetInternServeur()
{
    this->_AddrServ.addrun.sun_family = AF_UNIX;
    strcpy(this->_AddrServ.addrun.sun_path, "Intern.serv");
    if (bind(this->GetSocket(), (struct sockaddr *)&this->_AddrServ.addrun, SUN_LEN(&this->_AddrServ.addrun)) == -1)
        throw SocketExeption::BindError();
    this->_ServType = _SERVTYPE_UN;
    if (!this->_Udp)
        _Listen();
}

void Networks::Serveur::_Listen()
{
    if (!this->_Udp && listen(GetSocket(), SOMAXCONN) == -1)
        throw SocketExeption::ImpossibleToBind();
}

void Networks::Serveur::_HandelNewConnection()
{
    struct sockaddr_in addrclient;
    socklen_t len = sizeof(struct sockaddr_in);
    int clientfd = accept(GetSocket(),
                          (struct sockaddr *)&addrclient, &len);

    _SetSocket(clientfd);
}

Networks::Select::_SocketEvent_t Networks::Serveur::_Select()
{
    _ResetSelectData();
    int retSelect = select(_GetNbFds() + 1, _GetSelectRead(), /*_GetSelectWrite()*/ NULL, NULL, NULL);
    if (retSelect == -1)
        throw SocketExeption::SelectError();
    if (this->_Udp == true)
        return {S_EVENT_READ, _GetNbFds(), {0, 0, 0, 0}};
    _SocketEvent_t Event = _GetSocketEvent(GetSocket());
    switch (Event.Event)
    {
    case S_EVENT_NEW_CONNECTION:
        _HandelNewConnection();
        break;
    case S_EVENT_READ:
        return Event;
    default:
        break;
    }
    return Event;
}

/**
 * @brief Destroy the Networks:: Serveur:: Serveur object
 *
 */
Networks::Serveur::~Serveur()
{
    if (this->_ServType == _SERVTYPE_UN)
        unlink(this->_AddrServ.addrun.sun_path);
}
