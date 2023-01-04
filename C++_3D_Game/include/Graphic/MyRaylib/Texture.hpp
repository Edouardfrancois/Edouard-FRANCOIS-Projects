/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Texture
*/

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

namespace MyRaylib{

    class Texture {
        public:
            Texture(char const *file_name);
            Texture(Image img);
            ~Texture();
            Texture2D Get();
            void DrawCube(Vector3 pos, float width, float height, float lenght);
        protected:
        private:
            Texture2D _texture;
    };
}

#endif /* !TEXTURE_HPP_ */