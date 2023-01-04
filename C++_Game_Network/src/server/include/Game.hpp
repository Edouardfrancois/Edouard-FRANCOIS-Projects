/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <memory>
#include <chrono>
#include "registry.hpp"
#include "Packet.hpp"
#include "HandleUuid.hpp"
#include "FactoryMonster.hpp"
#include "ManageRegistry.hpp"
#include <utility>
#include "ManageWall.hpp"
#include <cmath>

Entity createPlayer(const uuid_t &uuid, const unsigned short x, const unsigned short y, registry &r);

// typedef struct manage_collision_s
// {
//     void collision_player(Entity wall, Entity other) {
//     }
// } manage_collision_t;

class Game
{
public:
    Game(std::shared_ptr<OneQueu<packet_t>> &MyQueu, const OnePacketQueue<packet_t> &P, const uuid_t &GameUuid);

private:
    void _BeginMove(OnePacketQueue<packet_t> &P);
    void _StopMove(OnePacketQueue<packet_t> &P);
    void _MoveEntity();
    /**
     * @brief Compute the new pos of all the bullets.
     *
     */
    void _UpdateBulletPosition();

public:
    /**
     * @brief Game loop.
     *
     */
    void Run();
    /**
     * @brief this function is only for test. When server receive packet it is draw here.
     *
     * @param packet the packet of the message receive
     */
    void msg(packet_t packet, __attribute__((unused)) registry &r)
    {
        std::cerr << packet.packet_type << "~~~~~~~~~~~~~~~~~~~~~~~~~~«««««««««\n";
    }
    ~Game();

private:
    /**
     * @brief This function is call when server receive : packet with type : T_ERROR_IMPOSIBLE_TO_STOP_MOVE
     *
     * @param packet the packet receive
     * @param r the register
     */
    void _MsgFromClientsErrorImpossible_to_stop_move(packet_t packet, registry &r);

    /**
     * @brief This function is call when server receive : packet with type : T_ERROR_IMPOSIBLE_TO_MOUVE
     *
     * @param packet the packet receive
     * @param r the register
     */
    void _MsgFromClientsErrorImpossible_to_move(packet_t packet, registry &r);

    /**
     * @brief This function is call when server receive : packet with type : T_ERROR_UNKNOWN_ENTITY_ID
     *
     * @param packet the packet receive
     * @param r the register
     */
    void _MsgFromClientsErrorImpossible_to_create_entity(packet_t packet, registry &r);

    /**
     * @brief This function is call when server receive : packet with type : T_ERROR_UNKNOWN_ENTITY_ID
     *
     * @param packet the packet receive
     * @param r the register
     */
    void _MsgFromClientsErrorUnknow_entity(packet_t packet, registry &r);

    /**
     * @brief This function is call when server receive : packet with type : T_ERR0R_LOBBY_FULL
     *
     * @param packet the packet receive
     * @param r the register
     */
    void _MsgFromClientsErrorLobby_full(packet_t packet, registry &r);

    /**
     * @brief This function is call when server receive : packet with type :T_ERROR
     *
     * @param packet the packet receive
     * @param r the register
     */
    void _MsgFromClientsError(packet_t packet, registry &r);

    /**
     * @brief This function is call when server receive : packet with type : T_CONNECTION
     *
     * @param packet the packet receive
     * @param r the register
     */
    void _MsgFromClientsConnection(packet_t packet, registry &r);

    /**
     * @brief This function is call when server receive : packet with type : T_BEGIN_GAME
     *
     * @param packet the packet receive
     * @param r the register
     */
    void _MsgFromClientsBeginGame(packet_t packet, registry &r);

    /**
     * @brief This function is call when server receive : packet with type : T_CREATE_ENTITY
     *
     * @param packet the packet receive
     * @param r the register
     */
    void _MsgFromClientsCreateEntity(packet_t packet, registry &r);

    /**
     * @brief This function is call when server receive : packet with type : T_BEGIN_MOUVE
     *
     * @param packet the packet receive
     * @param r the register
     */
    void _MsgFromClientsBeginMouve(packet_t packet, registry &r);

