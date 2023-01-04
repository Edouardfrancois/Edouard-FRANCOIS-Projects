/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** ManageMessageFromServer
*/

#include <iostream>
#include "Packet.hpp"

#include "GameManager.hpp"
#include "Weapon.hpp"
#include "components.hpp"
#include "registry.hpp"
#include "EntityId.hpp"

void GameManager::msg_from_server_error_impossible_to_stop_move(packet_t packet, __attribute__((unused)) uuid_t uuid)
{
    std::cerr << packet.packet_type << "\n";
}

void GameManager::msg_from_server_error_impossible_to_move(packet_t packet, __attribute__((unused)) uuid_t uuid)
{
    std::cerr << packet.packet_type << "\n";
}

void GameManager::msg_from_server_error_impossible_to_create_entity(packet_t packet, __attribute__((unused)) uuid_t uuid)
{
    std::cerr << packet.packet_type << "\n";
}

void GameManager::msg_from_server_error_unknow_entity(packet_t packet, __attribute__((unused)) uuid_t uuid)
{
    std::cerr << packet.packet_type << "\n";
}

void GameManager::msg_from_server_error_lobby_full(packet_t packet, __attribute__((unused)) uuid_t uuid)
{
}

void GameManager::msg_from_server_error(packet_t packet, __attribute__((unused)) uuid_t uuid)
{
}

void GameManager::msg_from_server_connection(packet_t packet, __attribute__((unused)) uuid_t uuid)
{
}

void GameManager::msg_from_server_begin_game(packet_t packet, __attribute__((unused)) uuid_t uuid)
{
}

/**
 * @brief this function is call when client receive T_CREATE_ENTITY from the serveur,
 * This function create an new entity in the registry from "create_entity" struct wich is in the packet
 *
 * @param packet the packet sent by the serveur
 * @param r the registry = the "array" that contain all our entity
 * @param uuid is the uuid of the client that receive this packet
 */
