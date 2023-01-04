/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Graphic
*/

#ifndef GRAPHIC_HPP_
#define GRAPHIC_HPP_

#include "Menu.hpp"
#include "IA.hpp"
#include "Json.hpp"


static const int MENU = 3;
static const int GAME = 4;
static const int END = 5;

namespace Graphic {

    // class Character {
    //     public:
    //         Character(Vector3 pos, std::string model_name, std::string anim_name);
    //         ~Character();
    //         void Draw();

    //     protected:
    //         Vector3 _position;
    //         Vector3 _rotation;
    //         Vector3 _scale;
    //         float _rotation_angle;
    //         Color _color;
    //         MyRaylib::MyModel _model;
    //         MyRaylib::Animation _animation;
    // };

    // typeid 
    // class Player : public Character{
    //     public:
    //     Player(Vector3 pos, std::string model_name, std::string anim_name,
    //     char menu, char pickup, char put, char up, char down, char left, char  right);
    //     ~Player();
    //         MyRaylib::Action GetAction();
    //     private:
    //         MyRaylib::Touch _touch;
    // };

    class   Graphic {
        public:
            Graphic();
            ~Graphic();
            int MyMenu(std::array<std::vector<char>, 4>& touch);
            int MyGame(const TAllMap& map);
            void SetUp(size_t x, size_t y, Json::Json& str_texture);
            void AddCamera(Camera camera);
            MyRaylib::Action Frame(const TAllMap& map);
            // bool Frame(Menu& menu);
            void SetMapSize();

        protected:
        private:
            MyRaylib::Action Draw(const TAllMap& map);
            MyRaylib::Action Draw3D(const TAllMap& map);
        private:
            MyRaylib::Action DrawMap(const TAllMap& map);
            MyRaylib::MyRaylib _raylib;
            std::vector<MyRaylib::Camera> _cameras;
            size_t _idx_camera;
            size_t _map_size_x;
            size_t _map_size_y;
            std::vector <MyRaylib::Texture> _texture;
            Menu _menu;
            MyRaylib::MyMusic _music;
            MyRaylib::Animation _anim;
    };
}   
#endif /* !GRAPHIC_HPP_ */