    /**
     * @brief This function is call when server receive : packet with type : T_END_MOUVE
     *
     * @param packet the packet receive
     * @param r the register
     */
    void _MsgFromClientsEndMouve(packet_t packet, registry &r);

    /**
     * @brief This function is call when server receive : packet with type : T_END_GAME
     *
     * @param packet the packet receive
     * @param r the register
     */
    void _MsgFromClientsEndGame(packet_t packet, registry &r);

    /**
     * @brief This function is call when server receive : packet with type : T_UPDATE_POS_ENTITY
     *
     * @param packet the packet receive
     * @param r the register
     */
    void _MsgFromClientDontKnow(packet_t packet, registry &r);

    /**
     * @brief This function is call when server receive : packet with type : T_UPDATE_POS
     *
     * @param packet the packet receive
     * @param r the register
     */
    void _MsgFromClientUpdatePosEntity(packet_t packet, registry &r);

    /**
     * @brief The main function for manage collision. She remove HP to defense and then she call herself with switch arg
     *
     * @param attack entity that is hiting defense
     * @param defense entity that is going to lost HP
     * @param recursion he has to be false
     */
    void _Collision(Entity attack, Entity defense, bool recursion);

    /**
     * @brief For know wich collision function you have to call you hash the two TYPE of entity
     *
     * @param i1 entity 1
     * @param i2 entity 2
     * @return the result of hash entity 1 and entity 2
     */
    int _HashCollision(int i1, int i2)
    {
        int i2_copy = i2;
        while (i2_copy)
        {
            i1 *= 10;
            i2_copy /= 10;
        }
        return i1 + i2;
    }

    void _CollisionPlayerToMonster(__attribute__((unused)) Entity entity, __attribute__((unused)) Entity other)
    {
        // std::cerr << "collision : PLAYER to MONSTER\n";
        _Collision(entity, other, false);
    }

    void _CollisionBulletToMonster(Entity entity, Entity other)
    {
        // this->_data.kill_entity(entity);
        // this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, this->_manage_regis.RmBullet(this->_data, entity));
        std::cerr << "collision : BULLET to MONSTER\n";
        _Collision(entity, other, false);
    }

    void _CollisionBulletToPlayer(__attribute__((unused)) Entity entity, __attribute__((unused)) Entity other)
    {
        // std::cerr << "collision : BULLET to PLAYER\n";
    }
    /**
     * @brief Function that is call when the collision is Bullet_Player to other Bullet_Player
     *
     * @param entity
     * @param other
     */
    void _CollisionBulletToBullet(__attribute__((unused)) Entity entity, __attribute__((unused)) Entity other)
    {
        // _Collision(entity, other, false);
    }
    void _CollisionMonsterToBullet(__attribute__((unused)) Entity entity, __attribute__((unused)) Entity bullet)
    {
        _Collision(entity, bullet, false);
        // std::cerr << "collision : MONSTER to BULLET\n";
    }

    void _CollisionWallToPLAYER(Entity wall, Entity player)
    {
        std::cerr << "collision : WALL to PLAYER\n";

        _Collision(wall, player, false);
    }

    void _CollisionBulletPlayerToWall(Entity bullet, Entity wall)
    {
        std::cerr << "collision : BULLET to WALL\n";
        _Collision(bullet, wall, false);
    }

    void _CollisionWallToWall(__attribute__((unused)) Entity wall_1, __attribute__((unused)) Entity wall_2)
    {
        // std::cerr << "collision : WALL to WALL\n";
    }

    /**
     * @brief the function that is call when there are collsion beetween :
     *
     * @param bullet_mob_1 attack
     * @param bullet_mob_2 defense
     */
    void _CollisionMobBulletToMobBullet(Entity bullet_mob_1, Entity bullet_mob_2)
    {
        // _Collision(bullet_mob_1, bullet_mob_2, false);
    }

    /**
     * @brief the function that is call when there are collsion beetween :
     *
     * @param bullet_mob attack
     * @param wall defense
     */
    void _CollisionMobBulletToWall(Entity bullet_mob, Entity wall)
    {
        _Collision(bullet_mob, wall, false);
    }

