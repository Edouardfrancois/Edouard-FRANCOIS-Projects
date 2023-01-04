/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** BombDetonation
*/

#ifndef BOMBDETONATION_HPP_
#define BOMBDETONATION_HPP_

#include "Indi.hpp"
#include <ctime>

class BombDetonation {
    public:
        BombDetonation();
        ~BombDetonation();
        bool CheckDetonation(const TAllMap& AllMap, BommConf_t *BommConf);
        bool Detonation(const TypePile &pile, BommConf_t *BommConf);

    protected:
    private:
        int _oldtime;
        time_t current_time;
};

#endif /* !BOMBDETONATION_HPP_ */
