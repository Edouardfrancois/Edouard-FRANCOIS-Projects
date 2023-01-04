/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran [WSL : Ubuntu-20.04]
** File description:
** ManageBonus
*/

#ifndef MANAGEBONUS_HPP_
#define MANAGEBONUS_HPP_

#include "components.hpp"
#include "Weapon.hpp"
#include "registry.hpp"

namespace PickUps {
    enum class Effect {
        NONE,
        HP,
        DMG,
        WEAP,
    };

    class PickUps {
        public:
            PickUps(Effect type) {
                this->_pickEffect = type;
                if (type == Effect::WEAP) {
                    rnow = std::chrono::steady_clock::now();
                    int index = rnow.time_since_epoch().count() % 3;
                    this->Wep_effect = this->_AvailableEffect[index];
                }
            }

            ~PickUps() {

            }
    
            void update(position_t pos) {
                pos.x -= 9;
            }

            bool pop(Entity subject, registry &regis) {
                if (_possibleEffect.find(_pickEffect) != _possibleEffect.end()) {
                    return this->_possibleEffect[_pickEffect](subject, regis);
                }
                return false;
            }
        protected:
        private:
            std::chrono::steady_clock::time_point rnow;

            bool pop_HP(Entity subject, registry &regis) {
                auto &HP_list = regis.get_components<HP_t>();

                HP_list[subject.get_size()]->hp += 5;
                return true;
            }

            bool pop_DMG(Entity subject, registry &regis) {
                auto &HP_list = regis.get_components<HP_t>();

                HP_list[subject.get_size()]->hp -= 15;
                return true;
            }

            bool pop_WEAP(Entity subject, registry &regis) {
                auto &WEAP_list = regis.get_components<shoot::Weapon>();

                if (WEAP_list[subject.get_size()]->GetFiringMOD() == Wep_effect || Wep_effect == shoot::FireMOD::None) {
                    return false;
                } else {
                    WEAP_list[subject.get_size()]->SetFiringMOD(Wep_effect);
                    return true;
                }
            }

            shoot::FireMOD Wep_effect = shoot::FireMOD::None;

            std::vector<shoot::FireMOD> _AvailableEffect = {
                shoot::FireMOD::Single,
                shoot::FireMOD::byThree,
                shoot::FireMOD::SuperShoot,
            };

            Effect _pickEffect;
            std::map<Effect, std::function<bool(Entity subject, registry &regis)>> _possibleEffect {
                {Effect::HP, std::function<bool(Entity, registry &)>(std::bind(&PickUps::pop_HP, this, std::placeholders::_1, std::placeholders::_2))},
                {Effect::DMG, std::function<bool(Entity, registry &)>(std::bind(&PickUps::pop_DMG, this, std::placeholders::_1, std::placeholders::_2))},
                {Effect::WEAP, std::function<bool(Entity, registry &)>(std::bind(&PickUps::pop_WEAP, this, std::placeholders::_1, std::placeholders::_2))},
            };
    };
}

#endif /* !MANAGEBONUS_HPP_ */
