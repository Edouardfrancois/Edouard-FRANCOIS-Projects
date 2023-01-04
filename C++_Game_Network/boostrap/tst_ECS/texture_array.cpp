/*
** EPITECH PROJECT, 2022
** boostrap
** File description:
** texture_array
*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <vector>

using texture_array = std::vector<sf::Texture>;

texture_array create_texture_array(texture_array &txt) {

    txt.push_back(sf::Texture());
    txt[0].loadFromFile("../../assets/images/monter.png");
    
    txt.push_back(sf::Texture());
    txt[1].loadFromFile("../../assets/images/ship.png");
    
    txt.push_back(sf::Texture());
    txt[2].loadFromFile("../../assets/images/space_ship.png");

    return txt;
}

