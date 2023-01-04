/*
** EPITECH PROJECT, 2022
** LibSocket
** File description:
** Server
*/

#include <criterion/criterion.h>

#include "SocketExeption.hpp"
#include "Serveur.hpp"
#include "Client.hpp"

typedef struct
{
    int data;
} Packet_t;

Test(TestServer, Normal_bind)
{
    Networks::Serveur a;

    a.SetPortServeur(4003);
}

Test(TestServer, Rong_bind)
{
    Networks::Serveur P;

    P.SetPortServeur(4000);
    try
    {
        Networks::Serveur p;
        p.SetPortServeur(0);
    }
    catch (const SocketExeption::PortProtected &e)
    {
        cr_assert(true);
    }
    try
    {
        Networks::Serveur p;
        p.SetPortServeur(22);
    }
    catch (const SocketExeption::PortProtected &e)
    {
        cr_assert(true);
    }
    try
    {
        Networks::Serveur p;
        p.SetPortServeur(4000);
    }
    catch (const SocketExeption::PortChange &e)
    {
        printf("%d\n", e.GetDataInt());
        cr_assert_eq(e.GetDataInt(), 4001);
    }
    try
    {
        Networks::Serveur p(AF_LOCAL);
        p.SetPortServeur(4000);
    }
    catch (const SocketExeption::BindError &e)
    {
        cr_assert(true);
    }
}

Test(TestServer, TestSelect)
{
    Networks::Serveur S;
    Packet_t res;
    Networks::SocketEvent_u e;
    {
        Networks::Client C;
        S.SetPortServeur(4005);
        C.ConnectServeur("127.0.0.1", 4005);
        C.SendPacket<Packet_t>({12});
        res = S.Select<Packet_t>(e);
        cr_assert_eq(e.Event, Networks::Select::S_EVENT_NEW_CONNECTION);
        res = S.Select<Packet_t>(e);
        cr_assert_eq(res.data, 12);
    }
    res = S.Select<Packet_t>(e);
    cr_assert_eq(e.Event, Networks::Select::S_EVENT_CLOSE);
}

Test(TestServer, Test_Multi_Client)
{
    Networks::SocketEvent_u e;
    Networks::Serveur S;
    Packet_t res;

    S.SetPortServeur(4015);

    {
        Networks::Client C1;
        C1.ConnectServeur("127.0.0.1", 4015);
        res = S.Select<Packet_t>(e);
        printf("%d\n", e.Socket);
        {
            Networks::Client C2;
            C2.ConnectServeur("127.0.0.1", 4015);
            res = S.Select<Packet_t>(e);
            cr_expect_eq(e.Event, Networks::Select::S_EVENT_NEW_CONNECTION);
            C1.SendPacket<Packet_t>({12});
            res = S.Select<Packet_t>(e);
            cr_expect_eq(e.Event, Networks::Select::S_EVENT_READ);
            cr_expect_eq(res.data, 12);
        }
        res = S.Select<Packet_t>(e);
        cr_expect_eq(e.Event, Networks::Select::S_EVENT_CLOSE);
    }
}