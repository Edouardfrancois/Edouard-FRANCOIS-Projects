#include <iostream>
#include <SFML/Graphics.hpp>
#include "texbox.hpp"
#include "button.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "R-type");
    window.setFramerateLimit(60);

    window.setKeyRepeatEnabled(true);
    sf::Font Arcane;
    Arcane.loadFromFile("04B_30__.TTF");
    Textbox textbox1(50, false);
    textbox1.setFont(Arcane);
    textbox1.setPosition({420,320});
    textbox1.setLimit(true, 10);
    sf::Vector2f sz;
    sz.x = 1;
    sz.y = 1;
    Button btn1(sz);
    btn1.setPosition({280,180});
    
    while (window.isOpen())
    {
        sf::Event Event;
        while (window.pollEvent(Event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                textbox1.setSelected(true);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                textbox1.setSelected(false);
            }
            switch (Event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::TextEntered:
                    textbox1.typeOn(Event);
                    break;
                case sf::Event::MouseMoved:
                    if(btn1.isMouseOver(window)) {
                        btn1.setScale({0.99,0.99});
                    }
                    else {
                        btn1.setScale(sz);
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if (btn1.isMouseOver(window))
                        std::cout << "you clicked\n";
            }
        } 
        //render
        window.clear();
        btn1.drawTo(window);
        textbox1.drawTo(window);
        window.display();
    }
    return 0;
}