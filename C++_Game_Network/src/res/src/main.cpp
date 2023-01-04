/*
** EPITECH PROJECT, 2022
** LibSocket
** File description:
** main
*/

#include <unistd.h>
#include <thread>
#include <mutex>
#include <queue>

#include "SocketExeption.hpp"

#include "Serveur.hpp"
#include "Client.hpp"
// #include "packet.hpp"

// void networkThread(std::queue<int> &q)
// {
// }

// void serv()
// {
//     std::queue<int> q;
//     std::thread NetworkThread = std::thread(networkThread, q);
//     NetworkThread.join();
// }

// int main(int ac, __attribute__((__unused__)) char *av[])
// {
//     if (ac == 1)
//         serv();
// }

typedef struct Packet_s
{
    int nadia;
} Packet_t;

int main(int ac, __attribute__((__unused__)) char *av[])
{
    if (ac == 1)
    {
        Networks::Serveur a(AF_INET, SOCK_DGRAM);

        try
        {
            a.SetPortServeur(30000);
        }
        catch (SocketExeption::PortChange &e)
        {
            std::cout << e.what() << std::endl;
        }
        while (1)
        {
            Networks::SocketEvent_u e;
            Packet_t z = a.Select<Packet_t>(e);
            // printf("%d\n", e.Event);
            // printf("%d\n", e.Socket);
            // printf("%s\n", inet_ntoa(e.addrclient.sin_addr));
            // printf("%d\n", e.addrclient.sin_family);
            printf("%d\n", e.addrclient.sin_port);
            // printf("\"%hhn\"\n", e.addrclient.sin_zero);
            // printf("%d\n", z.nadia);
        }
    }
    else
    {
        Networks::Client c(AF_INET, SOCK_DGRAM);
        Packet_t p = {4};
        try
        {
            c.ConnectServeur("127.0.0.1", 30000);
            while (1)
            {
                c.SendPacket<Packet_t>(p);
                sleep(1);
            }
        }
        catch (SocketExeption::PortChange &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    // try {
    // a.SetPortServeur(22);
    // } catch (const SocketExeption::BindError& e) {
    // printf("%s\n", e.what());
    // }
}
