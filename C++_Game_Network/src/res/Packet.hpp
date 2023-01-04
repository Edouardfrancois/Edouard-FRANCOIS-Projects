/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** packet
*/

#ifndef PACKET_HPP_
#define PACKET_HPP_

#include <cstddef>
#include <uuid/uuid.h>

#if __APPLE__
typedef unsigned short u_short;
#endif

struct packet_t
{
public:
    uuid_t senderUuid;
    uuid_t lobbyUuid;
    uuid_t packetuuid;
    enum type_e
    {
        T_ERROR_P_LOBBY_FULL = -104,
        T_ERROR_P_LOBBY_DON_T_EXIST = -103,
        T_ERROR_P_CANT_JOIN_THIS_LOBBY = -102,
        T_ERROR_P_LOBBY_ALL_READY_EXIST = -101,
        T_ERROR_P_MAX_LOBBY = -100,
        T_ERROR_ENTITY_NOT_DESTROY = -7,
        T_ERROR_IMPOSIBLE_TO_STOP_MOVE = -6,
        T_ERROR_IMPOSIBLE_TO_MOUVE = -5,
        T_ERROR_IMPOSIBLE_TO_CREATE_ENTITY = -4,
        T_ERROR_UNKNOWN_ENTITY_ID = -3,
        T_ERR0R_LOBBY_FULL = -2,
        T_ERROR = -1,
        T_CONNECTION = 0,
        T_BEGIN_GAME = 1,
        T_CREATE_ENTITY = 2,
        T_BEGIN_MOUVE = 3,
        T_PING_ENTITY = 4,
        T_END_MOUVE = 5,
        T_UUID_GET_INFO = 6,
        T_UUID_MABY_MISS = 7,
        T_DESTROY_ENTITY = 8,
        T_INVENTORY = 9,
        T_USE_BOOST = 10,
        T_END_GAME = 11,
        T_RUN_GAME = 12,
        T_UPDATE_POS_ENTITY = 13,
        T_UPDATE_LIFE = 14,
        T_DONT_KNOW = 15,
        P_CREATE_LOBBY = 100,
        P_USR_JOIN = 101,
        P_JOIN_SUCESS = 102,
        P_JOIN_LOBBY = 103,
        P_LEAVE_LOBBY = 104,
        P_USR_LEAVE_LOBBY = 105,
        P_LODDY_DESTRY = 106,
    } packet_type;
    union
    {
        struct
        {
            u_short id;
            float x;
            float y;
            float Degree;
            float Velocity;
            int life;
            // u_short Vy;
            uuid_t entity_uuid;
        } create_entity;
        struct
        {
            uuid_t entity_uuid;
            float Degree;
            u_short id;
            u_short x;
            u_short y;
            u_short Vx;
            u_short Vy;
        } get_info;

        struct
        {
            int life;
            uuid_t entity_uuid;

        } life;
        struct
        {
            u_short x;
            u_short y;
        } screen_size;
        struct
        {
            uuid_t entity_uuid;
            float Degree;
            u_short Velocity;
        } mouve;
        struct
        {
            uuid_t entity_uuid;
            float x;
            float y;
        } poss;
        struct
        {
            uuid_t entity_uuid;
            u_short x;
            u_short y;
        } ping_entity;
        struct
        {
            uuid_t entity_uuid;
        } maby_miss;
        struct
        {
            uuid_t entity_uuid;
            u_short x;
            u_short y;
        } destroy;
        struct
        {
            uuid_t entity_uuid;
            u_short boots_id; // id du boots
            u_short count;    // nombre de boots de l'entity
        } iventory;
        struct
        {
            uuid_t entity_uuid;
            float time_left;  // durée avant la fin du boots
            u_short boots_id; // id du boot
        } use_boots;
        // struct
        // {
        //     uuid_t entity_uuid;
        //     u_short hp_beafore;
        //     u_short hp_after;
        // } life;
        struct
        {
            uuid_t lobby_uuid;
            u_short index;
        } list_lobby;
        struct
        {
            uuid_t usruuid;
            u_short index;
        } lobby_new_usr;
        struct
        {
            uuid_t usruuid;
        } lobby_disconned_usr;
        struct
        {
            uuid_t lobby_uuid;
        } lobby_destroy;

        struct
        {
            bool check;
        } is_win;
    } body_t;
} __attribute__((packed));

// void toto()
// {
// packet_t p;
// p.lobby.usr_name = "toto";
// }

#endif /* !PACKET_HPP_ */
