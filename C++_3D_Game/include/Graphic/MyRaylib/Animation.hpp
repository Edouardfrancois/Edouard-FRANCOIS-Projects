/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Animation
*/

#include "MyRaylib.hpp"

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

namespace MyRaylib {

    class Animation {
        public:
            Animation(char const *file_name);
            ~Animation();
            ModelAnimation *Get();
            int GetFrame();
            void AddToFrame(int add);
            void ResetFrame();
        private:
            ModelAnimation *_animation;
            int _frame = 0;

    };

}

#endif /* !ANIMATION_HPP_ */
