/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** ManageWall
*/

#include "registry.hpp"
#include "components.hpp"
#include <functional>
#include <cstdlib>
#include <vector>

#ifndef MANAGEWALL_HPP_
#define MANAGEWALL_HPP_

enum LevelWall {
    NOTHING,
    ONE_SOMETIMES,
    ONE_BY_ONE,
    ONLY_WALL,
};

typedef struct wall_s
{
    float pos_x;
    float pos_y;
    int size_x;
    int size_y;
    int hp;
} wall_t;
class ManageWall {
    public:
        ManageWall(std::shared_ptr<OneQueu<packet_t>> &MyQueu, int SocketServer) : _level(NOTHING), _MyQueu(MyQueu), _SocketServer(SocketServer) {
            this->_update_functions.push_back(&ManageWall::_UpdateNothing);
            this->_update_functions.push_back(&ManageWall::_UpdateOneSometimes);
            this->_update_functions.push_back(&ManageWall::_UpdateOneByOne);
            this->_update_functions.push_back(&ManageWall::_UpdateOnlyWall);
            this->_last = std::chrono::steady_clock::now();
        }


        ~ManageWall() {}

        void 
        Update(registry &r) {
            this->_update_functions[_level](*this, r);
            if (_level == NOTHING)
                _CheckMonster(r);
        }

    private:
        void _UpdateNothing(registry &r) {
        }

        void _UpdateOneSometimes(registry &r) {
        }
        void _UpdateOneByOne(registry &r) {
        }
        void _UpdateOnlyWall(registry &r)
        {
            std::chrono::steady_clock::time_point time_now = std::chrono::steady_clock::now();
            std::chrono::duration<double, std::milli> elapsed_mili = (time_now - this->_last);
            auto &sparse_array_velocity = r.get_components<velocity_t>();
            auto &sparse_array_position = r.get_components<position_t>();
            auto &sparse_array_wall = r.get_components<is_wall_t>();
            auto &sparse_array_uuid = r.get_components<player_uuid_t>();
            auto &sparse_array_size = r.get_components<size_entity_t>();

            if (elapsed_mili.count() > 2000) {
                this->_last = std::chrono::steady_clock::now();
                _CreateWall(r);
                return ;
            }
            for (size_t idx = 0; idx < sparse_array_wall.size(); idx++) {
                if (sparse_array_position[idx].has_value() && sparse_array_velocity[idx].has_value() && sparse_array_wall[idx].has_value() && sparse_array_uuid[idx].has_value())
                {
                    if (sparse_array_position[idx]->x + (sparse_array_size[idx]->size * 2) <= 0) {
                        packet_t packet = {};
                        packet.packet_type = packet_t::T_DESTROY_ENTITY;
                        uuid_copy(packet.body_t.maby_miss.entity_uuid, sparse_array_uuid[idx]->uuid);
                        this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, packet);
                        // std::cerr << "KILL WALL\n";
                        r.kill_entity(r.entity_from_index(idx));
                        _CreateWall(r);
                        return ;
                    }
                }
            }
        }

        void _CreateWall(registry &r)
        {
            packet_t packet = {};
            float size = 50 + (rand() % 200);
            float x = 1920 + (rand() % 1920);
            float y = rand() % (int)((float)1080 - size);
            uuid_t uuid;
            player_uuid_t P = {};

            std::cout << "CREATE WALL\n";
            Entity entity = r.spawn_entity();
            uuid_generate(uuid);
            r.add_component<HP_t>(entity, {HP_WALL});
            r.add_component<hit_box_t>(entity, {});
            r.add_component<is_wall_t>(entity, {});
            r.add_component<my_id_t>(entity, {WALL});
            r.add_component<position_t>(entity, {x, y});
            r.add_component<size_entity_t>(entity, {(size_t)size});
            r.add_component<drawable_t>(entity, drawable_s(size, COLOR_WALL, 4));
            r.add_component<velocity_t>(entity, {VELOCITY_WALL});
            r.add_component<update_to_client_t>(entity, {});
            uuid_copy(r.emplace_component<player_uuid_t>(entity, P)->uuid, uuid);
            uuid_copy(packet.body_t.create_entity.entity_uuid, uuid);
            packet.packet_type = packet_t::T_CREATE_ENTITY;
            packet.body_t.create_entity.id = WALL;
            packet.body_t.create_entity.x = x;
            packet.body_t.create_entity.y = y;
            packet.body_t.create_entity.Velocity = VELOCITY_WALL;
            packet.body_t.create_entity.Degree = size;
            this->_MyQueu.get()->SendPacketToAllUsr(this->_SocketServer, packet);
        }

        void _CheckMonster(registry &r) {
            auto &sparse_array_id = r.get_components<my_id_t>();
            int a = 0;

            // for (int i = 0; i < sparse_array_id.size(); i++) {
            //     if (sparse_array_id[i].has_value() && sparse_array_id[i]->id == MOB_lv0) {
            //         a++;
            //         _level = NOTHING;
            //         return ;
            //     }
            // }
            // if (a == 0)
            _level = ONLY_WALL;
        }

    protected:
    private:
        size_t _nbWall = 0;
        LevelWall _level;
        std::vector<std::function<void(ManageWall &, registry &r)>> _update_functions;
        std::shared_ptr<OneQueu<packet_t>> _MyQueu;
        int _SocketServer;
        std::chrono::steady_clock::time_point _last;

};

#endif /* !MANAGEWALL_HPP_ */
