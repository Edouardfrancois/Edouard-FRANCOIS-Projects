/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran [WSL : Ubuntu-20.04]
** File description:
** Weapon
*/

#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include "MyDisplay.hpp"
#include "Packet.hpp"
#include "SendPacket.hpp"
#include "EntityId.hpp"

#include <map>
#include <queue>
#include <functional>
#include <memory>

namespace shoot
{
    enum class FireMOD {
        None,
        Single,
        byThree,
        SuperShoot,
    };

    class Weapon {
        public:
            Weapon() {
                this->_mod = FireMOD::None;
            }

            Weapon(FireMOD type, const entity_id_e &id, float veloce) {
                this->_mod = type;
                this->_id = id;
                this->_velocity = veloce;
                //regis = r;
                //_sender = std::move(sender);
            }
            ~Weapon() {

            }

            void SetFiringMOD(FireMOD newMod) {
                this->_mod = newMod;
            }
    
            FireMOD GetFiringMOD() const {
                return this->_mod;
            }

            std::queue<packet_t> shoot(position_t const &pos) {
                sf::Time curr = this->_cd.getElapsedTime();

                if (curr.asMilliseconds() < _max_rate) {
                    return std::queue<packet_t>();
                }
                if (this->_possibleMod.find(this->_mod) != _possibleMod.end()) {
                    this->_cd.restart();
                    return this->_possibleMod[_mod](pos, this->_id, this->_velocity);
                }
                return std::queue<packet_t>();
            }
        protected:
        private:
            entity_id_e _id;
            float _velocity;

            packet_t create_Bullet(position_t const &pos, const entity_id_e &id, float sped)
            {
                packet_t P;

                P.packet_type = packet_t::T_CREATE_ENTITY;
                P.body_t.create_entity.id = id;
                P.body_t.create_entity.x = pos.x;
                P.body_t.create_entity.y = pos.y;
                P.body_t.create_entity.Degree = 0;
                P.body_t.create_entity.Velocity = sped;
                return P;
            }

            std::queue<packet_t> shootSingle(position_t const &pos, const entity_id_e &id, float sped) {
                // std::cerr << pos.x << " && " << pos.y << std::endl;
                // std::cerr << "ShotSingle" << std::endl;

                std::queue<packet_t> res;
                res.push(create_Bullet(pos, id, sped));
                return res;
            }

            std::queue<packet_t> shootByThree(position_t const &pos, const entity_id_e &id, float sped) {
                // std::cerr << pos.x << " && " << pos.y << std::endl;
                // std::cerr << "ShotByThree" << std::endl;
                std::queue<packet_t> res;
                return res;
            }

            std::queue<packet_t> shootSuperShot(position_t const &pos, const entity_id_e &id, float sped) {
                // std::cerr << pos.x << " && " << pos.y << std::endl;
                // std::cerr << "ShotSuperShot" << std::endl;
                
                std::queue<packet_t> res;

                std::vector<position_t> list= {
                    pos,
                    position_t(pos),
                    position_t(pos),
                };
                list[1].y -= 15;
                list[2].y += 15;

                for (size_t i = 0; i < list.size(); i += 1) {
                    res.push(create_Bullet(list.at(i), id, sped));
                }
                return res;
            }

            // firing rate man
            sf::Clock _cd;
            int _max_rate = 100;

            // Local Weapon Var
            FireMOD _mod;
            std::map<FireMOD, std::function<std::queue<packet_t>(position_t const &pos, const entity_id_e &id, float sped)>> _possibleMod {
                {FireMOD::Single,std::function<std::queue<packet_t>(position_t const &, entity_id_e const &, float)>(std::bind(&Weapon::shootSingle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))},
                {FireMOD::byThree,std::function<std::queue<packet_t>(position_t const &, entity_id_e const &, float)>(std::bind(&Weapon::shootByThree, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))},
                {FireMOD::SuperShoot,std::function<std::queue<packet_t>(position_t const &, entity_id_e const &, float)>(std::bind(&Weapon::shootSuperShot, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))},
            };

    };
} // namespace Weapon

#endif /* !WEAPON_HPP_ */
