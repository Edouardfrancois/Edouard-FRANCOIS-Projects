/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Menu
*/

#include "Menu.hpp"

bool func()
{
    std::cout << "tsst\n";
    return true;
}

bool close_menu()
{
    return false;
}

Graphic::Btns::Btns(char const *str, Vector2 pos, Vector2 size,
Color color1, Color color2, Color color3, int (*action) (void)) : _rect(pos, size), name(str), 
_text(str, pos.x, pos.y, 70, BLACK)
{
    _colors.push_back(color1);
    _colors.push_back(color2);
    _colors.push_back(color3);
    _mouse_pos = {0, 0};
    _action = action;
    _is_click = false;
}

Graphic::Btns::~Btns()
{
}

int Graphic::Btns::Frame()
{
    int tmp = Update();
    Draw();
    _text.Draw();
    return tmp;
}

int first()
{
    std::cout << "1\n";
    return 1;
}
int second()
{
    std::cout << "2\n";
    return 2;
}
int third()
{
    std::cout << "3\n";
    return 3;
}
int fourth()
{
    std::cout << "4\n";
    return 4;
}

int Graphic::Btns::Update()
{
    _mouse_pos = GetMousePosition();
    if (CheckCollisionPointRec(_mouse_pos, _rect.Get()) && _is_click != true) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            _state = 2;
            _is_click = true;
            return _action();
        } else if (!_is_click)
            _state = 1;
    } else if (CheckCollisionPointRec(_mouse_pos, _rect.Get()) && _is_click == true) {
        // _state = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            std::cout << "false\n";
            _state = 1;
            _is_click = false;
        } else if (!_is_click)
            _state = 1;
    } else if (_is_click != true)
        _state = 0;
    return NOTHING;
}

void Graphic::Btns::Off()
{
    _state = 0;
    _is_click = false;
}

void Graphic::Btns::Draw()
{
    _rect.Draw(_colors[_state]);
}

bool Graphic::Btns::IsOn()
{
    return _is_click;
}


/*
::::::::::::::::::  :   :   :   
::::::::::::::::::  :   :   :
::::::::::::::::::  :   :   :
*/
Graphic::Button::Button(char const *str, Vector2 pos, Vector2 size,
Color color1, Color color2, Color color3, bool (*action) (void)) : _rect(pos, size), name(str), 
_text(str, pos.x, pos.y, 70, BLACK)
{
    _colors.push_back(color1);
    _colors.push_back(color2);
    _colors.push_back(color3);
    _mouse_pos = {0, 0};
    _action = action;
    _is_click = false;

    _list_select.push_back(std::make_unique<Btns>("1", Vector2{730, pos.y}, Vector2{60, 60}, YELLOW, (Color){ 240, 70, 90, 255 }, BLUE, first));
    _list_select.push_back(std::make_unique<Btns>("2", Vector2{830, pos.y}, Vector2{60, 60}, YELLOW, (Color){ 240, 70, 90, 255 }, BLUE, second));
    _list_select.push_back(std::make_unique<Btns>("3", Vector2{930, pos.y}, Vector2{60, 60}, YELLOW, (Color){ 240, 70, 90, 255 }, BLUE, third));
    _list_select.push_back(std::make_unique<Btns>("4", Vector2{1030, pos.y}, Vector2{60, 60}, YELLOW, (Color){ 240, 70, 90, 255 }, BLUE, fourth));
}

Graphic::Button::~Button(){
    // UnloadSound(_fxButton);
}

bool Graphic::Button::Frame()
{
    bool tmp = Update();
    Draw();
    _text.Draw();
    return tmp;
}

bool Graphic::Button::Update()
{
    _mouse_pos = GetMousePosition();
    if (CheckCollisionPointRec(_mouse_pos, _rect.Get()) && _is_click != true) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            _state = 2;
            _is_click = true;
            return _action();
        } else if (!_is_click)
            _state = 1;
    } else if (CheckCollisionPointRec(_mouse_pos, _rect.Get()) && _is_click == true) {
        // _state = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            std::cout << "false\n";
            _state = 1;
            _is_click = false;
        } else if (!_is_click)
            _state = 1;
    } else if (_is_click != true)
        _state = 0;
    return true;
}

