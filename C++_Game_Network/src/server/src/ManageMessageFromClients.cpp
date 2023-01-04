/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** ManageMessageFromClients
*/

#include <iostream>
#include "Packet.hpp"

#include "GameManager.hpp"
#include "components.hpp"
#include "registry.hpp"
#include "Game.hpp"

void Game::_MsgFromClientsErrorImpossible_to_stop_move(packet_t packet, __attribute__((unused)) registry &r)
{
    std::cerr << packet.packet_type << "~~~~~~~~~~~~~~~~~~~~~~~~~~«««««««««\n";
}
void Game::_MsgFromClientsErrorImpossible_to_move(packet_t packet, __attribute__((unused)) registry &r)
{
    std::cerr << packet.packet_type << "~~~~~~~~~~~~~~~~~~~~~~~~~~«««««««««\n";
}
void Game::_MsgFromClientsErrorImpossible_to_create_entity(packet_t packet, __attribute__((unused)) registry &r)
{
    std::cerr << packet.packet_type << "~~~~~~~~~~~~~~~~~~~~~~~~~~«««««««««\n";
}
void Game::_MsgFromClientsErrorUnknow_entity(packet_t packet, __attribute__((unused)) registry &r)
{
    std::cerr << packet.packet_type << "~~~~~~~~~~~~~~~~~~~~~~~~~~«««««««««\n";
}
void Game::_MsgFromClientsErrorLobby_full(packet_t packet, __attribute__((unused)) registry &r)
{
    std::cerr << packet.packet_type << "~~~~~~~~~~~~~~~~~~~~~~~~~~«««««««««\n";
}
void Game::_MsgFromClientsError(packet_t packet, __attribute__((unused)) registry &r)
{
    std::cerr << packet.packet_type << "~~~~~~~~~~~~~~~~~~~~~~~~~~«««««««««\n";
}

void Game::_MsgFromClientsConnection(packet_t packet, __attribute__((unused)) registry &r)
{
}

void Game::_MsgFromClientsBeginGame(packet_t packet, __attribute__((unused)) registry &r)
{
}

void Game::_MsgFromClientsCreateEntity(packet_t packet, __attribute__((unused)) registry &r)
{
    if (packet.body_t.create_entity.id == PLAYER_BULLET) {
        Entity entity = r.spawn_entity();
        uuid_t uuid;
        player_uuid_t P = {};
        packet_t new_packet = {};

        // r.add_component<type_entity_t>(entity, {PLAYER_BULLET});
        r.add_component<my_id_t>(entity, { PLAYER_BULLET});
        r.add_component<position_t>(entity, {(float)packet.body_t.create_entity.x, (float)packet.body_t.create_entity.y});
        r.add_component<size_entity_t>(entity, {SIZE_PLAYER_BULLET});
        r.add_component<drawable_t>(entity, drawable_s(SIZE_PLAYER_BULLET, COLOR_MOB_lv0, 100));
        r.add_component<hit_box_t>(entity, {});
        r.add_component<HP_t>(entity, {HP_BULLET});
        r.add_component<powerfull_t>(entity, {POWERFULL_BULLET_PLAYER});
        r.add_component<update_to_client_t>(entity, {});
        uuid_generate_random(uuid);
        uuid_copy(r.emplace_component<player_uuid_t>(entity, P)->uuid, uuid);
        // r.add_component<drawable_s>(entity, drawable_t(SIZE_PLAYER_BULLET, sf::Color::Red, 4));
        r.add_component<balle_t>(entity, {});
        r.add_component<velocity_t>(entity, {packet.body_t.create_entity.Velocity});

        new_packet.packet_type = packet_t::T_CREATE_ENTITY;
        new_packet.body_t.create_entity.id = entity_id_e::PLAYER_BULLET;
        new_packet.body_t.create_entity.x = packet.body_t.create_entity.x;
        new_packet.body_t.create_entity.y = packet.body_t.create_entity.y;
        new_packet.body_t.create_entity.Velocity = VELOCITY_BULLET_PLAYER;
        new_packet.body_t.create_entity.life = HP_BULLET;
        new_packet.body_t.create_entity.Degree = 0;
        uuid_copy(new_packet.body_t.create_entity.entity_uuid, uuid);
        this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, new_packet);
    }
}

void Game::_MsgFromClientsBeginMouve(packet_t packet, __attribute__((unused)) registry &r)
{
    std::cerr << packet.packet_type << "~~~~~~~~~~~~~~~~~~~~~~~~~~«««««««««\n";
}
void Game::_MsgFromClientsEndMouve(packet_t packet, __attribute__((unused)) registry &r)
{
    std::cerr << packet.packet_type << "~~~~~~~~~~~~~~~~~~~~~~~~~~«««««««««\n";
}
void Game::_MsgFromClientsEndGame(packet_t packet, __attribute__((unused)) registry &r)
{
    std::cerr << packet.packet_type << "~~~~~~~~~~~~~~~~~~~~~~~~~~«««««««««\n";
}

void Game::_MsgFromClientDontKnow(packet_t packet, registry &r)
{
    packet_t new_packet = {};
    auto &uuid = r.get_components<player_uuid_t>();
    auto &id = r.get_components<my_id_t>();
    auto &pos = r.get_components<position_t>();

    for (size_t idx = 0; idx < uuid.size(); idx++) {
        if (!uuid_compare(uuid[idx]->uuid, packet.body_t.poss.entity_uuid)) {
            new_packet.body_t.create_entity.id = id[idx]->id;
            new_packet.body_t.create_entity.x = pos[idx]->x;
            new_packet.body_t.create_entity.y = pos[idx]->y;
            new_packet.packet_type = packet_t::T_CREATE_ENTITY;
            uuid_copy(new_packet.body_t.create_entity.entity_uuid, packet.body_t.poss.entity_uuid);
            this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, new_packet);
        }
    }
}


void Game::_MsgFromClientUpdatePosEntity(packet_t packet, __attribute__((unused)) registry &r)
{
    auto &uuid = r.get_components<player_uuid_t>();
    auto &pos = r.get_components<position_t>();
    packet_t new_packet = {};

    for (size_t idx = 0; idx < uuid.size(); idx++) {
        if (uuid[idx] && pos[idx]) {
            if (!uuid_compare(uuid[idx]->uuid, packet.body_t.poss.entity_uuid)) {
                pos[idx]->x = packet.body_t.poss.x;
                pos[idx]->y = packet.body_t.poss.y;

                new_packet.packet_type = packet_t::T_UPDATE_POS_ENTITY;
                new_packet.body_t.poss.x = pos[idx]->x;
                new_packet.body_t.poss.y = pos[idx]->y;
                uuid_copy(new_packet.body_t.poss.entity_uuid, uuid[idx]->uuid);
                this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, new_packet);
            }
        }
    }
}