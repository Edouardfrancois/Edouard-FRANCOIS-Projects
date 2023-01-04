/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran [WSL : Ubuntu-20.04]
** File description:
** createEntity
*/

#include <uuid/uuid.h>

#include "registry.hpp"
#include "components.hpp"

// Entity createPlayer(const uuid_t &uuid, const unsigned short x, const unsigned short y, registry &r)
// {
//     Entity e = r.spawn_entity();
//     player_uuid_t P = {};

//     std::cerr << "SERVER ADD ONE PLAYERS ON HIS REGISTRE" << std::endl;
//     r.add_component<position_t>(e, {(float)x, (float)y});
//     r.add_component<move_t>(e, {0, 0});
//     r.add_component<my_id_t>(e, {entity_id_e::PLAYER});
//     uuid_copy(r.emplace_component<player_uuid_t>(e, P)->uuid, uuid);
//     r.add_component<hit_box_t>(e, {});
//     r.add_component<size_entity_t>(e, {40});
//     r.add_component<HP_t>(e, {HP_PLAYER});
//     return e;
// }