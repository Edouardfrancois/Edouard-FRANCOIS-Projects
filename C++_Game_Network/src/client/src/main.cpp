/*
** EPITECH PROJECT, 2022
** client
** File description:
** main
*/

#include "GameManager.hpp"

int main(int ac, char *argv[])
{
    if (ac != 3)
        return 0;
    std::cerr << sizeof(unsigned short) << std::endl;
    GameManager gameManager(argv);
    gameManager.Run();
    // Networks::Client a(AF_INET, SOCK_DGRAM);
    //
    // a.ConnectServeur("127.0.0.1", 30000);
    // packet_t p;
    //
    // memset(&p, 0, sizeof(packet_t));
    // p.type = p.LOBBY_JOIN;
    // a.SendPacket<packet_t>(p);
    // while (1)
    // ;
    return 0;
}
