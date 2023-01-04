/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** Particule
*/

#include "registry.hpp"
#include "components.hpp"
#include<cstdlib>

#ifndef PARTICULE_HPP_
#define PARTICULE_HPP_

class Particule {
    public:
        Particule(registry &r) {
            srand((unsigned) time(NULL));

            int nb_particule =  60 + (rand() % 100);
            float x = 0;
            float y = 0;

            for (int i = 0; i < nb_particule; i++) {
                Entity entity = r.spawn_entity();
                x = rand() % 1920;
                y = rand() % 1080;
                r.add_component<particule_t>(entity, {});
                r.add_component<my_id_t>(entity, {entity_id_e::ID_PARTICULE});
                r.add_component<position_t>(entity, {x, y});
                r.add_component<size_entity_t>(entity, {SIZE_PARTICULE});
                r.add_component<drawable_t>(entity, drawable_s(SIZE_PARTICULE, COLOR_PARTICULE, 4));
                r.add_component<velocity_t>(entity, {VELOCITY_PARTICULE});
            }
        }
        ~Particule() {}

        void update(registry &r) {
            auto &sparse_array_velocity = r.get_components<velocity_t>();
            auto &sparse_array_position = r.get_components<position_t>();
            auto &sparse_array_particule = r.get_components<particule_t>();
    

    for (size_t idx = 0; idx < sparse_array_particule.size(); idx++)
        if (sparse_array_position[idx].has_value() && sparse_array_velocity[idx].has_value() && sparse_array_particule[idx].has_value())
        {
            sparse_array_position[idx]->x += sparse_array_velocity[idx]->Velocity;
            if (sparse_array_position[idx]->x <= 0) {
                sparse_array_position[idx]->x = SIZE_BACKGROUND + (rand() % SIZE_BACKGROUND);
                sparse_array_position[idx]->y = rand() % 1080;
            }
        }
        }

    protected:
    private:
};

#endif /* !PARTICULE_HPP_ */