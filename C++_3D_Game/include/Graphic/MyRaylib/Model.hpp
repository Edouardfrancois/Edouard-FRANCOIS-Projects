/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Model
*/


#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "MyRaylib.hpp"
#include <iostream>
#include "raymath.h"
#include "../../../include/Graphic/MyRaylib/Texture.hpp"
#include "../../../include/Graphic/MyRaylib/Animation.hpp"

namespace MyRaylib {

    class MyModel {
        public:
            MyModel(char const *file_name);
            MyModel(char const *file_name_model, char const *file_name_texture);
            ~MyModel();
            void SetTexture(Texture texture);
            void Animatinig(Animation& animation);
            void Draw(Vector3 pos, Vector3 rotation_axis, float rotation_angle, Vector3 scale, Color color);
            void TurnDroite() {
                yaw = -90;
                _model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*pitch, DEG2RAD*roll, DEG2RAD*yaw});

            }
            void TurnLeft() {///
                yaw = 90;
                _model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*pitch, DEG2RAD*roll, DEG2RAD*yaw});

            }
            void TurnUp() {
                yaw = -180;
                _model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*pitch, DEG2RAD*roll, DEG2RAD*yaw});

            }
            void TurnDown() {
                yaw = 0;
                _model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*pitch, DEG2RAD*roll, DEG2RAD*yaw});

            }
        protected:
        private:
            float pitch = 0;
            float roll = 0;
            float yaw = 0;
            Model _model;
    };
}

#endif /* !MODEL_HPP_ */