/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** MyRaylib
*/

#include "MyRaylib.hpp"

#include <iostream>

MyRaylib::MyRaylib::MyRaylib(int width, int height, int fps, const char *title)
{
    InitWindow(width, height, title);
    SetTargetFPS(fps);
    InitAudioDevice();
}
MyRaylib::MyRaylib::MyRaylib(int width, int height, const char *title)
{
    InitWindow(width, height, title);
    InitAudioDevice();
    _camera.position = (Vector3){10, 10, 10};  // Camera position
    _camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };// Camera looking at point
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };// Camera up vector (rotation towards target)
    _camera.fovy = 45.0f;// Camera field-of-view Y
    _camera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(_camera, CAMERA_THIRD_PERSON);
}

MyRaylib::MyRaylib::~MyRaylib()
{
    std::cout << "close window\n";
    CloseWindow();
}

void MyRaylib::MyRaylib::Clear()
{
    ClearBackground(RAYWHITE);
}

bool MyRaylib::MyRaylib::WindowIsOpen()
{
    if (WindowShouldClose())
        return false;
    return true;
}

void MyRaylib::MyRaylib::SetTargetFps(int fps)
{
    SetTargetFPS(fps);
}

void MyRaylib::MyRaylib::BeginDrawMode()
{
    BeginDrawing();
}
void MyRaylib::MyRaylib::EndDrawMode()
{
    EndDrawing();
}

void MyRaylib::MyRaylib::DrawGround(size_t x, size_t y)
{
    DrawPlane((Vector3){0, 0, 0}, (Vector2){static_cast<float>(x), static_cast<float>(y)}, LIGHTGRAY);
}