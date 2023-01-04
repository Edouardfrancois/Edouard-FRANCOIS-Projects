/*
** EPITECH PROJECT, 2022
** client
** File description:
** GameManager
*/

#include <unistd.h>

#include "Frame.hpp"
#include "GameManager.hpp"
#include "components.hpp"
#include "registry.hpp"
#include "buttonFunc.hpp"
#include <limits.h>
// #include <Vector2.hpp>
// #include <SFML/RectangleShape.hpp>

#include <unordered_map>

std::shared_ptr<player_uuid_t> TestMe;

void GameManager::_UpdatePosToServer()
{
    auto &sparse_array_position = this->_regis.get_components<position_t>();
    auto &sparse_array_uuid = this->_regis.get_components<player_uuid_t>();

    packet_t P = {};
    P.packet_type = packet_t::T_UPDATE_POS_ENTITY;

    for (size_t idx = 0; idx < sparse_array_uuid.size(); idx++)
        if (sparse_array_position[idx] && sparse_array_uuid[idx])
        {
            if (uuid_compare(sparse_array_uuid[idx]->uuid, this->_uuidClient) == 0)
            {
                uuid_copy(P.body_t.poss.entity_uuid, sparse_array_uuid[idx]->uuid);
                P.body_t.poss.x = sparse_array_position[idx]->x;
                P.body_t.poss.y = sparse_array_position[idx]->y;
                this->_Send.get()->SendTo(P);
            }
        }
}

GameManager::GameManager(char *argv[]) : _Disp(1920, 1080, 60), _Pool(2, false, false), _particules(this->_regis)
{
    this->_HandleServ = std::make_unique<HandleServer>();
    this->_QueuThread = std::make_shared<utils::SafeQueue<packet_t>>();
    this->_Send = std::make_shared<SendPacket<packet_t>>(this->_HandleServ.get()->GetUdpServerSocket(), argv[1], std::atoi(argv[2]));

    // this->_playerGun = shoot::Weapon(shoot::FireMOD::Single);
    this->envSound.initSFX();
    this->envSound.load_Music("assets/sounds/music.ogg");
    this->envSound.set_MusicLoop(true);

    this->_Lobby = std::make_shared<Lobby>(this->_Send);
    this->_Pool.attributeTasks(std::bind(&HandleServer::RunClient, this->_HandleServ.get(), this->_QueuThread)); // NE pas enveler
    this->_Pool.attributeTasks(std::bind(&GameManager::_FncForTest, this));                                      // NE pas enveler pour le test sauf rendue final

    this->_manage_message_from_server.insert({packet_t::type_e::T_ERROR_IMPOSIBLE_TO_STOP_MOVE, &GameManager::msg_from_server_error_impossible_to_stop_move});
    this->_manage_message_from_server.insert({packet_t::type_e::T_ERROR_IMPOSIBLE_TO_MOUVE, &GameManager::msg_from_server_error_impossible_to_move});
    this->_manage_message_from_server.insert({packet_t::type_e::T_ERROR_UNKNOWN_ENTITY_ID, &GameManager::msg_from_server_error_impossible_to_create_entity});
    this->_manage_message_from_server.insert({packet_t::type_e::T_ERROR_UNKNOWN_ENTITY_ID, &GameManager::msg_from_server_error_unknow_entity});
    this->_manage_message_from_server.insert({packet_t::type_e::T_ERR0R_LOBBY_FULL, &GameManager::msg_from_server_error_lobby_full});
    this->_manage_message_from_server.insert({packet_t::type_e::T_ERROR, &GameManager::msg_from_server_error});
    this->_manage_message_from_server.insert({packet_t::type_e::T_CONNECTION, &GameManager::msg_from_server_connection});
    this->_manage_message_from_server.insert({packet_t::type_e::T_BEGIN_GAME, &GameManager::msg_from_server_begin_game});
    this->_manage_message_from_server.insert({packet_t::type_e::T_CREATE_ENTITY, &GameManager::msg_from_server_create_entity});
    this->_manage_message_from_server.insert({packet_t::type_e::T_BEGIN_MOUVE, &GameManager::msg_from_server_begin_mouve});
    this->_manage_message_from_server.insert({packet_t::type_e::T_END_MOUVE, &GameManager::msg_from_server_end_mouve});
    this->_manage_message_from_server.insert({packet_t::type_e::T_END_GAME, &GameManager::msg_from_server_end_game});
    this->_manage_message_from_server.insert({packet_t::type_e::T_UPDATE_POS_ENTITY, &GameManager::msg_from_server_update_pos_entity});
    this->_manage_message_from_server.insert({packet_t::type_e::T_DESTROY_ENTITY, &GameManager::msg_from_server_destroy_entity});
    this->_manage_message_from_server.insert({packet_t::type_e::T_UPDATE_LIFE, &GameManager::msg_from_server_update_life_entity});
    // _manage_paket.insert(T_ERR0R_LOBBY_FULL, manage_error_lobby);

    this->_collision.insert({this->_HashCollision(entity_id_e::PLAYER, entity_id_e::MOB_lv0), &GameManager::_CollisionPlayerToMonster});
    this->_collision.insert({this->_HashCollision(entity_id_e::PLAYER_BULLET, entity_id_e::MOB_lv0), &GameManager::_CollisionBulletToMonster});
    this->_collision.insert({this->_HashCollision(entity_id_e::PLAYER_BULLET, entity_id_e::PLAYER), &GameManager::_CollisionBulletToPlayer});
    this->_collision.insert({this->_HashCollision(entity_id_e::PLAYER_BULLET, entity_id_e::PLAYER_BULLET), &GameManager::_CollisionBulletToBullet});
    this->_collision.insert({this->_HashCollision(entity_id_e::MOB_lv0, entity_id_e::PLAYER_BULLET), &GameManager::_CollisionMonsterToBullet});
}

