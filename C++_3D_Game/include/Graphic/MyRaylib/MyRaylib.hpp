/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** MyRaylib
*/

#ifndef MYRAYLIB_HPP_
#define MYRAYLIB_HPP_

#include "raylib.h"
#include <memory>


// typedef enum {
//     CAMERA_CUSTOM = 0,              // Custom camera
//     CAMERA_FREE,                    // Free camera
//     CAMERA_ORBITAL,                 // Orbital camera
//     CAMERA_FIRST_PERSON,            // First person camera
//     CAMERA_THIRD_PERSON             // Third person camera
// } CameraMode;

namespace MyRaylib {
    class MyRaylib {
        public:
            MyRaylib(int width, int height, const char *title);
            MyRaylib(int width, int height, int fps, const char *title);
            ~MyRaylib();

            void SetTargetFps(int fps);
            bool WindowIsOpen();
            void BeginDrawMode();
            void EndDrawMode();
            void Clear();

            void DrawGround(size_t x, size_t y);
        protected:
        private:
            Camera3D _camera;
    };
}


#endif /* !MYRAYLIB_HPP_ */