    /**
     * @brief the function that is call when there are collsion beetween :
     *
     * @param wall attack
     * @param bullet_mob defense
     */
    void _CollisionWallToMobBullet(Entity wall, Entity bullet_mob)
    {
        _Collision(wall, bullet_mob, false);
    }

    /**
     * @brief the function that is call when there are collsion beetween :
     *
     * @param bullet_mob attack
     * @param player_bullet defense
     */
    void _CollisionMobBulletToPlayerBullet(Entity bullet_mob, Entity player_bullet)
    {
        _Collision(bullet_mob, player_bullet, false);
    }

    /**
     * @brief the function that is call when there are collsion beetween :
     *
     * @param bullet_mob attack
     * @param player_bullet defense
     */
    void _CollisionPlayerBulletToMobBullet(Entity player_bullet, Entity bullet_mob)
    {
        _Collision(player_bullet, bullet_mob, false);
    }

    /**
     * @brief the function that is call when there are collsion beetween :
     *
     * @param bullet_mob attack
     * @param player_bullet defense
     */
    void _CollisionMobBulletToMob(Entity bullet_mob, Entity mob)
    {
        // _Collision(bullet_mob, mob, false);
    }

    /**
     * @brief the function that is call when there are collsion beetween :
     *
     * @param bullet_mob attack
     * @param player_bullet defense
     */
    void _CollisionMobToMobBullet(Entity mob, Entity bullet_mob)
    {
        // _Collision(mob, bullet_mob, false);
    }

    /**
     * @brief the function that is call when there are collsion beetween :
     *
     * @param bullet_mob attack
     * @param player_bullet defense
     */
    void _CollisionMobBulletToPlayer(Entity bullet_mob, Entity player)
    {
        std::cout << "Collision : MobBullet -> Player\n";
        _Collision(bullet_mob, player, false);
    }

    /**
     * @brief the function that is call when there are collsion beetween :
     *
     * @param bullet_mob attack
     * @param player_bullet defense
     */
    void _CollisionPlayerToMobBullet(Entity player, Entity bullet_mob)
    {
        std::cout << "Collision : Player -> MobBullet\n";
        _Collision(player, bullet_mob, false);
    }

    /**
     * @brief the function that is call when there are collsion beetween :
     *
     * @param bullet_mob attack
     * @param player_bullet defense
     */
    void _CollisionPlayerToWall(Entity wall, Entity player)
    {
        std::cerr << "collision : PLAYER to WALL\n";

        _Collision(wall, player, false);
    }

    /**
     * @brief the function that is call when there are collsion beetween :
     *
     * @param bullet_mob attack
     * @param player_bullet defense
     */
    void _CollisionMobToMob(Entity mob_1, __attribute__((unused)) Entity mob_2)
    {
    }

    void KillEntityIsOut(int idx)
    {
        auto &pos = this->_data.get_components<position_t>();
        auto &uuid = this->_data.get_components<player_uuid_t>();

        Entity entity = this->_data.entity_from_index(idx);
        if (pos[entity.get_size()]->x > (float)2000 || pos[entity.get_size()]->x < float(-1000))
            this->_data.kill_entity(entity);
    }

    template <class T>
    T GetMax(T a, T b)
    {
        T result;
        result = (a > b) ? a : b;
        return (result);
    }

    template <class T>
    int CountType(T sparse_array)
    {
        int res = 0;
        for (int i = 0; i < sparse_array.size(); i++)
        {
            if (sparse_array[i].has_value())
                res += 1;
        }
        return res;
    }

