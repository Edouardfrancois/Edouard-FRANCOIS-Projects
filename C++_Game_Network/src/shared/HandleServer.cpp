/*
** EPITECH PROJECT, 2022
** server
** File description:
** HandleServer
*/

#include "HandleServer.hpp"
#include "Packet.hpp"

HandleServer::HandleServer() : _UdpServ(AF_INET, SOCK_DGRAM), _TcpServ()
{
}

void HandleServer::_DisplayInfoServer() const
{
    uint16_t port;
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);

    if (getsockname(this->_UdpServ.GetServeurSocket(), (struct sockaddr *)&sin, &len) == -1)
        return;
    port = htons(sin.sin_port);
    // if (getsockname(this->_TcpServ.GetServeurSocket(), (struct sockaddr *)&sin, &len) == -1)
    // return;
    // port = htons(sin.sin_port);
}

void HandleServer::_ConfiguServerUdp()
{
    try
    {
        this->_UdpServ.SetPortServeur(30000);
    }
    catch (const SocketExeption::PortChange &e)
    {
        std::string msg("[Warning] Port Udp Change 30000 -> ");
    }
}

void HandleServer::_ConfiguServerTcp()
{

    // try
    // {
    //     this->_TcpServ.SetPortServeur(30001);
    // }
    // catch (const SocketExeption::PortChange &e)
    // {
    //     std::string msg("[Warning] Port Tcp Change 30001 -> ");
    // }
}

void HandleServer::_SetOnApropiateQueu(std::weak_ptr<HandleUuid<packet_t>> &MyHandleUuid, packet_t &p, Networks::SocketEvent_u &e)
{
    const auto &HandleUuid = MyHandleUuid.lock();

    if (HandleUuid.get()->SetDataOnQueuByUsrUuid(p, p.senderUuid, e) == false)
    {
        printf("Connait pas\n");
    }
}

void HandleServer::RunClient(std::weak_ptr<utils::SafeQueue<packet_t>> Queu)
{
    packet_t P;
    Networks::SocketEvent_u e;

    try
    {
        _ConfiguServerUdp();
        _DisplayInfoServer();
    }
    catch (const SocketExeption::BindError &e)
    {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        return;
    }
    while (true)
    {
        try
        {
            P = this->_UdpServ.Select<packet_t>(e);
        }
        catch (const SocketExeption::SelectError &e)
        {
            std::cerr << "[Warning] " << e.what() << std::endl;
        }
        catch (const SocketExeption::ReadSocketError &e)
        {
            std::cerr << "[Warning] " << e.what() << std::endl;
        }
        Queu.lock().get()->add(P);
    }
}

int HandleServer::GetUdpServerSocket() const
{
    return this->_UdpServ.GetServeurSocket();
}

void HandleServer::RunServer(std::weak_ptr<HandleUuid<packet_t>> MyHandleUuid)
{
    packet_t P;
    Networks::SocketEvent_u e;

    try
    {
        _ConfiguServerUdp();
        _DisplayInfoServer();
    }
    catch (const SocketExeption::BindError &e)
    {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        return;
    }
    while (true)
    {
        try
        {
            P = this->_UdpServ.Select<packet_t>(e);
        }
        catch (const SocketExeption::SelectError &e)
        {
            std::cerr << "[Warning] " << e.what() << std::endl;
        }
        catch (const SocketExeption::ReadSocketError &e)
        {
            std::cerr << "[Warning] " << e.what() << std::endl;
        }
        _SetOnApropiateQueu(MyHandleUuid, P, e);
    }
}

HandleServer::~HandleServer()
{
}
