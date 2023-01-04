/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** StaticElem
*/

#include "Indi.hpp"
#include "StaticElem.hpp"

Bomb::Bomb(size_t x, size_t y) : IObject(ObjType::OBJBOMB, x, y), Model("assets/indie_bomb_model.iqm", "assets/Bomb_indie.png") {
    TimerExplose.Start();
}