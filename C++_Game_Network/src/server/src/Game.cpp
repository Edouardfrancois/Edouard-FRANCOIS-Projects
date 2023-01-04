/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** Game
*/

#include "EntityId.hpp"
#include "Game.hpp"
#include "components.hpp"

#include <unistd.h>
#include <cstdlib>
#include <cmath>

Game::Game(std::shared_ptr<OneQueu<packet_t>> &MyQueu, const OnePacketQueue<packet_t> &P, const uuid_t &GameUuid) : _MyQueu(MyQueu), _manage_wall(_MyQueu, P.e.Socket), _factoryMonster(_MyQueu, P.e.Socket)
{
    std::cerr << "LE SERVEUR VA DIRE QUE LA GAME COMMENCE" << std::endl;
    uuid_copy(this->_GameUuid, GameUuid);
    this->fps = 512;

    this->_SocketServer = P.e.Socket;
    this->CreatePlayers();

    // create the first monster.
    // monster_t mon = this->_factoryMonster.Generate(1, 800, int((rand() % 1920 - (SIZE_MOB_lv0 * 2))));
    // this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer,
    // this->_manage_regis.AddMonster(this->_data, mon, 0));

    // this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer,
    // this->_manage_regis.AddMonster(this->_data,
    // this->_factoryMonster.Generate(1, 800, 200), 0));

    this->_manage_message_from_client.insert({packet_t::type_e::T_ERROR_IMPOSIBLE_TO_STOP_MOVE, &Game::_MsgFromClientsErrorImpossible_to_stop_move});
    this->_manage_message_from_client.insert({packet_t::type_e::T_ERROR_IMPOSIBLE_TO_MOUVE, &Game::_MsgFromClientsErrorImpossible_to_move});
    this->_manage_message_from_client.insert({packet_t::type_e::T_ERROR_UNKNOWN_ENTITY_ID, &Game::_MsgFromClientsErrorImpossible_to_create_entity});
    this->_manage_message_from_client.insert({packet_t::type_e::T_ERROR_UNKNOWN_ENTITY_ID, &Game::_MsgFromClientsErrorUnknow_entity});
    this->_manage_message_from_client.insert({packet_t::type_e::T_ERR0R_LOBBY_FULL, &Game::_MsgFromClientsErrorLobby_full});
    this->_manage_message_from_client.insert({packet_t::type_e::T_ERROR, &Game::_MsgFromClientsError});
    this->_manage_message_from_client.insert({packet_t::type_e::T_CONNECTION, &Game::_MsgFromClientsConnection});
    this->_manage_message_from_client.insert({packet_t::type_e::T_BEGIN_GAME, &Game::_MsgFromClientsBeginGame});
    this->_manage_message_from_client.insert({packet_t::type_e::T_CREATE_ENTITY, &Game::_MsgFromClientsCreateEntity});
    this->_manage_message_from_client.insert({packet_t::type_e::T_BEGIN_MOUVE, &Game::_MsgFromClientsBeginMouve});
    this->_manage_message_from_client.insert({packet_t::type_e::T_END_MOUVE, &Game::_MsgFromClientsEndMouve});
    this->_manage_message_from_client.insert({packet_t::type_e::T_END_GAME, &Game::_MsgFromClientsEndGame});
    this->_manage_message_from_client.insert({packet_t::type_e::T_UPDATE_POS_ENTITY, &Game::_MsgFromClientUpdatePosEntity});
    this->_manage_message_from_client.insert({packet_t::type_e::T_DONT_KNOW, &Game::_MsgFromClientDontKnow});

    this->_collision.insert({this->_HashCollision(entity_id_e::PLAYER, entity_id_e::MOB_lv0), &Game::_CollisionPlayerToMonster});
    this->_collision.insert({this->_HashCollision(entity_id_e::PLAYER_BULLET, entity_id_e::MOB_lv0), &Game::_CollisionBulletToMonster});
    this->_collision.insert({this->_HashCollision(entity_id_e::PLAYER_BULLET, entity_id_e::PLAYER), &Game::_CollisionBulletToPlayer});
    this->_collision.insert({this->_HashCollision(entity_id_e::PLAYER_BULLET, entity_id_e::PLAYER_BULLET), &Game::_CollisionBulletToBullet});
    this->_collision.insert({this->_HashCollision(entity_id_e::MOB_lv0, entity_id_e::PLAYER_BULLET), &Game::_CollisionMonsterToBullet});
    this->_collision.insert({this->_HashCollision(entity_id_e::WALL, entity_id_e::PLAYER), &Game::_CollisionWallToPLAYER});
    this->_collision.insert({this->_HashCollision(entity_id_e::WALL, entity_id_e::PLAYER_BULLET), &Game::_CollisionWallToBullet});
    this->_collision.insert({this->_HashCollision(entity_id_e::PLAYER_BULLET, entity_id_e::WALL), &Game::_CollisionBulletPlayerToWall});
    this->_collision.insert({this->_HashCollision(entity_id_e::WALL, entity_id_e::WALL), &Game::_CollisionWallToWall});
    this->_collision.insert({this->_HashCollision(entity_id_e::PLAYER, entity_id_e::WALL), &Game::_CollisionPlayerToWall});
    this->_collision.insert({this->_HashCollision(entity_id_e::MOB_lv0, entity_id_e::MOB_lv0), &Game::_CollisionMobToMob});
    this->_collision.insert({this->_HashCollision(entity_id_e::WALL, entity_id_e::MOB_lv0), &Game::_CollisionWallToMob});
    this->_collision.insert({this->_HashCollision(entity_id_e::MOB_lv0, entity_id_e::WALL), &Game::_CollisionMobToWall});

    this->_collision.insert({this->_HashCollision(entity_id_e::MOB_BULLET, entity_id_e::MOB_BULLET), &Game::_CollisionMobBulletToMobBullet});

    this->_collision.insert({this->_HashCollision(entity_id_e::MOB_BULLET, entity_id_e::WALL), &Game::_CollisionMobBulletToWall});
    this->_collision.insert({this->_HashCollision(entity_id_e::WALL, entity_id_e::MOB_BULLET), &Game::_CollisionWallToMobBullet});

    this->_collision.insert({this->_HashCollision(entity_id_e::MOB_BULLET, entity_id_e::PLAYER_BULLET), &Game::_CollisionMobBulletToPlayerBullet});
    this->_collision.insert({this->_HashCollision(entity_id_e::PLAYER_BULLET, entity_id_e::MOB_BULLET), &Game::_CollisionPlayerBulletToMobBullet});

    this->_collision.insert({this->_HashCollision(entity_id_e::MOB_BULLET, entity_id_e::MOB_lv0), &Game::_CollisionMobBulletToMob});
    this->_collision.insert({this->_HashCollision(entity_id_e::MOB_lv0, entity_id_e::MOB_BULLET), &Game::_CollisionMobToMobBullet});

    this->_collision.insert({this->_HashCollision(entity_id_e::MOB_BULLET, entity_id_e::PLAYER), &Game::_CollisionMobBulletToPlayer});
    this->_collision.insert({this->_HashCollision(entity_id_e::PLAYER, entity_id_e::MOB_BULLET), &Game::_CollisionPlayerToMobBullet});
}

