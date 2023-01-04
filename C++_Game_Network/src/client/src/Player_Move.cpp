#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

sf::RenderWindow window;

/**
 * @brief Clear and Draw the window
 * 
 */
void draw()
{
    window.clear();
    window.display();
}

void input(bool fullscreen)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        window.close();
        // fonction move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        window.close();
        // fonction move right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        window.close();
        // fonction move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        window.close();
        // fonction move down
}

void update()
{

}

int main()
{
    window.create(sf::VideoMode::getFullscreenModes()[0], "R-Type");
    window.setFramerateLimit(60);
    bool fullscreen = 0;

    while (window.isOpen()) {
        draw();
        input(fullscreen);
        update();
    }
}


// Player_Move::Player_Move()
// {
// }

// Player_Move::~Player_Move()
// {
// }
