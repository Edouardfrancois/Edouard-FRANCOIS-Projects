/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** step3
*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#ifndef STEP3_HPP_
#define STEP3_HPP_

typedef struct position_s
{
    int x;
    int y;
} position_t;

typedef struct velocity_s
{
    float x;
    float y;
} velocity_t;

typedef struct drawable_s
{
    explicit drawable_s(int size, sf::Color color) : _shape(50, size)
    {
        _shape.setFillColor(color);
    }
    void draw(sf::RenderWindow &window) const
    {
        window.draw(_shape);
    }

    sf::CircleShape _shape;
} drawable_t;

typedef struct controllable_s
{
    // void moove(position_t pos) {
    //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    //         pos.x -= 10;
    //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    //         pos.x += 10;
    //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    //         pos.y += 10;
    //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    //         pos.y -= 10;
    // }
} controllable_t;

#endif /* !STEP3_HPP_ */