/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Menu
*/

#include "IDisplay.hpp"
#include "MyRaylib.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Touch.hpp"
#include "Model.hpp"
#include "Animation.hpp"
#include "Rectangle.hpp"
#include <array>
#include "Text.hpp"
#include "Music.hpp"
#include "Graphic.hpp"
#include <vector>
#include <iostream>

#ifndef MENU_HPP_
#define MENU_HPP_

static const int NUM_FRAMES = 3;
static const int MODE_1 = 1;
static const int MODE_2 = 2;
static const int MODE_3 = 3;
static const int MODE_4 = 4;
static const int NOTHING = 5;

namespace Graphic {

    class Btns {
        public:
            Btns(char const*str, Vector2 pos, Vector2 size,
            Color color1, Color color2, Color color3, int (*action) (void));
            ~Btns();
            int Frame();
            bool IsOn();
            void Off();
        private:
            int Update();
            void Draw();

            Text _text;
            std::string name;
            int _state = 0;
            int (*_action) (void);
            MyRectangle _rect;
            Vector2 _mouse_pos;
            std::vector<Color>_colors;
            bool _is_click;
    };
    class Button {
        public:
            Button(char const*str, Vector2 pos, Vector2 size,
            Color color1, Color color2, Color color3, bool (*action) (void));
            ~Button();
            bool Frame();
            bool IsOn();
            void Off();
        bool GetMode1() {return _mode1;}
            bool GetMode2() {return _mode2;}
            bool GetMode3() {return _mode3;}
            bool GetMode4() {return _mode4;}
        private:
            bool Update();
            void Draw();

            Text _text;
            std::string name;
            int _state = 0;
            Sound _fxButton;
            bool (*_action) (void);
            MyRectangle _rect;
            Vector2 _mouse_pos;
            std::vector<Color>_colors;
            bool _is_click;
            std::vector<std::unique_ptr<Btns>> _list_select;
            bool _mode1 = false;
            bool _mode2 = false;
            bool _mode3 = false;
            bool _mode4 = false;
    };


    class Menu {
        public:
            Menu();
            ~Menu();
            bool IsOn();
            int Draw();
            void GetInfoMenu(std::array<std::vector<char>, 4>& touch);
            void Active() { _active = true;}
            void Unactive() { _active = false;}

        protected:
        private:
            void Close() { _active = false;};

            bool _active;
            std::vector<std::unique_ptr<Button>> _btns_players;
            Button _btn_play;
    };
}
#endif /* !MENU_HPP_ */