/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "IEntity.hpp"
#include "MyRaylib.hpp"
#include "Timer.hpp"
#include "Touch.hpp"
#include "JsonData.hpp"
#include "IA.hpp"

class Player : public IEntity {
    public:
        Player(size_t x, size_t y, std::vector<char>& touch);
        ~Player() = default;
        MyRaylib::Action Run(const MyRaylib::Action& Action, const PassIaInfoGame_t& GameInfo);
        MyRaylib::Touch& GetTouch() {return this->_Touch;}
    private:
        MyRaylib::Touch _Touch;
};

#endif /* !PLAYER_HPP_ */
