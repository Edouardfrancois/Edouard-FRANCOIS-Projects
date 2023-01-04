/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** FactoryMonster
*/


#include <iostream>
#include <cmath>
#include "FactoryMonster.hpp"


FactoryMonster::FactoryMonster(std::shared_ptr<OneQueu<packet_t>> &MyQueu, int SocketServer) : _MyQueu(MyQueu), _SocketServer(SocketServer)
{
    this->level = 1;
}

FactoryMonster::~FactoryMonster()
{
}

/**
 * @brief Use this function for generate a monster with the level of your choice
 * 
 * @param level = level of the monster you want to create
 * @param pos_x = position x of the monster you want to create
 * @param pos_y = position y of the monster you want to create
 * @return monster_t 
 */
monster_t FactoryMonster::Generate(size_t level, float pos_x, float pos_y)
{
    // float x = 1920 + (rand() % 1920);

    if ((int)level < 0 || level >= NB_lv_MONSTERS) {
        std::cerr << "you cannot generate a monster level = " << level << "!!!!\n";
        level = 0;
    }

    monster_t res = this->_array_monsters[level];
    res.pos_x = pos_x;
    res.pos_y = 500;
    res.ground = rand() % (1080 - (SIZE_MOB_lv0 * 2));
    res.entendue = fabs((rand() % (1080 - (SIZE_MOB_lv0 * 2))) - res.ground);
    res.life = (size_t)HP_BULLET;
    std::cerr << "entendue : " << res.entendue << std::endl;
    return res;
}

int FactoryMonster::count(registry &r)
{
    auto &sparse_array_id = r.get_components<my_id_t>();
    // auto &sparse_array_pos = r.get_components<position_t>();
    int res = 0;

    for (int i = 0; i < sparse_array_id.size(); i++) {
        if (sparse_array_id[i].has_value() && sparse_array_id[i]->id == MOB_lv0) {
            res += 1;
        }
    }
    // std::cerr << "nb_mob = " << res << std::endl;
    return res;
}

packet_t FactoryMonster::AddRandomMonsterInRegis(registry &r)
{
    Entity entity = r.spawn_entity();
    player_uuid_t P = {};
    packet_t packet = {};
    uuid_t uuid;

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    monster_t monster = this->Generate(1, float(900 + (rand() % (720 - (SIZE_MOB_lv0 * 2)))), 0);
    uuid_generate_random(uuid);
    uuid_copy(r.emplace_component<player_uuid_t>(entity, P)->uuid, uuid);
    float y = (float)monster.pos_y - float(SIZE_MOB_lv0 / 2);

    r.add_component<position_t>(entity, {(float)monster.pos_x, (float)monster.pos_y});
    r.add_component<HP_t>(entity, {monster.life});
    // r.add_component<drawable_t>(entity, drawable_s(monster.size, color, 50));
    r.add_component<is_monster_t>(entity, {monster.ground, monster.entendue});
    r.add_component<hit_box_t>(entity, {});
    r.add_component<size_entity_t>(entity, {(size_t)monster.size});
    r.add_component<my_id_t>(entity, {entity_id_e::MOB_lv0});
    r.add_component<velocity_s>(entity, {VELOCITY_MOB_lv0});
    r.add_component<update_to_client_t>(entity, {});
    r.add_component<powerfull_t>(entity, {POWERFULL_HIT_MOB_lv0});
    r.add_component<clock_for_updt_t>(entity, {start});

    packet.packet_type = packet_t::T_CREATE_ENTITY;
    packet.body_t.create_entity.id = MOB_lv0;
    packet.body_t.create_entity.x = monster.pos_x;
    packet.body_t.create_entity.y = y;
    packet.body_t.create_entity.Degree = SIZE_MOB_lv0;
    packet.body_t.create_entity.Velocity = HP_MOB_lv0;
    uuid_copy(packet.body_t.create_entity.entity_uuid, uuid);
    return packet;
}


