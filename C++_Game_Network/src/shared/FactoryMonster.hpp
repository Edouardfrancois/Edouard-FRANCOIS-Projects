/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** FactoryMonster
*/

#include <stdint.h>

#include "registry.hpp"
#include "components.hpp"
#include "HandleUuid.hpp"
#include "Packet.hpp"

#ifndef FACTORYMONSTER_HPP_
#define FACTORYMONSTER_HPP_

__attribute__((unused)) static size_t NB_lv_MONSTERS = 5;

typedef struct monster_s {
    // monster_s(size_t Life, int Size, unsigned short PosX, 
    // unsigned short PosY, size_t lv) : this->life(Life)
    size_t life;
    int size;
    unsigned short pos_x;
    unsigned short pos_y;
    size_t lv;
    float ground;
    float entendue;
} monster_t;

class FactoryMonster {
    public:
        FactoryMonster(std::shared_ptr<OneQueu<packet_t>> &MyQueu, int SocketServer);
        ~FactoryMonster();
        monster_t Generate(size_t level, float pos_x, float pos_y);
        void update(registry &r);
        int count(registry &r);
        packet_t AddRandomMonsterInRegis(registry &r);
        void CreateBulletMonster(registry &r, position_t pos);

    protected:
    private:
        std::shared_ptr<OneQueu<packet_t>> _MyQueu;
        int _SocketServer;
        monster_t _array_monsters[5] = {{10, 80, 0, 0, 0}, {30, 100, 0, 0, 1}, {60, 120, 0, 0, 3}, {100, 150, 0, 0, 4}, {150, 150, 0, 0, 5}};
        int level;
};

#endif /* !FACTORYMONSTER_HPP_ */