void GameManager::PrintHp()
{
    auto &sparse_array_hp = _regis.get_components<HP_t>();
    auto &sparse_array_uuid = _regis.get_components<player_uuid_t>();
    auto &sparse_array_pos = _regis.get_components<position_t>();
    auto &sparse_array_id = _regis.get_components<my_id_t>();

    for (int i = 0; i < sparse_array_uuid.size(); i++)
    {
        if (sparse_array_hp[i].has_value() && sparse_array_uuid[i].has_value() && sparse_array_pos[i].has_value() && sparse_array_id[i].has_value())
        {
            // if (sparse_array_id[i]->id == PLAYER)
            //     std::cout << "HP = " << sparse_array_hp[i]->hp << "pos_x = " << sparse_array_pos[i]->x << "pos_y" << sparse_array_pos[i]->y << "\n";
        }
    }
}

void GameManager::AnalyseMessageServeur(packet_t packet)
{
    _manage_message_from_server[packet.packet_type](*this, packet, this->_uuidClient);
}

void GameManager::_ConnectToServer()
{
    packet_t P = {};
    P.packet_type = P.T_CONNECTION;
    uuid_generate(P.packetuuid);
    this->_Send.get()->SendTo(P);
}

void GameManager::_FncForTestPrintPacket(const packet_t &Packet)
{
    char struuid[37] = {};
    dprintf(2, "---New Packet---\ntype: '%d'.\n", Packet.packet_type);
    dprintf(2, "Sender Uuid: ");
    uuid_unparse_lower(Packet.senderUuid, struuid);
    dprintf(2, "'%s'.\n", struuid);
    dprintf(2, "Lobby Uuid: ");
    uuid_unparse_lower(Packet.lobbyUuid, struuid);
    dprintf(2, "'%s'.\n", struuid);
    dprintf(2, "Packet Uuid: ");
    uuid_unparse_lower(Packet.packetuuid, struuid);
    dprintf(2, "'%s'.\n\n", struuid);
    switch (Packet.packet_type)
    {
    case packet_t::T_CONNECTION:
        dprintf(2, "Connection Packet\n");
        break;
    case packet_t::T_BEGIN_GAME:
        dprintf(2, "Begin Game Packet\n");
        dprintf(2, "x:%d\n", Packet.body_t.screen_size.x);
        dprintf(2, "y:%d\n", Packet.body_t.screen_size.y);
        break;
    case packet_t::T_CREATE_ENTITY:
        dprintf(2, "Create Entity Packet\n");
        dprintf(2, "id Type: %d\n", Packet.body_t.create_entity.id);
        dprintf(2, "Entity uuid:\n");
        uuid_unparse_lower(Packet.body_t.create_entity.entity_uuid, struuid);
        dprintf(2, "'%s'.\n\n", struuid);
        dprintf(2, "x:%d\n", Packet.body_t.create_entity.x);
        dprintf(2, "y:%d\n", Packet.body_t.create_entity.y);
        break;
    case packet_t::T_BEGIN_MOUVE:
        dprintf(2, "Begin Move Entity Packet\n");
        // dprintf(2, "direction: %d\n", Packet.body_t.mouve.direction);
        dprintf(2, "Entity uuid:\n");
        uuid_unparse_lower(Packet.body_t.mouve.entity_uuid, struuid);
        dprintf(2, "'%s'.\n\n", struuid);
        dprintf(2, "Speed\n");
        // dprintf(2, ":%d\n", Packet.body_t.mouve.speed);
        break;
    case packet_t::P_CREATE_LOBBY:
        dprintf(2, "create Lobby\n");
        uuid_unparse_lower(Packet.body_t.list_lobby.lobby_uuid, struuid);
        dprintf(2, "'%s'.\n\n", struuid);
        dprintf(2, "index:%d\n", Packet.body_t.list_lobby.index);
        break;
    default:
        dprintf(2, "Unknown Packet\n");
        break;
    }
    dprintf(2, "--- END Packet---\n");
}

