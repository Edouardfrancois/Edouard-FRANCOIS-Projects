/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** step3
*/

#include <vector>
#include <iostream>
#include <optional>
#include "SparseArray.hpp"
#include "boostrap.hpp"
#include "step3.hpp"

// g++ step3.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


void logging_system(registry &r) {
    auto const &positions = r.get_components<position_t>();
    auto const &velocities = r.get_components<velocity_t>();

    for (size_t i = 0 ; i < positions.size() && i < velocities.size(); ++i) {
        auto const &pos = positions[i];
        auto const &vel= velocities[i];
        if(pos && vel) {
            std::cerr << i << ":Position={" << pos->x << "," <<pos->y << "},Velocity={" << vel->x << "," << vel->y << "}" << std::endl;
        }
    }
}

void create_register(registry &r) {
    r.register_component<position_t>();
    r.register_component<velocity_t>();
    r.register_component<drawable_t>();
    r.register_component<controllable_t>();

    Entity square = r.spawn_entity();
    //drawable_t(60, (sf::Color){20, 30, 50});
    r.add_component<position_t>(square, {20, 20});
    r.add_component<velocity_t>(square, {20.f, 20.f});
    r.add_component<drawable_t>(square, drawable_t(60, (sf::Color){20, 30, 50}));
    // r.add_component<controllable_t>(square, std::nullopt);
}

void draw_registre(sf::RenderWindow &window, registry &r) {
    auto const &drawable = r.get_components<drawable_t>();
    auto const &pos = r.get_components<position_t>();

    for (size_t i = 0 ; i < drawable.size(); i++) {
        if (drawable[i] && pos[i]) {
            std::cout << pos[i]->x << "\n";
            drawable[i]->draw(window);
        }
    }
}