    /**
     * @brief the function that manage all entity which need to update their pos to the client
     *
     */
    void _UpdatePosClient()
    {
        std::chrono::steady_clock::time_point time_now;
        packet_t packet = {};
        sparse_array<velocity_t> &vel = this->_data.get_components<velocity_t>();
        sparse_array<player_uuid_t> &uuid = this->_data.get_components<player_uuid_t>();
        sparse_array<update_to_client_t> &update = this->_data.get_components<update_to_client_t>();
        sparse_array<position_t> &pos = this->_data.get_components<position_t>();
        sparse_array<is_monster_t> &monster = this->_data.get_components<is_monster_t>();
        sparse_array<size_entity_t> &size = this->_data.get_components<size_entity_t>();
        auto &clock_updt = this->_data.get_components<clock_for_updt_t>();
        // double shot = 30000000;

        packet.packet_type = packet_t::T_UPDATE_POS_ENTITY;
        for (int i = 0; i < update.size(); i++)
        {
            // KillEntityIsOut(i);
            if (update[i].has_value() && uuid[i].has_value() && pos[i].has_value() && vel[i].has_value())
            {
                pos[i]->x += (double)((double)vel[i]->Velocity * (double)60) / (double)this->fps;
                if (monster.size() > i && monster[i].has_value() == true)
                {
                    pos[i]->y = (fabs(cos(pos[i]->x / 90)) * (monster[i]->entendue));
                    time_now = std::chrono::steady_clock::now();
                    std::chrono::duration<double, std::deci> diff = (time_now - clock_updt[i]->start);
                    if (diff.count() > 15)
                    {
                        // std::cerr << "mob shot\n";
                        _factoryMonster.CreateBulletMonster(this->_data, pos[i].value());
                        clock_updt[i]->start = std::chrono::steady_clock::now();
                    }
                }
                packet.body_t.poss.x = pos[i]->x;
                packet.body_t.poss.y = pos[i]->y;
                uuid_copy(packet.body_t.poss.entity_uuid, uuid[i]->uuid);
                this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, packet);
            }
        }
        // frame++;
    }

    /**
     * @brief the function that is call when there are collsion beetween :
     *
     * @param bullet_mob attack
     * @param player_bullet defense
     */
    void _CollisionWallToBullet(Entity wall, Entity bullet)
    {
        // _Collision(wall, bullet, false);
    }

    /**
     * @brief the function that is call when there are collsion beetween :
     *
     * @param wall
     * @param mob
     */
    void _CollisionWallToMob(Entity wall, Entity mob)
    {
        // _Collision(wall, mob, false);
    }

    /**
     * @brief the function that is call when there are collsion beetween :
     *
     * @param mob
     * @param wall
     */
    void _CollisionMobToWall(Entity mob, Entity wall)
    {
        //
    }

    void _CheckCollision();

    /**
     * @brief Create a Players object
     *
     */
    void CreatePlayers();

    /**
     * @brief Create a Players On Server object
     *
     */
    void CreatePlayersOnServer();

    /**
     * @brief Create a Players On Client object
     *
     */
    void CreatePlayersOnClient();

    /**
     * @brief Create a one Player
     *
     * @param uuid the uuid of the player
     * @param x position on x axe
     * @param y position on y axe
     * @param r the registry that contain all our entitys
     */
    void CreateOnePlayer(const uuid_t &uuid, const unsigned short x, const unsigned short y, registry &r);

    bool CheckIsFinish()
    {
        auto &sparse_array_id = _data.get_components<my_id_t>();
        // auto &sparse_array_pos = r.get_components<position_t>();
        int nb_player = 0;

        for (int i = 0; i < sparse_array_id.size(); i++)
        {
            if (sparse_array_id[i].has_value() && sparse_array_id[i]->id == PLAYER)
            {
                nb_player += 1;
            }
        }
        if (nb_player == 0)
        {
            packet_t packet = {};
            packet.packet_type = packet_t::T_END_GAME;
            packet.body_t.is_win.check = false;
            this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, packet);
            return false;
        }
        // std::cerr << "nb_mob = " << res << std::endl;
        return true;
    }

protected:
private:
    std::shared_ptr<OneQueu<packet_t>> _MyQueu;
    registry _data;
    uuid_t _GameUuid;
    std::unordered_map<packet_t::type_e, std::function<
                                             void(Game &, packet_t packet, registry &r)>>
        _manage_message_from_client;
    int _SocketServer;
    int fps;
    double _speedcoef;
    double _temp;
    double _get;
    bool _is_game = true;
    FactoryMonster _factoryMonster;
    ManageRegistry _manage_regis;
    ManageWall _manage_wall;
    std::unordered_map<int, std::function<void(Game &, Entity, Entity)>> _collision;
};

#endif /* !GAME_HPP_ */
