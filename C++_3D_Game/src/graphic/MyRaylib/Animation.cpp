/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Animation
*/

#include "MyRaylib.hpp"
#include "Animation.hpp"


MyRaylib::Animation::Animation(char const *file_name)
{
    unsigned int tmp = 0;

    _animation = LoadModelAnimations(file_name, &tmp);
}

MyRaylib::Animation::~Animation()
{
}

ModelAnimation *MyRaylib::Animation::Get()
{
    return _animation;
}

int MyRaylib::Animation::GetFrame()
{
    return _frame;
}

void MyRaylib::Animation::AddToFrame(int add)
{
    _frame += add;
}
void MyRaylib::Animation::ResetFrame()
{
    _frame = 0;
}