void Graphic::Button::Off()
{
    _state = 0;
    _is_click = false;
}

void Graphic::Button::Draw()
{
    _rect.Draw(_colors[_state]);
    int mode = NOTHING;

    if (!_is_click)
        return ;
    for (int i = 0; i < _list_select.size(); i++) {
        mode =  _list_select[i].get()->Frame();
        if (mode == MODE_1) {
            _mode1 = true;
            _mode2 = false;
            _mode3 = false;
            _mode4 = false;
        }
        if (mode == MODE_2) {
            _mode2 = true;
            _mode1 = false;
            _mode3 = false;
            _mode4 = false;
        }
        if (mode == MODE_3) {
            _mode1 = false;
            _mode2 = false;
            _mode3 = true;
            _mode4 = false;
        }
        if (mode == MODE_4) {
            _mode1 = false;
            _mode2 = false;
            _mode3 = false;
            _mode4 = true;
        }
        if (_list_select[i].get()->IsOn()) {
            for (int y = 0; y < _list_select.size(); y++) {
                if (i != y)
                    _list_select[y].get()->Off();
            }
        }
    }
}

bool Graphic::Button::IsOn()
{
    return _is_click;
}

Graphic::Menu::Menu() : _btn_play("PLAY", Vector2{790, 650}, Vector2{190, 60}, RED, (Color){ 240, 70, 90, 255 }, BLUE, close_menu), _active(true)
{
    // ShowCursor();
    EnableCursor();
    _btns_players.push_back(std::make_unique<Button>("PLAYEUR 1", Vector2{30, 30}, Vector2{400, 60}, RED, (Color){ 240, 70, 90, 255 }, BLUE, func));
    _btns_players.push_back(std::make_unique<Button>("PLAYEUR 2", Vector2{30, 100}, Vector2{400, 60}, RED, (Color){ 240, 70, 90, 255 }, BLUE, func));
    _btns_players.push_back(std::make_unique<Button>("PLAYEUR 3", Vector2{30, 170}, Vector2{400, 60}, RED, (Color){ 240, 70, 90, 255 }, BLUE, func));
    _btns_players.push_back(std::make_unique<Button>("PLAYEUR 4", Vector2{30, 240}, Vector2{400, 60}, RED, (Color){ 240, 70, 90, 255 }, BLUE, func));
}

Graphic::Menu::~Menu()
{
}


bool Graphic::Menu::IsOn()
{
    return _active;
}

int Graphic::Menu::Draw()
{
    for (int i = 0; i < _btns_players.size(); i++) {
        _btns_players[i].get()->Frame();
        if (_btns_players[i].get()->IsOn()) {
            for (int y = 0; y < _btns_players.size(); y++) {
                if (i != y)
                    _btns_players[y].get()->Off();
            }
        }
    }
    if (!_btn_play.Frame()){
        _active = false;
        std::cout << "close\n";
        return GAME;
    }
    return MENU;
}

void Graphic::Menu::GetInfoMenu(std::array<std::vector<char>, 4>& touch)
{   
    for (int i = 0; i < _btns_players.size(); i++) {
        if (_btns_players[i].get()->GetMode1())
            touch[i] = {'m', 'w', 'x', 'z', 's', 'q', 'd'};    
        if (_btns_players[i].get()->GetMode2())     
            touch[i] = {'m', 'w', 'x', 't', 'g', 'f', 'h'};
        if (_btns_players[i].get()->GetMode3()){     
            std::cout << "manette\n";
            touch[i] = {'0', '0', '0', '0', '0', 'q', 'd'};}
        if (_btns_players[i].get()->GetMode4())     
            std::cout << "player" << i << "mode 4\n";
    }
}