void GameManager::_FncForTest()
{
    packet_t P = {};
    while (1)
    {
        int x = 0;
        scanf("%d", &x);
        if (x == 1)
        {
            P.packet_type = packet_t::T_CONNECTION;
        }
        else if (x == 2)
        {
            std::printf("Send begin\n");
            P.packet_type = packet_t::T_BEGIN_GAME;
        }
        else if (x == -1)
        {
            P.packet_type = packet_t::P_CREATE_LOBBY;
            uuid_t NameOfLobby = "LobbyToto";
            uuid_copy(P.body_t.list_lobby.lobby_uuid, NameOfLobby);
        }
        else if (x == -2)
        {
            P.packet_type = packet_t::P_JOIN_LOBBY;
            uuid_t NameOfLobby = "LobbyToto";
            uuid_copy(P.body_t.list_lobby.lobby_uuid, NameOfLobby);
        }
        else if (x == -3)
        {
            P.packet_type = packet_t::P_LEAVE_LOBBY;
        }
        else if (x == -4)
        {
            P.packet_type = packet_t::P_CREATE_LOBBY;
            uuid_t NameOfLobby = "LobbyTiti";
            uuid_copy(P.body_t.list_lobby.lobby_uuid, NameOfLobby);
        }
        else if (x == -5)
        {
            P.packet_type = packet_t::P_JOIN_LOBBY;
            uuid_t NameOfLobby = "LobbyTiti";
            uuid_copy(P.body_t.list_lobby.lobby_uuid, NameOfLobby);
        }
        else
        {
            continue;
        }
        this->_Send.get()->SendTo(P);
    }
}

void GameManager::_SendServUuidStopMove(const uuid_t &uuid)
{
    packet_t P = {};
    uuid_generate_random(P.packetuuid);
    uuid_copy(P.body_t.mouve.entity_uuid, uuid);
    // P.body_t.mouve.speed = 1;
    P.packet_type = packet_t::T_END_MOUVE;
    this->_Send.get()->SendTo(P);
}

void GameManager::_SendServUuidBeginMove(const uuid_t &uuid)
{
    packet_t P = {};
    uuid_generate_random(P.packetuuid);
    uuid_copy(P.body_t.mouve.entity_uuid, uuid);
    // P.body_t.mouve.speed = 1;
    P.packet_type = packet_t::T_BEGIN_MOUVE;
    this->_Send.get()->SendTo(P);
}

