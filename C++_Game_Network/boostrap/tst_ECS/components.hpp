/*
** EPITECH PROJECT, 2022
** boostrap
** File description:
** components
*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

typedef struct position_s {
    int x;
    int y;
} position_t;

typedef struct velocity_s {
    float x;
    float y;
} velocity_t;

typedef struct drawable_s {
} drawable_t;

typedef struct controllable_s {
} controllable_t;

typedef struct size__s {
    size_t size;
} size__t;

typedef struct sprite_s {
    sf::Sprite sprite;
} sprite_t;

typedef struct healt_point_s {
    int life;
} healt_point_t;

typedef struct cliquable_s {
    // Mettre une box 
    /* Une action a faire en cas de clique, sois un std::function 
sois (ce qui est le mieux) une string à envoyer à un gestionnaire d'évenement. */
} cliquable_t;

#endif /* !COMPONENTS_HPP_ */