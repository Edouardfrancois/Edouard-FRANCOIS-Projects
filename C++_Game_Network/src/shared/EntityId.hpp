/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** EntityId
*/

#include <SFML/Graphics/Color.hpp>


#ifndef ENTITYID_HPP_
#define ENTITYID_HPP_

static const float VELOCITY_GAME = -9;

static const int SIZE_PLAYER_BULLET = 5;
static const int SIZE_MOB_BULLET = 10;
static const int SIZE_MOB_lv0 = 80;


static const sf::Color COLOR_MOB_lv0 = {192, 174, 245, 255};
static const sf::Color COLOR_BULLET_MOB = {100, 100, 100};

static const float VELOCITY_MOB_lv0 = -1;
static const float VELOCITY_BULLET_PLAYER = 15;
static const float VELOCITY_BULLET_MOB = -15;

static const int SIZE_PARTICULE = 3;
static const sf::Color COLOR_PARTICULE = {144, 145, 173, 255};
static const float VELOCITY_PARTICULE = VELOCITY_GAME;

static const int SIZE_BACKGROUND = 1920;

static const sf::Color COLOR_WALL = {202, 110, 50, 100};
static const float VELOCITY_WALL = -11;

/**
 * @brief Healt Point in the begin of the entity's life
 * 
 */
static const int HP_PLAYER = 500;
static const int HP_MOB_lv0 = 20;
static const int HP_WALL = 15;
static const int HP_BULLET = 1;


/**
 * @brief Powerfull of entity's
 * 
 */
static const int POWERFULL_BULLET_PLAYER = 1000;
static const int POWERFULL_BULLET_MOB_lv0 = 30  ;

static const int POWERFULL_HIT_PLAYER = 15000;
static const int POWERFULL_HIT_WALL = 100;
static const int POWERFULL_HIT_MOB_lv0 = 300;

/**
 * @brief The id of the entity
 *
 */
enum entity_id_e
{
    PLAYER = 0,
    PLAYER_BULLET,
    MOB_lv0,
    PICK_UPS_HP,
    PICK_UPS_DMG,
    PICK_UPS_WEAP,
    ID_PARTICULE,
    WALL,
    MOB_BULLET,
};

enum type_pickup {
    HP,
    DMG,
    WEAP,
};

#endif /* !ENTITYID_HPP_ */
