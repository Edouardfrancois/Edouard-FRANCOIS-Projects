/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Player
*/

#include <cmath>

#include "Player.hpp"

Player::Player(size_t x, size_t y, std::vector<char>& touch) : IEntity(ObjType::OBJENTITY, x, y), _Touch(touch)
{
    this->SetNewPoss(GetPoss());
}

MyRaylib::Action Player::Run(const MyRaylib::Action& Action, const PassIaInfoGame_t& GameInfo)
{
    Poss_t &NewPoss = this->GetNewPoss();
    size_t ToAdd;

    if (Action == MyRaylib::Action::Nothing)
        return MyRaylib::Action::Nothing;

    if (LastAction.LastAction != Action && LastAction.turn == false)
        LastAction.turn = true;
    else
        LastAction.turn = false;
    LastAction.LastAction = Action;
    if (!this->_IsUse) {
        ToAdd = lround(
                ((___TimeMaster * GameInfo.ConfPlayer.Speed) / 1) < 1
                    ?
                1
                    :
                ((___TimeMaster * GameInfo.ConfPlayer.Speed) / 1)
            );
    }

    this->SetNewPoss(this->GetPoss());
    switch(Action) {
        case MyRaylib::Action::Up:
            NewPoss.SetY(NewPoss.GetY() - ToAdd);
            break;
        case MyRaylib::Action::Down:
            NewPoss.SetY(NewPoss.GetY() + ToAdd);
        break;
        case MyRaylib::Action::Left :
            NewPoss.SetX(NewPoss.GetX() - ToAdd);
        break;
        case MyRaylib::Action::Right :
            NewPoss.SetX(NewPoss.GetX() + ToAdd);
        break;
        default:
            return Action;
    }
    return MyRaylib::Action::Nothing;
}

// 9b -> 1s
    // <- 0.05s