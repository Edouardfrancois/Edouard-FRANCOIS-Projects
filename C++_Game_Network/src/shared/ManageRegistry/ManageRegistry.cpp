/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** ManageRegistry
*/

#include <cstdlib>
#include "ManageRegistry.hpp"


ManageRegistry::ManageRegistry()
{
}

ManageRegistry::~ManageRegistry()
{
}

packet_t ManageRegistry::RmBullet(registry &regis, Entity bullet)
{
    packet_t packet = {};
    sparse_array<player_uuid_t> &uuid = regis.get_components<player_uuid_t>();


    packet.packet_type = packet_t::T_DESTROY_ENTITY;
    uuid_copy(packet.body_t.maby_miss.entity_uuid, uuid[bullet.get_size()]->uuid);
    regis.kill_entity(bullet);
    // std::cerr << "kill bullet\n";
    return packet;
}

packet_t ManageRegistry::AddWall(registry &regis, wall_t wall)
{
    Entity entity = regis.spawn_entity();
    player_uuid_t P = {};
    packet_t packet = {};
    uuid_t uuid;

    uuid_generate_random(uuid);
    uuid_copy(regis.emplace_component<player_uuid_t>(entity, P)->uuid, uuid);
    regis.add_component<position_t>(entity, {wall.pos_x, wall.pos_y});
    // regis.add_component<HP_t>(entity, {monster.life});
    regis.add_component<drawable_t>(entity, drawable_s(wall.size_x, COLOR_WALL, 3));
    regis.add_component<is_monster_t>(entity, {});
    regis.add_component<hit_box_t>(entity, {});
    regis.add_component<size_entity_t>(entity, {wall.size_x});
    regis.add_component<my_id_t>(entity, {entity_id_e::WALL});
    regis.add_component<is_wall_t>(entity, {});

    packet.packet_type = packet_t::T_CREATE_ENTITY;
    packet.body_t.create_entity.id = WALL;
    packet.body_t.create_entity.x = wall.pos_x;
    packet.body_t.create_entity.y = wall.pos_y;
    packet.body_t.create_entity.Degree = wall.size_x;
    uuid_copy(packet.body_t.create_entity.entity_uuid, uuid);
    return packet;

}

packet_t ManageRegistry::AddMonster(registry &regis, monster_t monster, int server)
{
    Entity entity = regis.spawn_entity();
    player_uuid_t P = {};
    packet_t packet = {};
    
    uuid_t uuid;
    uuid_generate_random(uuid);

    uuid_copy(regis.emplace_component<player_uuid_t>(entity, P)->uuid, uuid);
    regis.add_component<position_t>(entity, {monster.pos_x, monster.pos_y});

    regis.add_component<HP_t>(entity, {monster.life});
    regis.add_component<drawable_t>(entity, drawable_s(monster.size, COLOR_MOB_lv0, 50));
    regis.add_component<is_monster_t>(entity, {(monster.pos_y*2) + (rand() % (1080 - (monster.size*4)))});
    regis.add_component<hit_box_t>(entity, {});
    regis.add_component<size_entity_t>(entity, {monster.size});
    regis.add_component<my_id_t>(entity, {entity_id_e::MOB_lv0});
    regis.add_component<velocity_s>(entity, {VELOCITY_MOB_lv0});
    regis.add_component<update_to_client_t>(entity, {});
    regis.add_component<powerfull_t>(entity, {POWERFULL_HIT_MOB_lv0});
    // regis.add_component<


    packet.packet_type = packet_t::T_CREATE_ENTITY;
    packet.body_t.create_entity.id = MOB_lv0;
    packet.body_t.create_entity.x = monster.pos_x;
    packet.body_t.create_entity.y = monster.pos_y;
    uuid_copy(packet.body_t.create_entity.entity_uuid, uuid);
    return packet;
}

packet_t ManageRegistry::AddPickUps(registry &regis, int server)
{
    Entity entity = regis.spawn_entity();
    player_uuid_t P = {};
    packet_t packet = {};

    std::vector<PickUps::Effect> allowed_effect {
        PickUps::Effect::HP,
        PickUps::Effect::DMG,
        PickUps::Effect::WEAP,
    };
    std::vector<sf::Color> allowed_Color {
        sf::Color::Green,
        sf::Color::Magenta,
        sf::Color::Blue,
    };
    std::vector<int> allowed_shape {
        4,
        6,
        5,
    };
    std::vector<entity_id_e> allowed_id {
        entity_id_e::PICK_UPS_HP,
        entity_id_e::PICK_UPS_DMG,
        entity_id_e::PICK_UPS_WEAP,
    };

    srand(time(NULL));

    float x = rand() % 1920;
    float y = rand() % 1080;

    int type = rand() % 3;

    PickUps::Effect effect = allowed_effect[type];
    
    uuid_t uuid;
    uuid_generate_random(uuid);
    uuid_copy(regis.emplace_component<player_uuid_t>(entity, P)->uuid, uuid);
    
    regis.add_component<position_t>(entity, {x, y});
    regis.add_component<drawable_t>(entity, drawable_s(15, allowed_Color[type], allowed_shape[type]));
    regis.add_component<hit_box_t>(entity, {});
    //int id = entity_id_e::PICK_UPS_HP + type;
    regis.add_component<my_id_t>(entity, {allowed_id[type]});

    regis.emplace_component<PickUps::PickUps>(entity, effect);

    packet.packet_type = packet_t::T_CREATE_ENTITY;
    packet.body_t.create_entity.id = allowed_id[type];
    packet.body_t.create_entity.x = x;
    packet.body_t.create_entity.y = y;
    uuid_copy(packet.body_t.create_entity.entity_uuid, uuid);
    return packet;
}
