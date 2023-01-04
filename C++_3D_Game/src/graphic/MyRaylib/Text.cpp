/*
** EPITECH PROJECT, 2022
** INDIES_STUDIO
** File description:
** Text
*/

#include "Text.hpp"

Text::Text(char const *string, int pos_x, int pos_y, int size, Color color) : _str(string),
_pos_x(pos_x), _pos_y(pos_y), _size(size), _color(color)
{
}

Text::~Text()
{
}

void Text::Draw()
{
    DrawText(_str.c_str(), _pos_x, _pos_y, _size, _color);
}