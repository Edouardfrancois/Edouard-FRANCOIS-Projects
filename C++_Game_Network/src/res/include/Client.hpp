/*
** EPITECH PROJECT, 2022
** res
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <string>

#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/un.h>

#include "ISocket.hpp"
#include "Select.hpp"

namespace Networks
{
    class Client : private ISocket, private Select
    {
    public:
        /**
         * @brief Construct a new Networks:: Client:: Client object
         *
         * @param domain
         * @param type
         * @param protocol
         */
        Client(int domain = AF_INET, int type = SOCK_STREAM, int protocol = 0);

        /**
         * @brief Destroy the Client object
         *
         */
        ~Client() = default;

        /**
         * @brief Connect to a remote server
         *
         * @param addr address
         * @param port port
         * @throw SocketExeption::ImpossibleToConnect
         */
        void ConnectServeur(const std::string addr, const int port);

        /**
         * @brief Connect to a intern server
         * @throw SocketExeption::ImpossibleToConnect
         *
         */
        void ConnectInternalServeur();

    private:
        /**
         * @brief Manage Evenement from server
         *
         * @return Networks::Select::_SocketEvent_t The evenement of the socket
         * @throw SocketExeption::SelectError Select Error
         */
        _SocketEvent_t _Select();

    private:
        /**
         * @brief Read a packet from server
         *
         * @tparam T type of the packet
         * @param e event from server
         * @throw SocketExeption::ReadSocketError
         * @throw SocketExeption::SocketCloseConnection
         */
        template <typename T>
        T _ReadPacket(const _SocketEvent_t &e)
        {
            T packet = {0};

            ssize_t ret = recv(e.Socket, &packet, sizeof(T), 0);
            if (ret == -1)
                throw SocketExeption::ReadSocketError();
            else if (ret == 0)
                throw SocketExeption::SocketCloseConnection();
            return packet;
        }

    public:
        /**
         * @brief Send a packet to the server
         *
         * @tparam PacketType
         * @param packet
         * @throw SocketExeption::SendError error during sending
         */
        template <typename PacketType>
        void SendPacket(const PacketType &packet)
        {
            if (this->_Udp)
            {
                if (sendto(GetSocket(), std::addressof(packet), sizeof(PacketType), 0, (const struct sockaddr *)&this->_AddrClient, sizeof(sockaddr_in)) == -1)
                    throw SocketExeption::SendError();
            }
            else if (send(GetSocket(), std::addressof(packet), sizeof(PacketType), 0) == -1)
                throw SocketExeption::SendError();
        }

        /**
         * @brief Lisen from server
         *
         * @tparam P packet type
         * @return P packet type
         */
        template <typename P>
        P Select()
        {
            P packet = {0};
            while (true)
            {
                _SocketEvent_t e = _Select();

                if (e.Event == S_EVENT_READ)
                {
                    return _ReadPacket<P>(e);
                }
            }
            return packet;
        }

    protected:
    private:
        bool _Udp = false;
        enum _ClientType
        {
            _CLIENTTYPE_IN,
            _CLIENTTYPE_UN,
        } _ClientType = _CLIENTTYPE_IN;
        union _AddrClient_u
        {
            struct sockaddr_in addrin;
            struct sockaddr_un addrun;
        } _AddrClient;
    };
};

#endif /* !CLIENT_HPP_ */
