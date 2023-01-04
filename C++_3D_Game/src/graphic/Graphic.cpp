/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Graphic
*/

#include "Graphic.hpp"
#include "StaticElem.hpp"

Graphic::Graphic::Graphic() : _raylib(1480, 1020, 60, "teste title"), 
_idx_camera(0), _music("assets/soeur-sourire-dominique.mp3"), _anim("assets/indie_bomberman_walk_animation.iqm")
{
    _music.Play();
    _music.SetVolume(2);
    _cameras.push_back(MyRaylib::Camera());
}

Graphic::Graphic::~Graphic()
{
}

void Graphic::Graphic::SetUp(size_t x, size_t y, Json::Json& str_texture)
{
    _map_size_x = x;
    _map_size_y = y;
    
    for (size_t i = 0; i < str_texture.GetSize(); i++) {
        std::cout << "debug ->" << str_texture[i].GetData<std::string>() << "\n";
        // MyRaylib::Texture texture(str_texture[i].GetData<std::string>().c_str())
        _texture.push_back(MyRaylib::Texture(str_texture[i].GetData<std::string>().c_str()));
    }
}

MyRaylib::Action Graphic::Graphic::Frame(const TAllMap& map)
{
    MyRaylib::Action res = MyRaylib::Action::Nothing;
    if (_raylib.WindowIsOpen() != true)
        return MyRaylib::Action::PickUp; // false
    res = Draw(map);
    _music.Update();
    _cameras[_idx_camera].Update();
    _raylib.Clear();
    if (res == MyRaylib::Action::Menu)
        return MyRaylib::Action::Menu;
    return MyRaylib::Action::Nothing;
}

// bool Graphic::Graphic::Frame(Menu& menu)
// {
//     if (_raylib.WindowIsOpen() != true)
//         return false;
//     _raylib.BeginDrawMode();
//     menu.Draw();
//     _raylib.EndDrawMode();
//     _raylib.Clear();
//     return true;
// }

MyRaylib::Action Graphic::Graphic::Draw(const TAllMap& map)
{
    MyRaylib::Action res = MyRaylib::Action::Nothing;
    _raylib.BeginDrawMode();
    res = Draw3D(map);
    _raylib.EndDrawMode();
    return res;
}

MyRaylib::Action Graphic::Graphic::Draw3D(const TAllMap& map)
{
    MyRaylib::Action res = MyRaylib::Action::Nothing;
    _cameras[_idx_camera].Begin3DDraw();
    _raylib.DrawGround(_map_size_x * _SizeOneMapPiece, _map_size_y * _SizeOneMapPiece);
    res = DrawMap(map);
    _cameras[_idx_camera].End3DDraw();
    return res;
}

MyRaylib::Action Graphic::Graphic::DrawMap(const TAllMap& map)
{
    static float angle = 0;

    for (size_t y = 0; y != _map_size_y; y++) {
        for (size_t x = 0; x != _map_size_x; x++) {
            if (map[y][x].get()->GetPile().empty())
                continue;
            for (const auto& Elem : map[y][x].get()->GetPile()) {
                if (Elem.get()->GetType() == ObjType::OBJBLOC) {
                    _texture[2].DrawCube( \
                        {
                            static_cast<float>(static_cast<float>(Elem.get()->GetPoss().GetX()) - (_map_size_x * (_SizeOneMapPiece / 2))),
                            5,
                            static_cast<float>(static_cast<float>(Elem.get()->GetPoss().GetY()) - (_map_size_y *(_SizeOneMapPiece / 2))),
                        }, static_cast<float>(_SizeOneMapPiece), static_cast<float>(_SizeOneMapPiece), static_cast<float>(_SizeOneMapPiece));
                }
                else if (Elem.get()->GetType() == ObjType::OBJENTITY) {
                    IEntity& Tmp = *dynamic_cast<IEntity *>(Elem.get());
                    if ((Tmp.LastAction.LastAction) == MyRaylib::Action::Right && Tmp.LastAction.turn == true)
                        Tmp.Model.TurnDroite();
                    if ((Tmp.LastAction.LastAction) == MyRaylib::Action::Left && Tmp.LastAction.turn == true)
                        Tmp.Model.TurnLeft();
                    if ((Tmp.LastAction.LastAction) == MyRaylib::Action::Up && Tmp.LastAction.turn == true)
                        Tmp.Model.TurnUp();
                    if ((Tmp.LastAction.LastAction) == MyRaylib::Action::Down && Tmp.LastAction.turn == true)
                        Tmp.Model.TurnDown();
                    Tmp.Model.Draw({static_cast<float>(Tmp.GetPoss().GetX()) - (_map_size_x * (_SizeOneMapPiece / 2)), 
                    static_cast<float>(5), static_cast<float>(Tmp.GetPoss().GetY()) - (_map_size_y * (_SizeOneMapPiece / 2))}, 
                    (Vector3){1, 0, 0}, -90, (Vector3){0.05, 0.05, 0.05}, WHITE);
                    Tmp.Model.Animatinig(_anim);
                }
                else if (Elem.get()->GetType() == ObjType::OBJBOMB) {
                    Bomb& Tmp = *dynamic_cast<Bomb *>(Elem.get());
                    Tmp.Model.Draw({static_cast<float>(Tmp.GetPoss().GetX()) - (_map_size_x * (_SizeOneMapPiece / 2)), 
                    static_cast<float>(0), static_cast<float>(Tmp.GetPoss().GetY()) - (_map_size_y * (_SizeOneMapPiece / 2))}, 
                    (Vector3){ 1, 0, 0}, -90, (Vector3){10, 10, 10}, WHITE);
                }
                else if (Elem.get()->GetType() == ObjType::OBJFIRE) {
                    Fire& Tmp = *dynamic_cast<Fire *>(Elem.get());
                    Tmp.Model.Draw({static_cast<float>(Tmp.GetPoss().GetX()) - (_map_size_x * (_SizeOneMapPiece / 2)), 
                    static_cast<float>(0), static_cast<float>(Tmp.GetPoss().GetY()) - (_map_size_y * (_SizeOneMapPiece / 2))}, 
                    (Vector3){ 1, 0, 0}, -90, (Vector3){9, 9, 9}, WHITE);
                }
            }
        }
    }
    return MyRaylib::Action::Nothing;
}


// Graphic::Character::Character(Vector3 pos, std::string model_name, std::string anim_name) : _model(model_name.c_str()), _animation(anim_name.c_str())
// {
//     _position = pos;
//     _rotation = {0, 0, 0};
//     _scale = {10, 10, 10};
//     _rotation_angle = 1;
//     _color = GOLD;
// }

// Graphic::Character::~Character(){}

// void Graphic::Character::Draw()
// {
//     _model.Draw(_position, _rotation, _rotation_angle, _scale, _color);
//     _model.Animatinig(_animation);
// }

int Graphic::Graphic::MyGame(const TAllMap& map)
{
    MyRaylib::Action res = Frame(map);
    if (res == MyRaylib::Action::PickUp)
        return END;
    if (res == MyRaylib::Action::Menu) {
        std::cout << "menu\n";
        return MENU;
    }
    return GAME;
}

int Graphic::Graphic::MyMenu(std::array<std::vector<char>, 4>& touch)
{
    int result = MENU;
    // std::cout << "menu\n";
    _menu.Active();
    _raylib.BeginDrawMode();
    result = _menu.Draw();
    _raylib.EndDrawMode();
    if (_raylib.WindowIsOpen() == false)
        return END;
    _raylib.Clear();
    if (result == GAME)
        _menu.GetInfoMenu(touch);
    return result;
}