void GameManager::msg_from_server_create_entity(packet_t packet, uuid_t uuid)
{
    // std::cout << "CREATE ENTITY\n";
    Entity n1 = _regis.spawn_entity();

    player_uuid_t P = {};
    uuid_copy(_regis.emplace_component<player_uuid_t>(n1, P)->uuid, packet.body_t.create_entity.entity_uuid);
    _regis.add_component<position_t>(n1, {packet.body_t.create_entity.x, packet.body_t.create_entity.y});

    if (packet.body_t.create_entity.id == PLAYER)
    {
        _regis.add_component<HP_t>(n1, {HP_PLAYER});
        if (!uuid_compare(uuid, packet.body_t.create_entity.entity_uuid))
        {

            _regis.add_component<shoot::Weapon>(n1, shoot::Weapon(shoot::FireMOD::Single, entity_id_e::PLAYER_BULLET, VELOCITY_BULLET_PLAYER));
            // _regis.add_component<sprite_t>(n1, sprite_t{this->_envAsset, "assets/images/ship.png"});
            _regis.add_component<hit_box_t>(n1, {});
            _regis.add_component<controllable_t>(n1, {});
            _regis.add_component<my_id_t>(n1, {PLAYER});
            _regis.add_component<size_entity_t>(n1, {40});
            _regis.add_component<drawable_t>(n1, drawable_s(40, {200, 10, 13, 200}, 100));
            _regis.add_component<sprite_t>(n1, sprite_s(this->envAsset, "assets/images/VaiseauxEpitech.png"));
            _regis.get_components<sprite_t>()[n1.get_size()]->sprite.setScale((sf::Vector2f){0.1, 0.1});
        }
        else
        {
            _regis.add_component<shoot::Weapon>(n1, shoot::Weapon(shoot::FireMOD::Single, entity_id_e::PLAYER_BULLET, VELOCITY_BULLET_PLAYER));

            _regis.add_component<my_id_t>(n1, {PLAYER});
            _regis.add_component<hit_box_t>(n1, {});
            _regis.add_component<size_entity_t>(n1, {40});
            _regis.add_component<drawable_t>(n1, drawable_s(40, {10, 200, 13, 200}, 100));
            _regis.add_component<sprite_t>(n1, sprite_s(this->envAsset, "./assets/images/space_ship.png"));
            _regis.get_components<sprite_t>()[n1.get_size()]->sprite.setScale((sf::Vector2f){0.5, 0.7});
        }
    }
    else if (packet.body_t.create_entity.id == PLAYER_BULLET)
    {
        std::cout << "CREATE BULLET\n";
        _regis.add_component<HP_t>(n1, {HP_BULLET});
        _regis.add_component<my_id_t>(n1, {PLAYER_BULLET});
        _regis.add_component<drawable_s>(n1, drawable_t(SIZE_PLAYER_BULLET, sf::Color::Red, 4));
        _regis.add_component<balle_t>(n1, {});
        _regis.add_component<hit_box_t>(n1, {});
        _regis.add_component<size_entity_t>(n1, {SIZE_PLAYER_BULLET});
        _regis.add_component<velocity_t>(n1, {packet.body_t.create_entity.Velocity});
    }
    else if (packet.body_t.create_entity.id == MOB_lv0)
    {
        std::cout << "CREATE MOB\n";
        _regis.add_component<HP_t>(n1, {HP_MOB_lv0});
        _regis.add_component<hit_box_t>(n1, {});
        _regis.add_component<my_id_t>(n1, {MOB_lv0});
        _regis.add_component<HP_t>(n1, {10});
        _regis.add_component<size_entity_t>(n1, {SIZE_MOB_lv0});
        _regis.add_component<sprite_t>(n1, sprite_t(this->envAsset, "./assets/images/PngItem_6602144.png"));
        _regis.get_components<sprite_t>()[n1.get_size()]->setupAnime({0, 0}, {151, 379}, 151, 0, 5);
        _regis.get_components<sprite_t>()[n1.get_size()]->sprite.setRotation(-90);
        _regis.get_components<sprite_t>()[n1.get_size()]->sprite.setOrigin((sf::Vector2f){+151, 0});
        _regis.add_component<drawable_t>(n1, drawable_s(SIZE_MOB_lv0, {rand() % 255, rand() % 255, rand() % 255}, 50));
        //_regis.add_component<drawable_t>(n1, drawable_s(SIZE_MOB_lv0, COLOR_MOB_lv0, 50));
    }
    else if (packet.body_t.create_entity.id == WALL)
    {
        std::cout << "CREATE WALL\n";
        _regis.add_component<HP_t>(n1, {packet.body_t.create_entity.life});
        _regis.add_component<hit_box_t>(n1, {});
        _regis.add_component<my_id_t>(n1, {WALL});
        _regis.add_component<is_wall_t>(n1, {});
        _regis.add_component<velocity_t>(n1, {packet.body_t.create_entity.Velocity});
        _regis.add_component<size_entity_t>(n1, {(size_t)packet.body_t.create_entity.Degree});
        _regis.add_component<drawable_t>(n1, drawable_s(packet.body_t.create_entity.Degree, {COLOR_WALL}, 100));
        // std::cout << "CREATE WALL [" << packet.body_t.create_entity.entity_uuid << "] x = " << packet.body_t.create_entity.x << std::endl;
        // _regis.add_component<sprite_t>(n1, sprite_s(this->envAsset, "./assets/images/planete.png"));
        // _regis.get_components<sprite_t>()[n1.get_size()]->sprite.setScale((sf::Vector2f){packet.body_t.create_entity.Degree / 100, packet.body_t.create_entity.Degree / 100});
    }
    else if (packet.body_t.create_entity.id == MOB_BULLET)
    {
        std::cerr << "CREATE MOB BULLET\n";
        _regis.add_component<HP_t>(n1, {packet.body_t.create_entity.life});
        _regis.add_component<hit_box_t>(n1, {});
        _regis.add_component<my_id_t>(n1, {MOB_BULLET});
        _regis.add_component<balle_t>(n1, {});
        _regis.add_component<velocity_t>(n1, {packet.body_t.create_entity.Velocity});
        _regis.add_component<size_entity_t>(n1, {(size_t)packet.body_t.create_entity.Degree});
        _regis.add_component<drawable_t>(n1, drawable_s(packet.body_t.create_entity.Degree, {sf::Color::Yellow}, 4));
        _regis.add_component<size_entity_t>(n1, {10});
    }
}

void GameManager::msg_from_server_destroy_entity(packet_t packet, uuid_t uuid)
{
    auto &sparse_array_uuid = _regis.get_components<player_uuid_t>();
    // auto &pos = _regis.get_components<position_t>();
    // std::cerr << "\nTST :DESTROY ENTITY\n" << packet.body_t.maby_miss.entity_uuid << "\n";

    for (size_t idx = 0; idx < sparse_array_uuid.size(); idx++)
    {
        if (sparse_array_uuid[idx] && uuid_compare(sparse_array_uuid[idx]->uuid, packet.body_t.maby_miss.entity_uuid) == 0)
        {
            if (!uuid_compare(this->_uuidClient, packet.body_t.maby_miss.entity_uuid))
            {
                this->envSound.playSound(mySound::Death);
                std::cerr << "DESTROY Player" << std::endl;
            }
            else
            {
                _regis.kill_entity(_regis.entity_from_index(idx));
                std::cerr << "DESTROY Entity" << std::endl;
            }
        }
    }
}

