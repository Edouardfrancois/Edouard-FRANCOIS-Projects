/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Touch
*/

#ifndef TOUCH_HPP_
#define TOUCH_HPP_

#include <vector>

namespace MyRaylib {
    
    enum Action {
        Menu = 0,
        PickUp,
        Put,
        Up,
        Down,
        Left,
        Right,
        Nothing
    };

    class Touch {
        public:
            Touch(char menu, char pickup, char put, char up, char down, char left, char  right);
            Touch(bool manette);
            Touch(std::vector<char>& touch);
            ~Touch() = default;


            Action GetActionFromTouch();
        protected:
        private:
            Action GetActionFromManette();
            bool _manette;
            std::vector <char> _tabTouch;
    };

}

#endif /* !TOUCH_HPP_ */
