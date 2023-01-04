/*
** EPITECH PROJECT, 2022
** LibSocket
** File description:
** Serveur
*/

#ifndef SERVEUR_HPP_
#define SERVEUR_HPP_

#include <string>

#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/un.h>

#include "SocketExeption.hpp"
#include "ISocket.hpp"
#include "Select.hpp"

namespace Networks
{
    class Serveur : private ISocket, private Select
    {
    public:
        /**
         * @brief Construct a new Serveur object
         *
         * @param domain
         * @param type
         * @param protocol
         */
        Serveur(int domain = AF_INET, int type = SOCK_STREAM, int protocol = 0);

        /**
         * @brief Destroy the Serveur object
         *
         */
        ~Serveur();

        /**
         * @brief Bing the serveur to a specific port
         * @e if the port is allready used, the port will be automatically change to port + 1
         * @throw SocketExeption::PortProtected Impossible to bind to this port
         * @throw SocketExeption::BindError impossible to bind to this port
         * @throw  SocketExeption::PortChange the port was change
         * @param port the port
         */
        void SetPortServeur(int port);

        /**
         * @brief Set a intern machine server
         *
         * @throw SocketExeption::BindError impossible to bind to this port
         */
        void SetInternServeur();

    private:
        /**
         * @brief Lisen SocketExeption::ImpossibleToBind Imposible to bind
         *
         * @throw
         */
        void _Listen();

        /**
         * @brief Handle a new connection
         *
         */
        void _HandelNewConnection();

        /**
         * @brief Manage Event from client
         *
         * @return Networks::Select::_SocketEvent_t The evenement of the socket
         * @throw SocketExeption::SelectError
         */
        _SocketEvent_t _Select();

    public:
        /**
         * @brief Get the Socket of the server
         *
         * @return int
         */
        int GetServeurSocket() const
        {
            return this->GetSocket();
        }

    private:
        /**
         * @brief Read a Packet to the server
         *
         * @tparam PacketType
         * @param packet
         * @throw SocketExeption::ReadSocketError Imposible to read
         * @throw SocketCloseConnection the client disconnect
         */
        template <typename T>
        T _ReadPacket(const _SocketEvent_t &e)
        {
            T packet;
            ssize_t ret;

            if (this->_Udp)
            {
                socklen_t len = sizeof(struct sockaddr_in);
                ret = recvfrom(e.Socket, &packet, sizeof(T), MSG_WAITALL, (struct sockaddr *)&e.addrclient, &len);
            }
            else
                ret = recv(e.Socket, &packet, sizeof(T), 0);
            if (ret == -1)
                throw SocketExeption::ReadSocketError();
            else if (ret == 0)
                throw SocketExeption::SocketCloseConnection();
            return packet;
        }

    public:
        /**
         * @brief Send a packet to a client
         *
         * @tparam PacketType
         * @param socket
         * @param packet
         * @throw SocketExeption::SendError Error during sending
         */
        template <typename PacketType>
        void SendPacket(const int socket, const PacketType &packet)
        {
            if (send(socket, std::addressof(packet), sizeof(PacketType), 0) == -1)
                throw SocketExeption::SendError();
        }

        /**
         * @brief Manage packet from the client
         *
         * @tparam P the packet type
         * @param e Networks::SocketEvent_u
         * @return P the packet
         */
        template <typename P>
        P Select(Networks::SocketEvent_u &e)
        {
            P packet;
            while (true)
            {
                e = _Select();

                if (e.Event == S_EVENT_READ)
                {
                    try
                    {
                        return _ReadPacket<P>(e);
                    }
                    catch (const SocketExeption::SocketCloseConnection &err)
                    {
                        _RemoveSocket(e.Socket, GetSocket());
                        e.Event = S_EVENT_CLOSE;
                        return {};
                    }
                }
                else if (e.Event == S_EVENT_NEW_CONNECTION)
                    return {};
            }
            return packet;
        }

    private:
        bool _Udp = false;
        enum _ServeurType
        {
            _SERVTYPE_IN,
            _SERVTYPE_UN,
        } _ServType = _SERVTYPE_IN;
        union _AddrServ_u
        {
            struct sockaddr_in addrin;
            struct sockaddr_un addrun;
        } _AddrServ;
    };
}

#include <iostream>

#endif /* !SERVEUR_HPP_ */
