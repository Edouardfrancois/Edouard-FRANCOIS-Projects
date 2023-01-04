/*
** EPITECH PROJECT, 2022
** client
** File description:
** GameManager
*/

#ifndef GAMEMANAGER_HPP_
#define GAMEMANAGER_HPP_

#include "HandleUuid.hpp"
#include "SendPacket.hpp"
#include "HandleServer.hpp"
#include "ThreadPool.hpp"
#include "Packet.hpp"
#include "registry.hpp"
#include "MyDisplay.hpp"
#include "Weapon.hpp"
#include "Lobby.hpp"
#include "Particule.hpp"
#include "Manage_Asset.hpp"
#include "mySoundManager.hpp"

class GameManager
{
public:
    GameManager(char *argv[]);
    ~GameManager();

private:
    void ping();
    void _FncForTestPrintPacket(const packet_t &Packet);
    void _FncForTest();
    void _ConnectToServer();
    void manage_player_input(input_key player_key);
    void manage_player_inputQueue(std::queue<input_key> player_keys);
    void _SendServUuidBeginMove(const uuid_t &uuid);
    void _SendServUuidStopMove(const uuid_t &uuid);
    void _UpdatePosToServer();
    void UpdateBulletPosition();
    void UpdateWallPosition();
    void AnalyseMessageServeur(packet_t packet);
    void _CheckCollision();
    /**
     * @brief Run the game
     *
     */
    void _RunGame();
    void _RunLobby();

    void PrintHp();
    void _GenerateBackGround()
    {
    }

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

    void _CollisionPlayerToMonster(Entity entity, __attribute__((unused)) Entity other)
    {
        packet_t packet = {};
        sparse_array<HP_t> &hp = this->_regis.get_components<HP_t>();
        sparse_array<player_uuid_t> &uuid = this->_regis.get_components<player_uuid_t>();

        if (!uuid[entity.get_size()].has_value())
        {
            std::cerr << "entity not found\n";
            return;
        }

        if (hp[entity.get_size()].has_value())
        {
            if (hp[entity.get_size()]->hp > 20)
            {
                hp[entity.get_size()]->hp -= 20;
                packet.packet_type = packet_t::T_UPDATE_LIFE;
                uuid_copy(packet.body_t.life.entity_uuid, uuid[entity.get_size()]->uuid);

                packet.body_t.life.life = hp[entity.get_size()]->hp - 20;
            }
            else
            {
                hp[entity.get_size()]->hp = 0;
                packet.packet_type = packet_t::T_DESTROY_ENTITY;
                uuid_copy(packet.body_t.maby_miss.entity_uuid, uuid[entity.get_size()]->uuid);
                this->_regis.kill_entity(entity);
            }
            // this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, packet);
            return;
        }
        // _data.entity_from_index
        std::cerr << "entity not found\n";
    }
    void _CollisionBulletToMonster(Entity entity, __attribute__((unused)) Entity other)
    {
        this->_regis.kill_entity(entity);
        // this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, this->_manage_regis.RmBullet(this->_data, entity));
    }

    void _CollisionBulletToPlayer(__attribute__((unused)) Entity entity, __attribute__((unused)) Entity other)
    {
    }
    /**
     * @brief Function that is call when the collision is Bullet_Player to other Bullet_Player
     *
     * @param entity
     * @param other
     */
    void _CollisionBulletToBullet(__attribute__((unused)) Entity entity, __attribute__((unused)) Entity other)
    {
        // this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, this->_manage_regis.RmBullet(this->_data, entity));
        int a = 0;
    }
    void _CollisionMonsterToBullet(Entity entity, Entity other)
    {
        static int a = 0;

        packet_t packet = {};
        sparse_array<HP_t> &hp = this->_regis.get_components<HP_t>();
        sparse_array<player_uuid_t> &uuid = this->_regis.get_components<player_uuid_t>();

        if (!uuid[entity.get_size()])
        {
            std::cerr << uuid[entity.get_size()]->uuid << "entity not found\n";
            return;
        }
        std::cerr << uuid[entity.get_size()]->uuid << "entity found\n";

        if (hp[entity.get_size()])
        {
            if (hp[entity.get_size()]->hp > 2000)
            {
                hp[entity.get_size()]->hp -= 2000;
                packet.packet_type = packet_t::T_UPDATE_LIFE;
                uuid_copy(packet.body_t.life.entity_uuid, uuid[entity.get_size()]->uuid);

                packet.body_t.life.life = hp[entity.get_size()]->hp - 20;
            }
            else
            {
                hp[entity.get_size()]->hp = 0;
                packet.packet_type = packet_t::T_DESTROY_ENTITY;
                uuid_copy(packet.body_t.maby_miss.entity_uuid, uuid[entity.get_size()]->uuid);
                this->_regis.kill_entity(entity);
            }
            return;
        }
        // _data.entity_from_index
        // std::cerr << "entity not found\n";
    }
    void msg_from_server_error_impossible_to_stop_move(packet_t packet, uuid_t uuid);
    void msg_from_server_error_impossible_to_move(packet_t packet, uuid_t uuid);
    void msg_from_server_error_impossible_to_create_entity(packet_t packet, uuid_t uuid);
    void msg_from_server_error_unknow_entity(packet_t packet, uuid_t uuid);
    void msg_from_server_error_lobby_full(packet_t packet, uuid_t uuid);
    void msg_from_server_error(packet_t packet, uuid_t uuid);
    void msg_from_server_connection(packet_t packet, uuid_t uuid);
    void msg_from_server_begin_game(packet_t packet, uuid_t uuid);
    void msg_from_server_create_entity(packet_t packet, uuid_t uuid);
    void msg_from_server_begin_mouve(packet_t packet, uuid_t uuid);
    void msg_from_server_end_mouve(packet_t packet, uuid_t uuid);
    void msg_from_server_end_game(packet_t packet, __attribute__((unused)) uuid_t uuid);
    void msg_from_server_update_pos_entity(packet_t packet, __attribute__((unused)) uuid_t uuid);
    void msg_from_server_destroy_entity(packet_t packet, __attribute__((unused)) uuid_t uuid);
    void msg_from_server_update_life_entity(packet_t packet, __attribute__((unused)) uuid_t uuid);

public:
    void Run();
    registry get_registry() const
    {
        return this->_regis;
    }
    registry &get_registry()
    {
        return this->_regis;
    }

protected:
private:
    Manage_Asset envAsset;
    mySound::SoundManager envSound;

    MyDisplay _Disp;
    registry _regis;
    registry _menuRegis;
    registry _WaiterRegis;
    registry _LobbyRegis;

    std::shared_ptr<SendPacket<packet_t>> _Send;
    std::unique_ptr<HandleServer> _HandleServ;
    std::shared_ptr<utils::SafeQueue<packet_t>> _QueuThread;
    ThreadPool _Pool;
    std::shared_ptr<Lobby> _Lobby;
    std::unordered_map<packet_t::type_e, std::function<
                                             void(GameManager &, packet_t packet, uuid_t uuid)>>
        _manage_message_from_server;

    shoot::Weapon _playerGun;
    std::vector<Entity> Entitys;
    uuid_t _uuidClient;
    int entityIdx = 0;
    bool begingame = false;
    short int _fpsMax = 60;
    Particule _particules;
    std::unordered_map<int, std::function<void(GameManager &, Entity, Entity)>> _collision;
    Manage_Asset _envAsset;
};

#endif /* !GAMEMANAGER_HPP_ */
