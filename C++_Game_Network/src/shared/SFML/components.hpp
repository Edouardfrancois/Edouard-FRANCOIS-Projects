/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** step3
*/

#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <uuid/uuid.h>
#include <optional>
#include <functional>
#include <iostream>
#include <chrono>

#ifndef STEP3_HPP_
#define STEP3_HPP_

#include "EntityId.hpp"
#include "Manage_Asset.hpp"

static const int TYPE_PLAYER = 0;
static const int TYPE_MONSTER = 1;
static const int TYPE_BULLET = 2;

typedef struct position_s
{
    double x;
    double y;
} position_t;

typedef struct velocity_s
{
    float Velocity;
} velocity_t;

// typedef struct curv_s
// {

// }

typedef struct move_s
{
    float Degree;
    u_short Velocity;
} move_t;

typedef struct my_id_s
{
    entity_id_e id;
} my_id_t;

typedef struct particule_s
{
} particule_t;

typedef struct drawable_s
{
    explicit drawable_s(int size, sf::Color color, int points) : _shape(size, points)
    {
        _shape.setFillColor(color);
    }
    void draw(sf::RenderWindow &window)
    {
        hitBox = _shape.getGlobalBounds();
        window.draw(_shape);
    }

    sf::CircleShape _shape;

    sf::FloatRect hitBox = _shape.getGlobalBounds();
} drawable_t;

typedef struct hit_box_s
{
    // hit_box_s(drawable_t &master) : master_hitBox(master.hitBox) {
    //
    // }
    // sf::FloatRect &master_hitBox;
} hit_box_t;

typedef struct controllable_s
{
} controllable_t;

/**
 * @brief Contains a sprite and a shared to the texture.
 *
 */
