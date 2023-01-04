/*
** EPITECH PROJECT, 2022
** boostrap
** File description:
** create_entity
*/

#include <vector>

#include <optional>
#include "../SparseArray.hpp"
#include "../boostrap.hpp"
#include "components.hpp"

void create_entity_1(registry &r, sf::Texture texture)
{

    Entity n1 = r.spawn_entity();

    r.add_component<position_t>(n1, {20, 20});
    r.add_component<velocity_t>(n1, {20.f, 20.f});
    r.add_component<drawable_t>(n1, {});
    r.add_component<sprite_t>(n1, {sf::Sprite(texture)});
    r.add_component<size_t>(n1, {10});
}

/*fonction asyncrone*/