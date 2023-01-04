/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Camera
*/

    #include "MyRaylib.hpp"

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

namespace MyRaylib {
    class Camera {
        public:
            Camera(Vector3 position, Vector3 target, Vector3 up, float fovy, int projection, int mode);
            Camera();
            ~Camera() = default;

            Camera3D Get();

            void SetCameraPosition(Vector3 pos);
            void SetCameraTarget(Vector3 target);
            void SetCameraUp(Vector3 up);
            void SetCameraFovy(float field_of_view);
            void SetCameraProjection(int projection);
            void SetModeCamera(CameraMode mode);
            void Begin3DDraw();
            void End3DDraw();
            void Update();
        protected:
        private:
            Camera3D _camera;
            float _hauteur = 10;
    };
}

#endif /* !CAMERA_HPP_ */
