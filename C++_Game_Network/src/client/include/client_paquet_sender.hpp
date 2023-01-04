/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** client_paquet_sender.hpp
*/

#include <unistd.h>
#include <iostream>

#include "HandleUuid.hpp"
#include "SendPacket.hpp"
#include "HandleServer.hpp"
#include "ThreadPool.hpp"

class cl_sender {
    public:
        cl_sender();
        ~cl_sender();
        void sender(){
            packet_t P = {};
            uuid_generate_random(P.packetuuid);
            P->_Send.get()->SendTo(P);
        }
    private:
        std::shared_ptr<SendPacket<packet_t>> _Send;

};