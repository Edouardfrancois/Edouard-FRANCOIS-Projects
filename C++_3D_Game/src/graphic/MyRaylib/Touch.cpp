/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Touch
*/

#include <iostream>
#include "MyRaylib.hpp"
#include "Touch.hpp"

MyRaylib::Touch::Touch(char menu, char pickup, char put, char up, char down, char left, char  right)
{
    _manette = false;
    _tabTouch.push_back(menu);
    _tabTouch.push_back(pickup);
    _tabTouch.push_back(put);
    _tabTouch.push_back(up);
    _tabTouch.push_back(down);
    _tabTouch.push_back(left);
    _tabTouch.push_back(right);
}

MyRaylib::Touch::Touch(std::vector<char>& touch) : _tabTouch(touch)
{
    std::cout << _tabTouch[0] << "\n";
    if (_tabTouch[0] == '0') {
        std::cout << "lol manett\n";
        _manette = true;}
    else
        _manette = false;
}

MyRaylib::Touch::Touch(bool manette)
{
    _manette = true;
    std::cout << "Manette is setup\n";
}

MyRaylib::Action MyRaylib::Touch::GetActionFromTouch()
{
    if (_manette == true)
        return GetActionFromManette();
    char key = static_cast<char>(GetCharPressed());

    for (int i = 0; i <= Right; i++) {
        if (_tabTouch[i] == key) 
            return static_cast<Action>(i);
    }
    return Nothing;
}

MyRaylib::Action MyRaylib::Touch::GetActionFromManette()
{
    int a = GetGamepadButtonPressed();

    if (a == 1)
        return Up;
    if (a == 2)
        return Right;
    if (a == 3)
        return Down;
    if (a == 4)
        return Left;
    if (a == 7)
        return Put;
    if (a == 6)
        return PickUp;
    if (a == 15)
        return Menu;
    return Nothing;
}