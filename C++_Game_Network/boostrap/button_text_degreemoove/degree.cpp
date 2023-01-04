/*
** EPITECH PROJECT, 2022
** Epitech
** File description:
** degreemove
*/
#include <SFML/Graphics.hpp>
#include <math.h>

void alterna()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "My Program");
    window.setFramerateLimit(60);
 
    sf::RectangleShape rect;
 
    sf::Vector2f rectanglePosition(640, 360);
 
    rect.setPosition(rectanglePosition);
    rect.setSize(sf::Vector2f(100, 100));
 
    float xVelocity = 0;
    float yVelocity = 0;
    float coeff = 0.02222222;
    float radian = M_PI / 180;
    int degrees = 70;
    float rad_angle = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }
        //"physics"
        rad_angle = degrees * radian;
        xVelocity = cos(rad_angle);
        yVelocity = sin(rad_angle);
        rectanglePosition.x -= xVelocity;
        rectanglePosition.y -= yVelocity;
        if (rectanglePosition.x < 0 || rectanglePosition.x > 1280 - 100) xVelocity *= -1;
        if (rectanglePosition.y < 0 || rectanglePosition.y > 720 - 100) yVelocity *= -1;
        if (degrees > 0 && degrees <= 45) {
        xVelocity = 1;
        yVelocity = degrees * coeff;
        if (degrees == 0)
            yVelocity = 0;
        if (degrees == 45)
            yVelocity = 1;
        rectanglePosition.x -= xVelocity;
        rectanglePosition.y -= yVelocity;
    }
        else if (degrees > 45 && degrees <= 90) {
        yVelocity = 1;
        xVelocity = 1 - (degrees - 45) * coeff;
        if (degrees == 90)
            xVelocity = 0;
        rectanglePosition.y -= yVelocity;
        rectanglePosition.x -= xVelocity;
    }
    // -----------------------------------------------
        else if (degrees > 90 && degrees <= 135) {
        yVelocity = 1;
        xVelocity = 1 - (degrees - 45) * coeff;
        if (degrees == 135)
            xVelocity = 0;
        rectanglePosition.y -= yVelocity;
        rectanglePosition.x += xVelocity;
    }
        else if (degrees > 135 && degrees <= 180) {
        yVelocity = 1;
        xVelocity = 1 - (degrees - 45) * coeff;
        if (degrees == 180)
            yVelocity = 0;
        rectanglePosition.y -= yVelocity;
        rectanglePosition.x -= xVelocity;
    }
    // -------------------------------------------------
        else if (degrees > 180 && degrees <= 225) {
        yVelocity = 1;
        xVelocity = 1 - (degrees - 45) * coeff;
        if (degrees == 225)
            yVelocity = 0;
        rectanglePosition.y += yVelocity;
        rectanglePosition.x += xVelocity;
    }
        else if (degrees > 225 && degrees <= 270) {
        yVelocity = 1;
        xVelocity = 1 - (degrees - 45) * coeff;
        if (degrees == 270)
            yVelocity = 0;
        rectanglePosition.y += yVelocity;
        rectanglePosition.x += xVelocity;
    }
    // --------------------------------------------------
            else if (degrees > 270 && degrees <= 315) {
        yVelocity = 1;
        xVelocity = 1 - (degrees - 45) * coeff;
        if (degrees == 315)
            yVelocity = 0;
        rectanglePosition.y += yVelocity;
        rectanglePosition.x += xVelocity;
    }
        else if (degrees > 315 && degrees <= 360) {
        xVelocity = 1;
        yVelocity = 1 - ((degrees - 270) * coeff);
        if (degrees == 360)
            yVelocity = 0;
        rectanglePosition.y += yVelocity;
        rectanglePosition.x -= xVelocity;
    }
        rect.setPosition(rectanglePosition);
 
        //render
        window.clear();
        window.draw(rect);
        window.display();
    }
    return;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "My Program");
    window.setFramerateLimit(60);
 
    sf::RectangleShape rect;
 
    sf::Vector2f rectanglePosition(640, 360);
 
    rect.setPosition(rectanglePosition);
    rect.setSize(sf::Vector2f(100, 100));
 
    float xVelocity = 0;
    float yVelocity = 0;
    float coeff = 0.02222222;
    float radian = M_PI / 180;
    int degrees = 90;
    int velocity = 2;
    float rad_angle = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }
        if (degrees < 0)
            degrees = degrees - 360;
        //"physics"
        rad_angle = degrees * radian;
        xVelocity = cos(rad_angle);
        yVelocity = sin(rad_angle);
        rectanglePosition.x -= xVelocity * velocity;
        rectanglePosition.y -= yVelocity * velocity;

        rect.setPosition(rectanglePosition);
 
        //render
        window.clear();
        window.draw(rect);
        window.display();
    }
    return 0;
}