void GameManager::manage_player_inputQueue(std::queue<input_key> player_keys)
{
    auto &uuid_s = _regis.get_components<player_uuid_t>();
    auto &pos = _regis.get_components<position_t>();
    auto &weap = _regis.get_components<shoot::Weapon>();

    int i = -1;
    input_key key;
    std::unordered_map<input_key, dirctionsValues> mapDirectionVal = {
        {input_key::UP, dirctionsValues(-1, 0)},
        {input_key::DOWN, dirctionsValues(1, 0)},
        {input_key::LEFT, dirctionsValues(0, -1)},
        {input_key::RIGHT, dirctionsValues(0, 1)},
    };

    for (size_t idx = 0; idx < uuid_s.size() && idx < pos.size(); idx++)
        if (!uuid_compare(uuid_s[idx]->uuid, this->_uuidClient))
            i = idx;
    if (i == -1)
        return;
    while (!player_keys.empty())
    {
        key = player_keys.front();
        player_keys.pop();
        if (key == input_key::NIL)
        {
            continue;
        }
        if (key != input_key::NIL)
        {
            pos[i]->y += (mapDirectionVal[key].y * 6);
            pos[i]->x += (mapDirectionVal[key].x * 6);
        }
        if (key == input_key::SPACE)
        {
            if (pos[i].has_value() && weap.size() > i && weap[i].has_value())
            {
                std::queue<packet_t> toSend = weap[i]->shoot(pos.at(i)); // this->_playerGun.shoot(pos.at(i));
                while (!toSend.empty())
                {
                    this->envSound.playSound(mySound::Fire);
                    packet_t curr = toSend.front();
                    toSend.pop();
                    this->_Send.get()->SendTo(curr);
                }
            }
            return;
        }
    }
}

void GameManager::manage_player_input(input_key player_key)
{
    auto &uuid_s = _regis.get_components<player_uuid_t>();
    auto &pos = _regis.get_components<position_t>();
    auto &weap = _regis.get_components<shoot::Weapon>();

    int i = -1;
    std::unordered_map<input_key, dirctionsValues> mapDirectionVal = {
        {input_key::UP, dirctionsValues(-1, 0)},
        {input_key::DOWN, dirctionsValues(1, 0)},
        {input_key::LEFT, dirctionsValues(0, -1)},
        {input_key::RIGHT, dirctionsValues(0, 1)},
    };

    for (size_t idx = 0; idx < uuid_s.size() && idx < pos.size(); idx++)
        if (!uuid_compare(uuid_s[idx]->uuid, this->_uuidClient))
            i = idx;

    if (i == -1)
        return;
    if (player_key != input_key::NIL)
    {
        pos[i]->y += (mapDirectionVal[player_key].y * 6);
        pos[i]->x += (mapDirectionVal[player_key].x * 6);
    }

    if (player_key == input_key::SPACE)
    {
        this->envSound.playSound(mySound::mySoundType::Fire);
        if (pos[i].has_value() && weap.size() > i && weap[i].has_value())
        {
            std::queue<packet_t> toSend = weap[i]->shoot(pos.at(i)); // this->_playerGun.shoot(pos.at(i));
            while (!toSend.empty())
            {
                packet_t curr = toSend.front();
                toSend.pop();
                this->_Send.get()->SendTo(curr);
            }
        }
        // packet_t packet_send = {};
        // packet_send.packet_type = packet_t::T_CREATE_ENTITY;
        // packet_send.body_t.create_entity.id = entity_id_e::PLAYER_BULLET;
        // packet_send.body_t.create_entity.x = pos[i]->x;
        // packet_send.body_t.create_entity.y = pos[i]->y;
        // packet_send.body_t.create_entity.Degree = 0;
        // packet_send.body_t.create_entity.Velocity = VELOCITY_BULLET_PLAYER;
        // this->_Send.get()->SendTo(packet_send);
        return;
    }
}

