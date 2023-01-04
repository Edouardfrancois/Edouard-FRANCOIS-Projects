/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** StaticElem
*/

#ifndef STATICELEM_HPP_
#define STATICELEM_HPP_

#include "IObject.hpp"
#include "Model.hpp"
#include "Timer.hpp"

/**
 * @brief Pevent etre casse par des bombes
 * 
 */
class Block : public IObject {
    public:
        Block(size_t x, size_t y) : IObject(ObjType::OBJBLOC, x, y) {};
        ~Block() = default;
};

/**
 * @brief Ne peuve pas etre casse
 * 
 */
class Wall : public IObject {
    public:
        Wall(size_t x, size_t y) : IObject(ObjType::OBJWALL, x, y) {};
        ~Wall() = default;
};

/**
 * @brief Bomb
 * 
 */
class Bomb : public IObject {
    public:
        Bomb(size_t x, size_t y);
        ~Bomb() = default;
    public:
        Timer TimerExplose;
        MyRaylib::MyModel Model;
        
};

/**
 * @brief La zones cree par la bombe qui fait des dega
 * 
 */
class Fire : public IObject {
    public:
        Fire(size_t x, size_t y) : IObject(ObjType::OBJFIRE, x, y), Model("assets/indie_fire_model.iqm", "assets/Fire_indie.png") {
            this->TimerExplose.Start();
        };
        ~Fire() = default;
    public:
        Timer TimerExplose;
        MyRaylib::MyModel Model;
        
};

/**
 * @brief Bonus qui permet d'aller plus vite
 * 
 */
class Spead : public IObject {
    public:
        Spead(size_t x, size_t y) : IObject(ObjType::OBJSPEED, x, y) {};
        ~Spead() = default;
};

/**
 * @brief Heal qui permet d'avoir une vie en plus si il nous en manque
 * 
 */
class Heal : public IObject {
    public:
        Heal(size_t x, size_t y) : IObject(ObjType::OBJHEAL, x, y) {};
        ~Heal() = default;
};

/**
 * @brief Point de spawn
 * 
 */
class Spawn : public IObject {
    public:
        Spawn(size_t x, size_t y) : IObject(ObjType::OBJSPAWN, x, y) {};
        ~Spawn() = default;
};



#endif /* !STATICELEM_HPP_ */
