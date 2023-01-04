/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Model
*/

#include "MyRaylib.hpp"
#include "Model.hpp"

MyRaylib::MyModel::MyModel(char const *file_name)
{
    _model = LoadModel(file_name);
}

MyRaylib::MyModel::MyModel(char const *file_name_model, char const *file_name_texture)
{
    Texture texture(file_name_texture);

    _model = LoadModel(file_name_model);
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, texture.Get());
}

MyRaylib::MyModel::~MyModel()
{
    UnloadModel(_model);
}

void MyRaylib::MyModel::SetTexture(Texture texture)
{
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, texture.Get());
}

void MyRaylib::MyModel::Animatinig(Animation& animation)
{
    animation.AddToFrame(1);

    UpdateModelAnimation(_model, animation.Get()[0], animation.GetFrame());
    if (animation.GetFrame() >= animation.Get()[0].frameCount)
        animation.ResetFrame();
}

void MyRaylib::MyModel::Draw(Vector3 pos, Vector3 rotation_axis, float rotation_angle, Vector3 scale, Color color)
{
    DrawModelEx(_model, pos, rotation_axis, rotation_angle, scale, color);
}