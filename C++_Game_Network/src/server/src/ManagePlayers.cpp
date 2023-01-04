/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** ManagePlayers
*/

#include "Game.hpp"
#include "registry.hpp"
#include "components.hpp"

void Game::CreatePlayersOnServer()
{
    unsigned short y = 120;
    unsigned short x = 400;

    for (const auto &Usr : this->_MyQueu.get()->GetAllUsr())
    {
        Entity e = this->_data.spawn_entity();
        player_uuid_t P = {};

        std::cerr << "SERVER ADD ONE PLAYERS ON HIS REGISTRE" << std::endl;
        this->_data.add_component<position_t>(e, {(float)x, (float)y});
        this->_data.add_component<move_t>(e, {0, 0});
        this->_data.add_component<my_id_t>(e, {entity_id_e::PLAYER});
        uuid_copy(this->_data.emplace_component<player_uuid_t>(e, P)->uuid, Usr.uuid);
        this->_data.add_component<hit_box_t>(e, {});
        this->_data.add_component<size_entity_t>(e, {40});
        this->_data.add_component<HP_t>(e, {HP_PLAYER});
        this->_data.add_component<powerfull_t>(e, {POWERFULL_HIT_PLAYER});
        y += 100;
        x += 200;
    }
}

void Game::CreatePlayersOnClient()
{

    sparse_array<player_uuid_t> &Player = this->_data.get_components<player_uuid_t>();
    sparse_array<position_t> &Poss = this->_data.get_components<position_t>();

    for (size_t i = 0; i < Player.size(); ++i)
    {
        if (Player[i].has_value() && Poss[i].has_value())
        {
            packet_t PtoSend = {};
            uuid_copy(PtoSend.lobbyUuid, this->_GameUuid);
            PtoSend.packet_type = packet_t::T_CREATE_ENTITY;
            PtoSend.body_t.create_entity.id = entity_id_e::PLAYER;
            uuid_copy(PtoSend.body_t.create_entity.entity_uuid, Player[i]->uuid);
            PtoSend.body_t.create_entity.x = Poss[i]->x;
            PtoSend.body_t.create_entity.y = Poss[i]->y;
            PtoSend.body_t.create_entity.life = HP_PLAYER;
            this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, PtoSend);
        }
    }
}

void Game::CreatePlayers()
{
    this->CreatePlayersOnServer();
    this->CreatePlayersOnClient();
}