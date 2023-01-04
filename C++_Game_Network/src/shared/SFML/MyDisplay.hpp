/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran [WSL : Ubuntu-20.04]
** File description:
** Display.hpp Display Class, SFML draw every drawable in a given registry
** Safe Display, can interact with a threaded event manager
*/

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

// SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <unistd.h>

// Containers
#include <vector>
#include <queue>
#include <map>
#include <tuple>
#include <optional>

// Threading
#include <mutex>

// Custom
#include "registry.hpp"
#include "components.hpp"
#include "SendPacket.hpp"

enum input_key
{
    UP,
    RIGHT,
    DOWN,
    LEFT,
    ESC,
    SPACE,
    NIL
};

struct dirctionsValues
{
    dirctionsValues() = default;
    dirctionsValues(int _y, int _x) : y{_y}, x{_x} {};
    // Copy constructor
    dirctionsValues(const dirctionsValues &p1) : y{p1.y}, x{p1.x} {};
    int y;
    int x;
};

class MyDisplay
{
private:
    sf::RenderWindow _render;
    sf::Event _event;

    // input queue
    // std::mutex mtx;
    std::queue<input_key> inputQueue;

    // Caching, stop calling ref all of the time !!

    sf::Clock _in_frame;
    sf::Time _elapsdif;

    std::map<sf::Keyboard::Key, input_key> _associative_mapping{
        {sf::Keyboard::Right, input_key::RIGHT},
        {sf::Keyboard::Left, input_key::LEFT},
        {sf::Keyboard::Up, input_key::UP},
        {sf::Keyboard::Down, input_key::DOWN},
        {sf::Keyboard::Escape, input_key::ESC},
        {sf::Keyboard::Space, input_key::SPACE},
        // add associative binded controls
    };
    std::vector<sf::Keyboard::Key> _possible_input{
        sf::Keyboard::Right,
        sf::Keyboard::Left,
        sf::Keyboard::Up,
        sf::Keyboard::Down,
        sf::Keyboard::Escape,
        sf::Keyboard::Space,
        // add keys here if needed
    };

    double _fps;
    double _fmetime;
    double _speedcoef;
    double _temp;
    double _get;

    input_key key_call(sf::Event::KeyEvent key)
    {
        if (this->_associative_mapping.end() != this->_associative_mapping.find(key.code))
            return _associative_mapping[key.code];
        else
            return input_key::NIL;
    }

    /**
     * @brief layers the objects to be draw by their layer_s
     * returns a sorted list by layers of entity to be drawn
     *
     * Performance might get affected.
     * @param _regis
     * @return std::vector<std::tuple<std::optional<position_t>, std::optional<drawable_t>, std::optional<sprite_t>>>
     */
    std::vector<std::tuple<std::optional<position_t>, std::optional<drawable_t>, std::optional<sprite_t>>> LayerManagement(registry &_regis)
    {
        using position = std::optional<position_t>;
        using backup = std::optional<drawable_t>;
        using spr = std::optional<sprite_t>;

        auto &drawable = _regis.get_components<drawable_t>();
        auto const &pos = _regis.get_components<position_t>();
        auto &sprit = _regis.get_components<sprite_t>();
        auto const &layer_list = _regis.get_components<layer_s>();

        std::vector<std::tuple<position, backup, spr>> layers;
        size_t max_layer = 0;

        for (size_t i = 0; i < layer_list.size(); i += 1)
        {
            if (layer_list[i].has_value() && layer_list[i]->_layer > max_layer)
            {
                max_layer = layer_list[i]->_layer;
            }
        }
        for (size_t layer = 0; layer < max_layer; layer += 1)
        {
            for (size_t i = 0; i < drawable.size() && i < pos.size(); i += 1)
            {
                if (layer_list[i].has_value() && layer_list[i]->_layer == layer)
                {
                    layers.push_back(std::make_tuple(pos[i], drawable[i], (sprit.size() > i) ? sprit[i] : std::nullopt));
                }
            }
        }
        for (size_t i = 0; i < drawable.size() && i < pos.size(); i += 1)
        {
            if (!layer_list[i].has_value())
            {
                layers.push_back(std::make_tuple(pos[i], drawable[i], (sprit.size() > i) ? sprit[i] : std::nullopt));
            }
        }
        return layers;
    }

    /**
     * @brief draw all drawable entities based on the layered list
     *
     * @param layered_drawable
     */
    void draw_layers(std::vector<std::tuple<std::optional<position_t>, std::optional<drawable_t>, std::optional<sprite_t>>> layered_drawable)
    {
        for (size_t i = 0; i < layered_drawable.size(); i += 1)
        {
            std::optional<position_t> curr_pos = std::get<0>(layered_drawable[i]);
            std::optional<drawable_t> curr_drawable = std::get<1>(layered_drawable[i]);
            std::optional<sprite_t> curr_sprite = std::get<2>(layered_drawable[i]);
            if (curr_pos.has_value())
            {
                sf::Vector2f ps(static_cast<short>(curr_pos->x), static_cast<short>(curr_pos->y));
                if (curr_sprite.has_value())
                {
                    curr_sprite->sprite.setPosition(ps);
                    this->_render.draw(curr_sprite->sprite);
                }
                else if (curr_drawable.has_value())
                {
                    curr_drawable->_shape.setPosition(ps);
                    curr_drawable->draw(_render);
                }
            }
        }
    }

