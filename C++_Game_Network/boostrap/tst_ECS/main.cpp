/*
** EPITECH PROJECT, 2022
** boostrap
** File description:
** main
*/

#include <vector>
#include <iostream>
#include <optional>
#include "../SparseArray.hpp"
#include "../boostrap.hpp"
#include "components.hpp"

void draw_registre(sf::RenderWindow &window, registry &r);
void create_register(registry &r);

using texture_array = std::vector<sf::Texture>;
texture_array create_texture_array(texture_array &txt);

void create_register(registry &r);

void create_entity_1(registry &r, sf::Texture texture);
void create_entity_2(registry &r, sf::Texture texture);
void create_entity_3(registry &r, sf::Texture texture);



void draw_registre(sf::RenderWindow &window, registry &r) {
    auto const &drawable = r.get_components<drawable_t>();
    auto const &pos = r.get_components<position_t>();
    auto &sprite = r.get_components<sprite_t>();

    for (size_t i = 0 ; i < drawable.size(); i++) {
        if (drawable[i] && pos[i] && sprite[i]) {
            sprite[i]->sprite.setScale(0.5, 0.5);
            sprite[i]->sprite.setPosition(pos[i]->x, pos[i]->y);
            window.draw(sprite[i]->sprite);
        }
    }
}


int main()
{
    
    texture_array txt;
    registry r;
    
    create_texture_array(txt);
    // create_register(r);
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    create_entity_1(r, txt[1]);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        draw_registre(window, r);
        // window.draw(sf::Sprite(txt[0]));
        // window.draw(sprite1);
        // window.draw(sprite2);
        // window.draw(sprite3);
        // window.draw(text);
        window.display();
    }
    return EXIT_SUCCESS;
}