void GameManager::UpdateBulletPosition()
{
    auto &sparse_array_balle = this->_regis.get_components<balle_t>();
    auto &sparse_array_position = this->_regis.get_components<position_t>();

    auto &sparse_array_velocity = this->_regis.get_components<velocity_t>();
    auto &wall = this->_regis.get_components<is_wall_t>();

    // std::cout << "a\n";
    // for (size_t idx = 0; idx < sparse_array_position.size(); idx++) {
    //     if (sparse_array_balle.size() > 0) {
    //         if (sparse_array_position[idx].has_value() && sparse_array_balle[idx].has_value() && sparse_array_velocity[idx].has_value())
    //         {
    //             // std::cout << "cc\n";
    //             sparse_array_position[idx]->x += 15 /*sparse_array_velocity[idx]->Velocity*/;

    //         }
    //     }
    //     if (wall.size() > 0) {
    //         if (sparse_array_position[idx].has_value() && wall[idx].has_value() && sparse_array_velocity[idx].has_value()) {
    //             sparse_array_position[idx]->x += sparse_array_velocity[idx]->Velocity;
    //             // std::cout << sparse_array_position[idx]->x << " POS WALL\n";
    //         }
    //     }
    // }
    this->_particules.update(this->_regis);
}

void GameManager::UpdateWallPosition()
{
    auto &sparse_array_wall = this->_regis.get_components<is_wall_t>();
    auto &sparse_array_position = this->_regis.get_components<position_t>();

    auto &sparse_array_velocity = this->_regis.get_components<velocity_t>();

    for (size_t idx = 0; idx < sparse_array_wall.size(); idx++)
        if (sparse_array_position[idx].has_value() && sparse_array_wall[idx].has_value() && sparse_array_velocity[idx].has_value())
        {
            if (sparse_array_position[idx]->x < 0)
                _regis.kill_entity(_regis.entity_from_index(idx));
            sparse_array_position[idx]->x += sparse_array_velocity[idx]->Velocity;
        }
    this->_particules.update(this->_regis);
}

void GameManager::_CheckCollision()
{
    sparse_array<hit_box_t> &box = this->_regis.get_components<hit_box_t>();
    sparse_array<position_t> &pos = this->_regis.get_components<position_t>();
    sparse_array<size_entity_t> &size = this->_regis.get_components<size_entity_t>();
    sparse_array<my_id_t> &id = this->_regis.get_components<my_id_t>();
    sparse_array<balle_t> &bullets = this->_regis.get_components<balle_t>();

    for (size_t idx = 0; idx < box.size(); idx++)
    {
        for (size_t i = 0; i < box.size(); i++)
        {
            if (idx != i && box[i].has_value() && pos[i].has_value() && size[i].has_value() && id[i].has_value() && box[idx].has_value() && id[idx].has_value())
            {
                sf::FloatRect fst(pos[idx]->x, pos[idx]->y, size[idx]->size, size[idx]->size);
                sf::FloatRect sd(pos[i]->x, pos[i]->y, size[i]->size, size[i]->size);

                if (fst.intersects(sd))
                {
                    this->_collision[this->_HashCollision(id[idx]->id, id[i]->id)](*this, _regis.entity_from_index(idx), _regis.entity_from_index(i));
                }
            }
        }
    }
}

void GameManager::_RunGame()
{
    Frame frame;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    int tmp = 0;
    sleep(1);
    _ConnectToServer();
    //_regis.register_component<balle_t>();
    this->envSound.play_Music();
    while (this->_Disp.win_is_open())
    {
        start = std::chrono::system_clock::now();
        // manage_player_input(this->_Disp.keycatch());
        manage_player_inputQueue(this->_Disp.get_inputQueue());
        // this->_Disp.clearEventQueue();
        //  UpdateBulletPosition();
        //  UpdateWallPosition();
        this->_particules.update(this->_regis);
        PrintHp();
        this->_Disp.ite(this->_regis);
        frame.Increment();
        if (frame.Get() == 5)
        {
            frame.Reset();
            this->_UpdatePosToServer();
        }

        if (this->_QueuThread.get()->is_empty() == true)
            continue;
        while (!this->_QueuThread.get()->is_empty())
        {
            packet_t packet = {};
            this->_QueuThread.get()->try_pop(packet);
            // std::cout << "packet -----\n";
            this->AnalyseMessageServeur(packet);
        }

        // this->_CheckCollision();
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> time = (end - start) * 1000000;
    }
}

