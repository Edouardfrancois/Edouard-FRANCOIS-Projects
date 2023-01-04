/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** ManageRegistry
*/

#ifndef MANAGEREGISTRY_HPP_
#define MANAGEREGISTRY_HPP_

#include <memory>

#include "components.hpp"
#include "PickUps.hpp"
#include "registry.hpp"
#include "FactoryMonster.hpp"
#include "Packet.hpp"
#include "ManageWall.hpp"


// typedef struct wall_s
// {
//     float pos_x;
//     float pos_y;
//     int size_x;
//     int size_y;
//     int hp;
// } wall_t;

class ManageRegistry {
    public:
        ManageRegistry();
        ~ManageRegistry();
        //packet_t AddMonster(__attribute__((unused)) registry &regis, __attribute__((unused)) const monster_t monster) {};
        packet_t AddMonster(registry &regis, const monster_t monster, int server);

        packet_t AddPickUps(registry &regis, int server);
        packet_t RmBullet(registry &regis, Entity bullet);

        packet_t AddWall(registry &regis, wall_t wall);
        // packet_t AddWall(registry &regis, int size_x, int size_y, int pos_x, int pos_y);
        // void AddMonsterInGame(registry &regis, const monster_t monster);
    protected:
    private:
};

#endif /* !MANAGEREGISTRY_HPP_ */