/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Objectif
*/

#include "IA.hpp"

/**
 * @brief 
 * 
 * @param Map AllMap
 * @param ObjectifX the new X objectif
 * @throw Exception::ImposibleToSetThatObjectif
 */
void IaObjectif_s::SetNewObjectifX(const TAllMap& AllMap, const size_t ObjectifX)
{
    if (AllMap[this->_DirectionObjectifY][ObjectifX].get()->IsWallInPile())
        throw Exception::ImposibleToSetThatObjectif();
    this->_DirectionObjectifX = ObjectifX;
}

/**
 * @brief 
 * 
 * @param Map AllMap
 * @param ObjectifY the new Y objectif
 * @throw Exception::ImposibleToSetThatObjectif
 */
void IaObjectif_s::SetNewObjectifY(const TAllMap& AllMap, const size_t ObjectifY)
{
    if (AllMap[ObjectifY][this->_DirectionObjectifX].get()->IsWallInPile())
        throw Exception::ImposibleToSetThatObjectif();
    this->_DirectionObjectifY = ObjectifY;
}

/**
 * @brief 
 * 
 * @param AllMap 
 * @param ObjectifX 
 * @param ObjectifY 
 * @throw Exception::ImposibleToSetThatObjectif
 */
void IaObjectif_s::SetNewObjectifXY(const TAllMap& AllMap, const size_t ObjectifX, const size_t ObjectifY)
{
    if (AllMap[ObjectifY][ObjectifX].get()->IsBombAtThisPile())
        throw Exception::ImposibleToSetThatObjectif();
    this->_DirectionObjectifX = ObjectifX;
    this->_DirectionObjectifY = ObjectifY;
}
