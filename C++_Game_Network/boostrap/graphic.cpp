/*
** EPITECH PROJECT, 2022
** boostrap
** File description:
** graphic
*/

#include <vector>
#include <iostream>
#include <optional>
#include "SparseArray.hpp"
#include "boostrap.hpp"
#include "step3.hpp"

void draw_registre(sf::RenderWindow &window, registry &r);
void create_register(registry &r);


int main()
{

    registry r;
    create_register(r);
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
 
    sf::Texture texture;
    if (!texture.loadFromFile("../assets/images/background.jpg"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    sf::Font font;
    if (!font.loadFromFile("../assets/fonts/bradley-gratis/BradleyGratis.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("../assets/sounds/music.ogg"))
        return EXIT_FAILURE;
    // Play the music
    music.play();
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        draw_registre(window, r);
        // window.draw(sprite);
        // window.draw(text);
        window.display();
    }
    return EXIT_SUCCESS;
}