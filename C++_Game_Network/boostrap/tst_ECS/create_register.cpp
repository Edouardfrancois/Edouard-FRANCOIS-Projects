/*
** EPITECH PROJECT, 2022
** boostrap
** File description:
** create_register
*/

#include <vector>
#include <iostream>
#include <optional>
#include "../SparseArray.hpp"
#include "../boostrap.hpp"
#include "components.hpp"

void create_register(registry &r) {
    r.register_component<position_t>();
    r.register_component<velocity_t>();
    r.register_component<drawable_t>();
    r.register_component<controllable_t>();
}