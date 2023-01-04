/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Camera
*/

// #include "../../../include/graphic/MyRaylib/MyRaylib.hpp"
#include "Camera.hpp"
#include <iostream>

MyRaylib::Camera::Camera(Vector3 position, Vector3 target, Vector3 up, float fovy, int projection, int mode)
{
    _camera.position = position;  // Camera position
    _camera.target = target;// Camera looking at point
    _camera.up = up;// Camera up vector (rotation towards target)
    _camera.fovy = fovy;// Camera field-of-view Y
    _camera.projection = projection;
    SetCameraMode(_camera, mode);
}

MyRaylib::Camera::Camera()
{
    _camera.position = (Vector3){0, _hauteur, 69};  // Camera position
    _camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };// Camera looking at point
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };// Camera up vector (rotation towards target)
    _camera.fovy = 90.0f;// Camera field-of-view Y
    _camera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(_camera, CAMERA_THIRD_PERSON);
}

void MyRaylib::Camera::SetCameraPosition(Vector3 pos)
{
    _camera.position = pos;
}
void MyRaylib::Camera::SetCameraTarget(Vector3 target)
{
    _camera.target = target;
}
void MyRaylib::Camera::SetCameraUp(Vector3 up)
{
    _camera.up = up;
}
void MyRaylib::Camera::SetCameraFovy(float field_of_view)
{
    _camera.fovy = field_of_view;
}
void MyRaylib::Camera::SetCameraProjection(int projection)
{
    projection += 1;
    _camera.projection = CAMERA_PERSPECTIVE;
}
void MyRaylib::Camera::SetModeCamera(CameraMode mode = CAMERA_THIRD_PERSON)
{
    SetCameraMode(_camera, mode);
}

Camera3D MyRaylib::Camera::Get()
{
    return this->_camera;
}

void MyRaylib::Camera::Update()
{
    if (_hauteur < 110) {
        _hauteur += 0.2;
        _camera.position.y = _hauteur;
    }
    if (IsKeyDown(KEY_UP)) {
        std::cout << "position x " << _camera.position.x << "\n";
        std::cout << "position y " << _camera.position.y << "\n";
        std::cout << "position z" << _camera.position.z << "\n";
        UpdateCamera(&_camera);
    }
}

void MyRaylib::Camera::Begin3DDraw()
{
    BeginMode3D(_camera);
}

void MyRaylib::Camera::End3DDraw()
{
    EndMode3D();
}