void Game::_Collision(Entity defense, Entity attack, bool recursion)
{
    packet_t packet = {};
    sparse_array<HP_t> &hp = this->_data.get_components<HP_t>();
    sparse_array<player_uuid_t> &uuid = this->_data.get_components<player_uuid_t>();
    sparse_array<powerfull_t> &powerfull = this->_data.get_components<powerfull_t>();

    if (!uuid[attack.get_size()])
    {
        // std::cerr << uuid[attack.get_size()]->uuid << "attack not found\n";
        return;
    }
    // std::cerr << uuid[attack.get_size()]->uuid << "attack found\n";

    if (hp[attack.get_size()].has_value())
    {
        // std::cerr << "If in collision\n";
        if ((size_t)hp[defense.get_size()]->hp > (size_t)powerfull[attack.get_size()]->powerfull)
        {
            // std::cerr << "If in collision _______________1"<< (size_t)hp[defense.get_size()]->hp << "|||||" << (size_t)powerfull[attack.get_size()]->powerfull << "\n";
            hp[defense.get_size()]->hp -= powerfull[attack.get_size()]->powerfull;
            packet.packet_type = packet_t::T_UPDATE_LIFE;
            if (recursion == false)
                _Collision(attack, defense, true);
            uuid_copy(packet.body_t.life.entity_uuid, uuid[defense.get_size()]->uuid);
            packet.body_t.life.life = hp[defense.get_size()]->hp - powerfull[attack.get_size()]->powerfull;
        }
        else
        {
            // std::cerr << "If in collision _______________1else\n";
            hp[defense.get_size()]->hp = 0;
            packet.packet_type = packet_t::T_DESTROY_ENTITY;
            uuid_copy(packet.body_t.maby_miss.entity_uuid, uuid[defense.get_size()]->uuid);
            if (recursion == false)
                _Collision(attack, defense, true);
            this->_data.kill_entity(defense);
            // std::cerr << "destroy\n";
        }
        this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, packet);
        return;
    }
}

/**
 * @brief This function is call for each frame. If there are collision she call
 * the function coresponding of the type of the collsion
 *
 */
void Game::_CheckCollision()
{
    sparse_array<hit_box_t> &box = this->_data.get_components<hit_box_t>();
    sparse_array<position_t> &pos = this->_data.get_components<position_t>();
    sparse_array<size_entity_t> &size = this->_data.get_components<size_entity_t>();
    sparse_array<my_id_t> &id = this->_data.get_components<my_id_t>();
    // sparse_array<balle_t> &bullets = this->_data.get_components<balle_t>();

    for (size_t idx = 0; idx < box.size(); idx++)
    {
        for (size_t i = 0; i < box.size(); i++)
        {
            if (idx != i && box[i].has_value() && pos[i].has_value() && size[i].has_value() && id[i].has_value() && box[idx].has_value())
            {
                sf::FloatRect fst(pos[idx]->x, pos[idx]->y, size[idx]->size * 2, size[idx]->size * 2);
                sf::FloatRect sd(pos[i]->x, pos[i]->y, size[i]->size, size[i]->size);

                if (fst.intersects(sd))
                {
                    std::cout << "hash " << id[idx]->id << id[i]->id << "\n";
                    this->_collision[this->_HashCollision(id[idx]->id, id[i]->id)](*this, _data.entity_from_index(idx), _data.entity_from_index(i));
                }
            }
        }
    }
}

