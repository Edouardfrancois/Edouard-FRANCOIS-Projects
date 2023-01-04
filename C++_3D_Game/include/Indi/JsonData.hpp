/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** JsonData
*/

#ifndef JSONDATA_HPP_
#define JSONDATA_HPP_

#include <sys/types.h>

typedef struct EntityConf_s
{
    size_t Heal;
    size_t Speed;
    size_t MaxItem;
} EntityConf_t;

typedef struct BommConf_s
{
    size_t ExplosionSize;
    double TimeBeaforeExplose;
} BommConf_t;

typedef struct Speed_s
{
    size_t AddSpeed;
    double EffectDuration;
} Speed_t;

#endif /* !JSONDATA_HPP_ */
