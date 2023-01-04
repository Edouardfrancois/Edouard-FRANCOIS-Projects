/*
** EPITECH PROJECT, 2022
** server
** File description:
** SendPacket
*/

#ifndef SENDPACKET_HPP_
#define SENDPACKET_HPP_

#include <mutex>

#include "HandleUuid.hpp"

#if __APPLE__
#define MSG_CONFIRM 0
#endif

template <typename DataType>
class SendPacket
{
public:
    /**
     * @brief Construct a new Send Packet object
     *
     */
    SendPacket(){};
    /**
     * @brief Construct a new Send Packet object
     *
     * @param Socket Socket of the server
     * @param AddrServeur addr of the server
     * @param Port port th send
     */
    SendPacket(const int Socket, const std::string &&AddrServeur, const int Port) : _Socket(Socket)
    {
        this->_AddrServer.sin_family = AF_INET;
        this->_AddrServer.sin_addr.s_addr = inet_addr(AddrServeur.c_str());
        this->_AddrServer.sin_port = htons(Port);
    }
    /**
     * @brief Destroy the Send Packet object
     *
     */
    ~SendPacket() = default;

    /**
     * @brief Change the port
     *
     * @param NewPort
     */
    void ChangePort(const int NewPort)
    {
        this->_M_mutex.lock();
        this->_AddrServer.sin_port = htons(NewPort);
        this->_M_mutex.unlock();
    }

    /**
     * @brief Send a paket to the Socket registered
     *
     * @param P
     */
    void SendTo(DataType &P)
    {
        this->_M_mutex.lock();
        if (sendto(this->_Socket, &P, sizeof(DataType), MSG_CONFIRM, (const struct sockaddr *)&this->_AddrServer, sizeof(struct sockaddr_in)) == -1)
        {
            this->_M_mutex.unlock();
            throw SocketExeption::SendError();
        }
        this->_M_mutex.unlock();
    }

    /**
     * @brief Send a paket to the SocketServ
     *
     * @param SocketServ
     * @param P
     */
    void SendNoMutex(int SocketServ, sockaddr_in &Addr, DataType &P)
    {
        if (sendto(SocketServ, &P, sizeof(DataType), MSG_CONFIRM, (const struct sockaddr *)&Addr, sizeof(struct sockaddr_in)) == -1)
        {
            throw SocketExeption::SendError();
        }
    }

    /**
     * @brief Send a packet using OnePacketQueue object
     *
     * @param P
     */
    void SendTo(const OnePacketQueue<DataType> &P)
    {
        this->_M_mutex.lock();
        if (sendto(P.e.Socket, &P.Data, sizeof(DataType), MSG_CONFIRM, (const struct sockaddr *)&P.e.addrclient, sizeof(struct sockaddr_in)) == -1)
        {
            this->_M_mutex.unlock();
            throw SocketExeption::SendError();
        }
        this->_M_mutex.unlock();
    }

    /**
     * @brief Send a packet using OnePacketQueue object but not using mutex
     *

     *
     * @param P
     */
    void SendToNoMutex(const OnePacketQueue<DataType> &P)
    {
        if (sendto(P.e.Socket, &P.Data, sizeof(DataType), MSG_CONFIRM, (const struct sockaddr *)&P.e.addrclient, sizeof(struct sockaddr_in)) == -1)
        {
            throw SocketExeption::SendError();
        }
        this->_M_mutex.unlock();
    }

    /**
     * @brief Send the packet util it is send (no mutex)
     *
     * @param P
     */
    void SendToHandleErrorNoMutex(const OnePacketQueue<DataType> &P)
    {
        while (true)
        {
            try
            {
                SendToNoMutex(P);
            }
            catch (const SocketExeption::SendError &e)
            {
                continue;
            }
            break;
        }
    }

    /**
     * @brief Send the packet util it is send
     *
     * @param P
     */
    void SendToHandleError(const OnePacketQueue<DataType> &P)
    {
        while (true)
        {
            try
            {
                SendTo(P);
            }
            catch (const SocketExeption::SendError &e)
            {
                continue;
            }
            break;
        }
    }

private:
    std::mutex _M_mutex;
    int _Socket;
    struct sockaddr_in _AddrServer;
};

#endif /* !SENDPACKET_HPP_ */