    /**
     * @brief dumb Draw Registry, draw everything that has Drawable_t and position_t component
     * you can add a sprite_t component to an drawable entity and it'll be draw with that sprite_t
     *
     * @param _regis
     */
    void draw_registre(registry &_regis)
    {
        auto &drawable = _regis.get_components<drawable_t>();
        auto const &pos = _regis.get_components<position_t>();
        auto &sprit = _regis.get_components<sprite_t>();
        auto &text = _regis.get_components<textBox_t>();
        auto &size = _regis.get_components<size_entity_s>();

        for (size_t i = 0; i < drawable.size(); i += 1)
        {
            if (pos[i].has_value())
            {
                sf::Vector2f ps(static_cast<short>(pos[i]->x), static_cast<short>(pos[i]->y));
                if (sprit.size() > i && sprit[i].has_value() && sprit.at(i).getIsValid())
                {
                    sprit[i]->sprite.setPosition(ps);
                    sprit[i]->animate();
                    this->_render.draw(sprit[i]->sprite);
                }
                else if (text.size() > i && (text[i]).has_value())
                {
                    text[i]->txt1.setPosition(ps);
                    this->_render.draw(text[i]->txt1);
                }
                else if ((drawable[i]).has_value())
                {
                    // sf::FloatRect fst(pos[idx]->x, pos[idx]->y, size[idx]->size, size[idx]->size);
                    sf::FloatRect sd(pos[i]->x, pos[i]->y, size[i]->size, size[i]->size);
                    drawable[i]->_shape.setPosition(ps);
                    drawable[i]->draw(_render);
                }
            }
        }
    }

public:
    /**
     * @brief return a queue of all the key pressed event
     *
     * @return std::queue<input_key>& queue of all the key pressed
     */
    std::queue<input_key> &eventQueue()
    {
        while (this->_render.pollEvent(this->_event))
        {
            if (this->_event.type == sf::Event::Closed)
                _render.close();
            if (this->_event.type == sf::Event::KeyPressed)
            {
                inputQueue.push(key_call(this->_event.key));
            }
        }
        return inputQueue;
    }

    /**
     * @brief clear the queue of event
     *
     */
    void clearEventQueue()
    {
        std::queue<input_key> empty;
        std::swap(this->inputQueue, empty);
    }

    input_key keycatch()
    {
        for (size_t i = 0; i < this->_possible_input.size(); i += 1)
        {
            if (sf::Keyboard::isKeyPressed(this->_possible_input.at(i)))
            {
                return this->_associative_mapping[this->_possible_input.at(i)];
            }
        }
        return input_key::NIL;
    }

    std::queue<input_key> &get_inputQueue()
    {
        return (this->inputQueue);
    }

    explicit MyDisplay(int x, int y, double fps)
    {
        this->_render.create(sf::VideoMode(x, y), "R-Type");
        this->_render.setFramerateLimit(fps);
        this->_fmetime = 1000 / fps;
    }

    ~MyDisplay()
    {
        this->_render.close();
    }

    bool win_is_open() const
    {
        return _render.isOpen();
    }

    /**
     * @brief takes a registry, and draws, iteration by iteration
     * any object that are to be drawn should pocess at least:
     *      - a drawable_s component
     *      - a position_s component
     *
     * @param _regis
     */
    void ite(registry &_regis)
    {
        this->_event = sf::Event();

        if (this->_get > 0)
            usleep(this->_elapsdif.asMicroseconds());
        this->_in_frame.restart();

        this->clearEventQueue();
        this->_render.clear();
        this->draw_registre(_regis);
        this->_render.display();
        this->eventQueue();

        this->_elapsdif = this->_in_frame.getElapsedTime();
        this->_temp = this->_elapsdif.asMilliseconds();
        this->_get = this->_fmetime - this->_temp;
        if (this->_get < 0)
            this->_speedcoef = abs(this->_get / this->_fmetime);
    }

    size_t buttonPressed(registry &_regis)
    {
        auto &buttonArray = _regis.get_components<button_t>();
        auto &spritesArray = _regis.get_components<sprite_t>();
        size_t i = 0;
        // if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        // sf::Vector2f Mouse = _render.mapPixelToCoords(sf::Mouse::getPosition(_render));
        // std::cout << "Mouse.x = " << Mouse.x << ", Mouse.y = " << Mouse.y << std::endl;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
        {
            for (; i < spritesArray.size() && i < buttonArray.size(); i++)
            {
                if (spritesArray[i].has_value())
                {
                    spritesArray.at(i).sprite.getGlobalBounds();
                    sf::Vector2f g(sf::Mouse::getPosition(_render).x, sf::Mouse::getPosition(_render).y);
                    if (buttonArray[i].has_value() && spritesArray.at(i).sprite.getGlobalBounds().contains(g))
                    {
                        std::cout << "colision" << std::endl;
                        return (size_t(i));
                    }
                }
            }
        }
        return (i = 42);
    }

    sf::RenderWindow &getWindow() { return (_render); }
};

#endif /* !DISPLAY_HPP_ */