// packet_t FactoryMonster::AddRandomBossInRegis(registry &r)
// {
//     Entity entity = r.spawn_entity();
//     player_uuid_t P = {};
//     packet_t packet = {};
//     uuid_t uuid;

//     std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
//     monster_t monster = {};
//     monster.pos_x = 2000;
//     monster.pos_y = 500;
//     monster.entendue = 200;
//     monster.ground = 900;
//     uuid_generate_random(uuid);
//     uuid_copy(r.emplace_component<player_uuid_t>(entity, P)->uuid, uuid);
//     float y = (float)monster.pos_y - float(SIZE_MOB_lv0 / 2);

//     r.add_component<position_t>(entity, {(float)monster.pos_x, });
//     r.add_component<HP_t>(entity, {monster.life});
//     // r.add_component<drawable_t>(entity, drawable_s(monster.size, color, 50));
//     r.add_component<is_monster_t>(entity, {monster.ground, monster.entendue});
//     r.add_component<hit_box_t>(entity, {});
//     r.add_component<size_entity_t>(entity, {(size_t)monster.size});
//     r.add_component<my_id_t>(entity, {entity_id_e::MOB_lv0});
//     r.add_component<velocity_s>(entity, {VELOCITY_MOB_lv0});
//     r.add_component<update_to_client_t>(entity, {});
//     r.add_component<powerfull_t>(entity, {POWERFULL_HIT_MOB_lv0});
//     r.add_component<clock_for_updt_t>(entity, {start});

//     packet.packet_type = packet_t::T_CREATE_ENTITY;
//     packet.body_t.create_entity.id = MOB_lv0;
//     packet.body_t.create_entity.x = monster.pos_x;
//     packet.body_t.create_entity.y = y;
//     uuid_copy(packet.body_t.create_entity.entity_uuid, uuid);
//     return packet;
// }

void FactoryMonster::update(registry &r)
{
    if (this->count(r) > 0)
        return ;
    this->level++;
    // std::cerr << level << "\n";
    std::cerr <<"add monster\n";
    if (level > 5) {
        packet_t packet = {};
        packet.packet_type = packet_t::T_END_GAME;
        packet.body_t.is_win.check = true;
        this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, packet);
        exit(9);
    }
    for (int i = 0; i < this->level; i++) {
        packet_t packet = this->AddRandomMonsterInRegis(r);
        this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, packet);
    }
}

void FactoryMonster::CreateBulletMonster(registry &r, position_t pos)
{
    Entity entity = r.spawn_entity();
        uuid_t uuid;
        player_uuid_t P = {};
        packet_t packet = {};

        r.add_component<my_id_t>(entity, {MOB_BULLET});
        r.add_component<position_t>(entity, {pos.x, pos.y});
        r.add_component<size_entity_t>(entity, {SIZE_MOB_BULLET});
        r.add_component<hit_box_t>(entity, {});
        r.add_component<HP_t>(entity, {HP_BULLET});
        r.add_component<powerfull_t>(entity, {POWERFULL_BULLET_MOB_lv0});
        r.add_component<update_to_client_t>(entity, {});
        uuid_generate_random(uuid);
        uuid_copy(r.emplace_component<player_uuid_t>(entity, P)->uuid, uuid);
        r.add_component<balle_t>(entity, {});
        r.add_component<velocity_t>(entity, {VELOCITY_BULLET_MOB});

        packet.packet_type = packet_t::T_CREATE_ENTITY;
        packet.body_t.create_entity.id = entity_id_e::MOB_BULLET;
        packet.body_t.create_entity.x = packet.body_t.create_entity.x;
        packet.body_t.create_entity.y = packet.body_t.create_entity.y;
        packet.body_t.create_entity.Velocity = VELOCITY_BULLET_MOB;
        packet.body_t.create_entity.life = HP_BULLET;
        packet.body_t.create_entity.Degree = SIZE_MOB_BULLET;
        uuid_copy(packet.body_t.create_entity.entity_uuid, uuid);
        this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, packet);
}