typedef struct sprite_s
{
    sprite_s(Manage_Asset &man, std::string src)
    {
        this->_is_animated = false;
        std::cerr << "== Sprite_t: Loading... " << src << std::endl;
        this->spriteTex = man.loadText(src, IDtexture); // Create Asset or link to an existing Asset
        if (this->spriteTex.get() != nullptr)
        {
            std::cerr << "=/ Sprite_t: Loaded successfully " << src << std::endl;
            this->_dimension = spriteTex.get()->getSize();
            this->sprite.setTextureRect((sf::IntRect){0, 0, this->_dimension.x, this->_dimension.y});
            this->sprite.setTexture(*(spriteTex.get()), true); // set Texture
            this->_is_valid = true;
        }
    }

    /**
     * @brief sets up the animation path on the texture
     * will go left to right then bottom
     *
     * @param topLeft top left point of your texture rectangle
     * @param bottomRight bottome right of your texture rectangle
     * @param stepX for every iteration how much should the texture rectangle move to the right
     * @param stepY when it reached the rightest point of the texture how much should the texture rectangle go down
     * @param nb_frame the totale number of frames your animation should have.
     */
    void setupAnime(position_t topLeft, position_t bottomRight, int stepX, int stepY, int nb_frame)
    {
        this->_is_animated = true;

        this->_texRect = sf::IntRect(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
        this->_steps = sf::Vector2i(stepX, stepY);
        this->_nb_frame = nb_frame;
        this->sprite = sf::Sprite(*(spriteTex.get()), this->_texRect);
    }

    /**
     * @brief animates the sprite, to be called before each draw
     *
     */
    void animate()
    {
        if (_is_animated == false)
            return;
        if (this->_curr_frame > this->_nb_frame)
        {
            this->_texRect.top = 0;
            this->_texRect.left = 0;
            this->_curr_frame = 0;
        }

        int currWidth = (this->_texRect.left + this->_texRect.width);
        int currHeight = (this->_texRect.top + this->_texRect.height);
        int maxWidth = this->_dimension.x;
        int maxHeight = this->_dimension.y;

        this->_texRect.left += this->_steps.x;
        // this->_texRect = sf::IntRect((sf::Vector2i){this->_texRect.left + this->_steps.x, this->_texRect.top}, (sf::Vector2i){this->_texRect.width, this->_texRect.height});
        if (currWidth > maxWidth)
        {
            this->_texRect.top += this->_steps.y;
            this->_texRect.left = 0;
        }
        if (currHeight > maxHeight)
            this->_texRect.top = 0;
        this->sprite.setTextureRect(this->_texRect);
        this->_curr_frame += 1;
    }

    /**
     * @brief returns true if the sprite is animated
     *
     * @return true
     * @return false
     */
    bool getIsAnimated() const
    {
        return this->_is_animated;
    }

    /**
     * @brief returns true if the sprite is valid
     *
     * @return true
     * @return false
     */
    bool getIsValid() const
    {
        if (!this->_is_valid)
        {
            std::cerr << "COMPONENT SPRITE_T : Texture couldn't be loaded leading the sprite to be invalid" << std::endl;
        }
        return this->_is_valid;
    }

private:
    // for animation
    int _nb_frame = 0;
    int _curr_frame = 0;
    bool _is_animated = false;
    sf::Vector2u _dimension;
    sf::Vector2i _steps;
    sf::IntRect _texRect;

    // utility containers
    size_t IDtexture;
    std::shared_ptr<sf::Texture> spriteTex;
    bool _is_valid = false;

public:
    // sprite
    sf::Sprite sprite;
} sprite_t;

typedef struct player_uuid_s
{
    uuid_t uuid;
} player_uuid_t;

typedef struct balle_s
{
} balle_t;

typedef struct size_entity_s
{
    size_t size;
} size_entity_t;

typedef struct HP_s
{
    int hp;
} HP_t;

typedef struct is_monster_s
{
    float ground;
    float entendue;
} is_monster_t;

typedef struct is_wall_s
{
} is_wall_t;

typedef struct type_entity_s
{
    int type;
} type_entity_t;

struct layer_s
{
    layer_s(size_t layer)
    {
        this->_layer = layer;
    }
    size_t _layer;
};

typedef struct powerfull_s
{
    int powerfull;
} powerfull_t;

typedef struct update_to_client_s
{
} update_to_client_t;




typedef struct clock_for_updt_s
{
    std::chrono::steady_clock::time_point start;
} clock_for_updt_t;

typedef struct textBox_s
{
    textBox_s(const textBox_s &example)
    {
        std::cerr << "TEXT BOX : making a copy..." << std::endl;
        this->charSize = example.charSize;
        this->sourceFont = example.sourceFont;
        this->txt1 = example.txt1;
        this->textbox = example.textbox;
        this->color = example.color;
        if (!this->font.loadFromFile(this->sourceFont))
            std::cerr << "FAILURE TEXT BOX: FONT COULD NOT BE LOADED" << std::endl;
        this->txt1.setColor(this->color);
        this->txt1.setFont(this->font);
        this->txt1.setCharacterSize(this->charSize);
    }

    textBox_s(const std::string &sourceFont, float sizePixel, sf::Color color)
    {
        this->sourceFont = sourceFont;
        this->charSize = sizePixel;
        this->color = color;
        if (!this->font.loadFromFile(sourceFont))
            std::cerr << "FAILURE TEXT BOX: FONT COULD NOT BE LOADED" << std::endl;
        else
        {
            std::cerr << "settings up" << std::endl;
            this->txt1.setFont(this->font);
            this->txt1.setColor(color);
            this->txt1.setCharacterSize(sizePixel); // in pixels, not points!
        }
    };

    void setText(std::string txt) { txt1.setString(txt); }
    void setColor(sf::Color color)
    {
        txt1.setFillColor(color);
        this->color = color;
    }
    void setSize(float size)
    {
        txt1.setCharacterSize(size);
        this->charSize = size;
    }

    sf::Color color;
    float charSize;
    std::string sourceFont;
    sf::Font font;
    sf::Text textbox;
    sf::String playerInput;
    sf::Text txt1;
} textBox_t;

#endif /* !STEP3_HPP_ */