void Game::_UpdateBulletPosition()
{
    auto &sparse_array_balle = this->_data.get_components<balle_t>();
    auto &sparse_array_position = this->_data.get_components<position_t>();

    auto &sparse_array_velocity = this->_data.get_components<velocity_t>();

    for (size_t idx = 0; idx < sparse_array_balle.size(); idx++)
        if (sparse_array_position[idx].has_value() && sparse_array_balle[idx].has_value() && sparse_array_velocity[idx].has_value())
        {
            double speed_x = (double)((double)sparse_array_velocity[idx]->Velocity * (double)60) / (double)this->fps;
            // double speed_y = (sparse_array_velocity[idx]->y * 60)/this->fps;
            sparse_array_position[idx]->x += speed_x;
            // sparse_array_position[idx]->y += speed_y;
        }
}

void Game::_MoveEntity()
{
    sparse_array<my_id_t> &Id = this->_data.get_components<my_id_t>();
    sparse_array<position_t> &Poss = this->_data.get_components<position_t>();
    sparse_array<move_t> &Move = this->_data.get_components<move_t>();

    for (size_t i = 0; i < Id.size(); ++i)
    {
        if ((!(Id[i].has_value() && Poss[i].has_value() && Move[i].has_value())))
            continue;
        // switch (Move[i]->dir)
        // {
        // case 0: // TOP
        //     Poss[i]->y--;
        //     break;
        // case 1: // RIGHT
        //     Poss[i]->x++;
        //     break;
        // case 2: // BAS
        //     Poss[i]->y++;
        //     break;
        // case 3: // LEFT
        //     Poss[i]->x--;
        //     break;
        // default:
        //     printf("C la delacanse\n");
        //     break;
        // }
    }
}

void Game::_BeginMove(OnePacketQueue<packet_t> &P)
{
    sparse_array<move_t> &Move = this->_data.get_components<move_t>();
    sparse_array<player_uuid_t> &MyEntity = this->_data.get_components<player_uuid_t>();

    for (size_t i = 0; i < Move.size(); ++i)
    {
        if (!MyEntity[i].has_value())
            continue;
        if (uuid_compare(P.Data.body_t.mouve.entity_uuid, MyEntity[i]->uuid) != 0)
            continue;
        // TODO Move avec Vx et Vy et Degree
        // Move[i]->dir = P.Data.body_t.mouve.speed;
        // Move[i]->mouving = P.Data.body_t.mouve.direction;
        packet_t NewP = {};
        uuid_copy(NewP.lobbyUuid, this->_GameUuid);
        uuid_copy(NewP.packetuuid, P.Data.packetuuid);
        NewP.packet_type = packet_t::T_BEGIN_MOUVE;
        uuid_copy(NewP.body_t.mouve.entity_uuid, P.Data.body_t.mouve.entity_uuid);
        // NewP.body_t.mouve.speed = P.Data.body_t.mouve.speed;
        // NewP.body_t.mouve.direction = P.Data.body_t.mouve.direction;
        this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, NewP);
        break;
    }
}

void Game::_StopMove(__attribute__((unused)) OnePacketQueue<packet_t> &P)
{
}

void Game::Run()
{
    double frameTimeMS = 1000 / this->fps;
    {
        char struuidLobby[37] = {};
        uuid_unparse_lower(this->_GameUuid, struuidLobby);
        std::cerr << "[Info] Game: " << struuidLobby << " Begin." << std::endl;
    }
    bool z = false;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

    while (CheckIsFinish())
    {
        std::chrono::duration<double, std::milli> elapsed_mili = (end - start);
        // std::chrono::duration<double> elapsed_seconds = (end - start);
        if (elapsed_mili.count() < frameTimeMS)
        {
            usleep(((frameTimeMS)-elapsed_mili.count()) * 1000);
        }
        start = std::chrono::steady_clock::now();
        _MoveEntity();
        // this->_UpdateBulletPosition();
        this->_CheckCollision();
        this->_factoryMonster.update(this->_data);

        this->_manage_wall.Update(this->_data);
        this->_UpdatePosClient();
        if (this->_MyQueu.get()->IsQueueEmpty())
        {
            end = std::chrono::steady_clock::now();
            z = true;
            continue;
        }
        OnePacketQueue<packet_t> Packet = {};
        this->_MyQueu.get()->GetOnQueu(Packet); //----------------------------------------------
        printf("%d\n", Packet.Data.packet_type);
        this->_manage_message_from_client[Packet.Data.packet_type](*this, Packet.Data, this->_data);
        end = std::chrono::steady_clock::now();
    }
}

Game::~Game()
{
}