void GameManager::msg_from_server_update_life_entity(packet_t packet, uuid_t uuid)
{
    auto &sparse_array_hp = _regis.get_components<HP_t>();
    auto &sparse_array_uuid = _regis.get_components<player_uuid_t>();

    std::cout << "__________UPDATE LIFE\n";
    for (int i = 0; i < sparse_array_uuid.size(); i++)
    {
        if (sparse_array_hp[i].has_value() && sparse_array_uuid[i].has_value())
        {
            if (uuid_compare(sparse_array_uuid[i]->uuid, packet.body_t.life.entity_uuid) == 0)
            {
                sparse_array_hp[i]->hp = packet.body_t.life.life;
                std::cout << "UPDATE LIFE\n";
            }
        }
    }
}

/**
 * @brief this function is call when client receive T_BEGIN_MOUVE from the serveur,
 * This function moove the entity who is specified with is uuid from "mouve" struct wich is in the packet
 *
 * @param packet the packet sent by the serveur
 * @param r the registry = the "array" that contain all our entity
 * @param uuid is the uuid of the client that receive this packet
 */
void GameManager::msg_from_server_begin_mouve(packet_t packet, __attribute__((unused)) uuid_t uuid)
{
    auto &pos = _regis.get_components<position_t>();
    auto &velocity = _regis.get_components<velocity_t>();

    for (size_t i = 0; i < pos.size(); i++)
    {
        if (pos[i] && velocity[i])
        {
            // TODO peut tourner avec les degrees
            // if (packet.body_t.mouve.direction == 0) {
            //     pos[i]->y -= velocity[i]->y;
            // }
            // if (packet.body_t.mouve.direction == 2) {
            //     pos[i]->y += velocity[i]->y;
            // }
            // if (packet.body_t.mouve.direction == 1) {
            //     pos[i]->x += velocity[i]->x;
            // }
            // if (packet.body_t.mouve.direction == 0) {
            //     pos[i]->y -= velocity[i]->x;
            // }
        }
    }
    // packet.body_t.mouve.entity_uuid;
}

void GameManager::msg_from_server_end_mouve(packet_t packet, __attribute__((unused)) uuid_t uuid)
{
}

void GameManager::msg_from_server_end_game(packet_t packet, __attribute__((unused)) uuid_t uuid)
{
    std::cout << "THE GAME IS FINISH";
    if (packet.body_t.is_win.check == false)
    {
        std::cout << "You Loose\n";
        Entity n1 = _regis.spawn_entity();
        _regis.add_component<position_t>(n1, {-90, -10});
        _regis.add_component<drawable_t>(n1, drawable_s(40000, {200, 10, 13, 200}, 100));
        _regis.add_component<sprite_t>(n1, sprite_s(this->envAsset, "assets/images/mort.jpg"));
        _regis.get_components<sprite_t>()[n1.get_size()]->sprite.setScale((sf::Vector2f){1, 1});
    } else {
        std::cout << "You Win\n";
        Entity n1 = _regis.spawn_entity();
        _regis.add_component<position_t>(n1, {610, 100});
        _regis.add_component<drawable_t>(n1, drawable_s(40000, {200, 10, 13, 200}, 100));
        _regis.add_component<sprite_t>(n1, sprite_s(this->envAsset, "assets/images/VICTOIRE.jpg"));
        _regis.get_components<sprite_t>()[n1.get_size()]->sprite.setScale((sf::Vector2f){0.5, 0.5});
    }
    return;
}

void GameManager::msg_from_server_update_pos_entity(packet_t packet, __attribute__((unused)) uuid_t uuid)
{
    // std::cerr << "update from serv\n";
    auto &sparse_array_uuid = _regis.get_components<player_uuid_t>();
    auto &pos = _regis.get_components<position_t>();
    auto &wall = _regis.get_components<is_wall_t>();
    auto &type = _regis.get_components<my_id_t>();

    for (size_t idx = 0; idx < sparse_array_uuid.size(); idx++)
    {
        if (0 == uuid_compare(sparse_array_uuid[idx]->uuid, packet.body_t.poss.entity_uuid))
        {
            pos[idx]->x = packet.body_t.poss.x;
            pos[idx]->y = packet.body_t.poss.y;
            return;
            // if (type[idx]->id == 1) {
            // std::cerr << packet.body_t.poss.entity_uuid << "\npos x = " << pos[idx]->x << std::endl;
            // std::cerr << "type to update : " << type[idx]->id << "\n";
            // }
        }
    }
    packet_t new_packet = {};

    packet.packet_type = packet_t::T_DONT_KNOW;
    uuid_copy(new_packet.body_t.poss.entity_uuid, packet.body_t.poss.entity_uuid);
    this->_Send.get()->SendTo(new_packet);
}