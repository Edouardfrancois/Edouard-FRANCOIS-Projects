#include "SFML/Graphics.hpp"
#include <iostream>

int main(int argc, char ** argv){
  sf::RenderWindow renderWindow(sf::VideoMode(2557, 1026), "Demo Game");

  sf::Event event;
  sf::Texture texture;
  texture.loadFromFile("sp.png");

  sf::IntRect rectsource(0, 0, 630, 38);
  sf::Sprite sprite(texture, rectsource);
  sprite.setPosition({50,50});

  sf::Clock clock;


  while (renderWindow.isOpen()){
    while (renderWindow.pollEvent(event)){
      if (event.type == sf::Event::EventType::Closed)
        renderWindow.close();
    }
    if (clock.getElapsedTime().asMilliseconds() > 150) {
        if (rectsource.top >= 428) {
            rectsource.top = 0;
            sprite.setTextureRect(rectsource);
            clock.restart();
        }
        else
            rectsource.top += 38;
        sprite.setTextureRect(rectsource);
        clock.restart();
    }

    renderWindow.clear();
    renderWindow.draw(sprite);
    renderWindow.display();
  }
}