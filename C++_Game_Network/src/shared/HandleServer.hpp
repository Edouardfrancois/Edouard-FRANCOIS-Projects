/*
** EPITECH PROJECT, 2022
** server
** File description:
** HandleServer
*/

#ifndef HANDLESERVER_HPP_
#define HANDLESERVER_HPP_

#include <thread>
#include <memory>

#include "Packet.hpp"
#include "Serveur.hpp"
#include "HandleUuid.hpp"

class HandleServer
{
public:
    /**
     * @brief Construct a new Handle Server object
     *
     */
    HandleServer();
    /**
     * @brief Destroy the Handle Server object
     *
     */
    ~HandleServer();

private:
    /**
     * @brief Display port number when connected
     *
     */
    void _DisplayInfoServer() const;
    /**
     * @brief Start the server in Udp mode
     *
     */
    void _ConfiguServerUdp();
    /**
     * @brief Start the server in Tcp mode
     *
     */
    void _ConfiguServerTcp();
    /**
     * @brief set the packet on Apropiate Queue
     *
     * @param MyHandleUuid
     * @param p packet
     * @param e
     */
    void _SetOnApropiateQueu(std::weak_ptr<HandleUuid<packet_t>> &MyHandleUuid, packet_t &p, Networks::SocketEvent_u &e);

public:
    /**
     * @brief Get the Udp Server Socket object
     *
     * @return int
     */
    int GetUdpServerSocket() const;
    /**
     * @brief Run Server
     *
     * @param MyHandleUuid
     */
    void RunServer(std::weak_ptr<HandleUuid<packet_t>> MyHandleUuid);
    /**
     * @brief Run Client
     *
     * @param Queu
     */
    void RunClient(std::weak_ptr<utils::SafeQueue<packet_t>> Queu);

protected:
private:
    Networks::Serveur _UdpServ;
    Networks::Serveur _TcpServ;
};

#endif /* !HANDLESERVER_HPP_ */
