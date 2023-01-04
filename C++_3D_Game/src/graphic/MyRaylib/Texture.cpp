/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Texture
*/

#include "MyRaylib.hpp"
#include "Texture.hpp"

MyRaylib::Texture::Texture(char const *file_name)
{
    _texture = LoadTexture(file_name);
}

MyRaylib::Texture::Texture(Image img)
{
    _texture = LoadTextureFromImage(img);
}

MyRaylib::Texture::~Texture()
{
}

Texture2D  MyRaylib::Texture::Get()
{
    return _texture;
}

void MyRaylib::Texture::DrawCube(Vector3 pos, float width, float height, float lenght)
{
    DrawCubeTexture(_texture, pos, width, height, lenght, GRAY);
}