/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Rectangle
*/

#include "Rectangle.hpp"

MyRectangle::MyRectangle(Vector2 pos, Vector2 size)
{
    _rectangle.x = pos.x;
    _rectangle.y = pos.y;
    _rectangle.width = size.x;
    _rectangle.height = size.y;
}

MyRectangle::~MyRectangle()
{
}

void MyRectangle::Draw(Color color)
{
    DrawRectangleRec(_rectangle, color);   
}

Rectangle MyRectangle::Get()
{
    return _rectangle;
}
