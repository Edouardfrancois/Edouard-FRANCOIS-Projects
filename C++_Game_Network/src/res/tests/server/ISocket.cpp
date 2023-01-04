/*
** EPITECH PROJECT, 2022
** LibSocket
** File description:
** ISocket
*/

#include <criterion/criterion.h>

#include "SocketExeption.hpp"
#include "ISocket.hpp"

Test(TestSocket, TestAll)
{
    try
    {
        Networks::ISocket i(12, 15, 20);
    }
    catch (SocketExeption::ISocketError &e)
    {
        cr_assert(true);
    }
    Networks::ISocket i;
}