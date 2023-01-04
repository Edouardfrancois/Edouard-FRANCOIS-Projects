/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Rectangle
*/

#include "MyRaylib.hpp"

#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

class MyRectangle {
    public:
        MyRectangle(Vector2 pos, Vector2 size);
        ~MyRectangle();
        void Draw(Color color);
        Rectangle Get();

    protected:
    private:
        Rectangle _rectangle;
};

#endif /* !RECTANGLE_HPP_ */