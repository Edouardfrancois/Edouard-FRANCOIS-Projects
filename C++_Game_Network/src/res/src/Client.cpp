/*
** EPITECH PROJECT, 2022
** res
** File description:
** Client
*/

#include "SocketExeption.hpp"
#include "Client.hpp"

Networks::Client::Client(int domain, int type, int protocol) : ISocket(domain, type, protocol), Networks::Select(GetSocket())
{
    if (type == SOCK_DGRAM)
        this->_Udp = true;
}

void Networks::Client::ConnectServeur(const std::string addr, const int port)
{
    this->_AddrClient.addrin.sin_addr.s_addr = inet_addr(addr.c_str());
    this->_AddrClient.addrin.sin_family = AF_INET;
    this->_AddrClient.addrin.sin_port = htons(port);
    if (this->_Udp)
        return;
    if (connect(GetSocket(), (const struct sockaddr *)&this->_AddrClient.addrin, sizeof(struct sockaddr_in)) == -1)
        throw SocketExeption::ImpossibleToConnect();
}

void Networks::Client::ConnectInternalServeur()
{
    this->_AddrClient.addrun.sun_family = AF_UNIX;
    strcpy(this->_AddrClient.addrun.sun_path, "Intern.serv");
    this->_ClientType = _CLIENTTYPE_UN;
    if (this->_Udp)
        return;
    if (connect(GetSocket(), (const struct sockaddr *)&this->_AddrClient.addrun, sizeof(struct sockaddr_un)) == -1)
        throw SocketExeption::ImpossibleToConnect();
}

Networks::Select::_SocketEvent_t Networks::Client::_Select()
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
    case S_EVENT_READ:
        return Event;
    default:
        break;
    }
    return Event;
}
