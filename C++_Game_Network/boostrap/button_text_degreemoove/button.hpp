#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
 public:
    Button() { }

    Button(sf::Vector2f size)
    {
        texture.loadFromFile("button2.png");
        button.setTexture(texture);
        button.setScale(size);
    }

    void setScale(sf::Vector2f sz)
    {
        button.setScale(sz);
    }

    void setPosition(sf::Vector2f pos)
    {
        button.setPosition(pos);
    }

    void drawTo(sf::RenderWindow &window)
    {
        window.draw(button);
    }

    bool isMouseOver(sf::RenderWindow &window)
    {
        int mousex = sf::Mouse::getPosition(window).x;
        int mousey = sf::Mouse::getPosition(window).y;

        float btnposx = button.getPosition().x;
        float btnposy = button.getPosition().y;

        float btnxposwidth = button.getPosition().x + 770;
        float btnyposheight = button.getPosition().y + 345;

        if (mousex < btnxposwidth && mousex > btnposx && mousey < btnyposheight && mousey > btnposy)
            return true;
        return false;
    }

 private:
    sf::Texture texture;
    sf::Sprite button;
}; 