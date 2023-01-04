/*
** EPITECH PROJECT, 2022
** INDIES_STUDIO
** File description:
** Text
*/


#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "MyRaylib.hpp"
#include <string>

class Text {
    public:
        Text(char const *string, int pos_x, int pos_y, int size, Color color);
        ~Text();
        void Draw();

    protected:
    private:
        int _pos_x;
        int _pos_y;
        int _size;
        Color _color;
        std::string _str;
};

#endif /* !TEXT_HPP_ */