void GameManager::_RunLobby()
{
    bool HaveToStop = false;

    Manage_Asset assetManager;

    Entity menuSprite = _LobbyRegis.spawn_entity();
    _LobbyRegis.add_component<sprite_s>(menuSprite, sprite_s(assetManager, "./assets/images/waiter.jpg"));
    _LobbyRegis.add_component<drawable_t>(menuSprite, drawable_t(1, sf::Color::Cyan, 1));
    _LobbyRegis.add_component<position_t>(menuSprite, {0, 0});

    Entity createLobbySprite = _LobbyRegis.spawn_entity();

    Entity playSprite = _LobbyRegis.spawn_entity();
    buttonFunc buttonfunc;
    std::function<void(void)> func = [&]()
    { buttonfunc.playButton(HaveToStop); };
    _LobbyRegis.add_component<button_t>(playSprite, button_t(assetManager, "./assets/images/play-button.png", func));
    _LobbyRegis.add_component<sprite_s>(playSprite, sprite_s(assetManager, "./assets/images/play-button.png"));
    _LobbyRegis.get_components<sprite_s>()[playSprite.get_size()]->sprite.setScale(sf::Vector2f(0.05f, 0.05f));
    _LobbyRegis.add_component<drawable_t>(playSprite, drawable_t(0, sf::Color::Cyan, 1));
    _LobbyRegis.add_component<position_t>(playSprite, {300, 300});

    Entity playSprite2 = _LobbyRegis.spawn_entity();
    buttonFunc buttonfunc3;
    std::function<void(void)> func2 = [&]()
    { buttonfunc3.createLobby(); };
    _LobbyRegis.add_component<button_t>(playSprite2, button_t(assetManager, "./assets/images/create.png", func2));
    _LobbyRegis.add_component<sprite_s>(playSprite2, sprite_s(assetManager, "./assets/images/create.png"));
    _LobbyRegis.get_components<sprite_s>()[playSprite2.get_size()]->sprite.setScale(sf::Vector2f(0.05f, 0.05f));
    _LobbyRegis.add_component<drawable_t>(playSprite2, drawable_t(0, sf::Color::Cyan, 1));
    _LobbyRegis.add_component<position_t>(playSprite2, {1200, 600});

    Entity TextBoxSprite = _LobbyRegis.spawn_entity();

    _LobbyRegis.add_component<textBox_t>(TextBoxSprite, textBox_t("assets/fonts/Arial.ttf", 24, sf::Color::Red));
    _LobbyRegis.get_components<textBox_t>()[TextBoxSprite.get_size()]->setText("GGGhello epitech");
    _LobbyRegis.add_component<drawable_t>(TextBoxSprite, drawable_t(100, sf::Color::Cyan, 4));
    _LobbyRegis.add_component<position_t>(TextBoxSprite, {100, 100});


    // LOBBY LOOP
    size_t clicked = -1;
    while (this->_Disp.win_is_open())
    {
        // std::cout << _Disp.buttonPressed(_LobbyRegis) << std::endl;
        clicked = _Disp.buttonPressed(_LobbyRegis);
        if (clicked != 42)
        {
            _LobbyRegis.get_components<button_t>()[clicked]->func();
            clicked = -1;
        }
        this->_Lobby.get()->Run(HaveToStop, this->_Disp, this->_uuidClient);
        this->_Disp.ite(_LobbyRegis); // draw _LobbyRegis !!
        if (HaveToStop)
        {
            printf("debug\n");
            break;
        }
        if (this->_QueuThread.get()->is_empty() == true)
            continue;
        packet_t packet = {};
        this->_QueuThread.get()->try_pop(packet);
        this->_Lobby.get()->ManagePacket(packet);
    }
}

void GameManager::Run()
{
    TestMe = std::make_shared<player_uuid_t>();

    sleep(1); // NE pas enlever
    _ConnectToServer();
    _RunLobby();
    _RunGame();
}

GameManager::~GameManager() {}
