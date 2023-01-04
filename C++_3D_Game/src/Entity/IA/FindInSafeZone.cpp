/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** FindInSafeZone
*/

#include "IA.hpp"

HisPossibleToGoObjectif FindArray_s::_IsSafeZoneNext(const ManageIa& ManageMap, const Poss_t& Poss, size_t x, size_t y, size_t& count, const PassIaInfoGame_t& GameInfo, const TInveotry& Inv)
{
    // /* regarde en haut */
    auto TmpType = static_cast<IAMapElemType>(this->_Array[y - 1][x]);
    HisPossibleToGoObjectif RetHistory;

    if (TmpType != IAMapElemType::UNBREAKABLE and TmpType != IAMapElemType::DAMAGE_ZONE and TmpType != IAMapElemType::ME and this->_Array[y - 1][x] <= 0) {
    //     // printf("Boucle Not danger zone: x:%ld y:%ld\n", x, y - 1);
        RetHistory = _SetSafeObjectif(ManageMap, Poss, x, y - 1, count, GameInfo, Inv);
        if (RetHistory != HisPossibleToGoObjectif::IMPOSSIBLE)
            return RetHistory;
    }
    // /* regarde en bas */
    TmpType = static_cast<IAMapElemType>(this->_Array[y + 1][x]);
    if (TmpType != IAMapElemType::UNBREAKABLE and TmpType != IAMapElemType::DAMAGE_ZONE and TmpType != IAMapElemType::ME and this->_Array[y + 1][x] <= 0) {
    //     // printf("Boucle Not danger zone: x:%ld y:%ld\n", x, y + 1);
        RetHistory = _SetSafeObjectif(ManageMap, Poss, x, y + 1, count, GameInfo, Inv);
        if (RetHistory != HisPossibleToGoObjectif::IMPOSSIBLE)
            return RetHistory;
    }
    // /* regarde a gauche */
    TmpType = static_cast<IAMapElemType>(this->_Array[y][x - 1]);
    if (TmpType != IAMapElemType::UNBREAKABLE and TmpType != IAMapElemType::DAMAGE_ZONE and TmpType != IAMapElemType::ME and this->_Array[y][x - 1] <= 0) {
    //     // printf("Boucle Not danger zone: x:%ld y:%ld\n", x - 1, y);
        RetHistory = _SetSafeObjectif(ManageMap, Poss, x - 1, y, count, GameInfo, Inv);
        if (RetHistory != HisPossibleToGoObjectif::IMPOSSIBLE)
            return RetHistory;
    }
    // /* regarde a droite */
    TmpType = static_cast<IAMapElemType>(this->_Array[y][x + 1]);
    if (TmpType != IAMapElemType::UNBREAKABLE and TmpType != IAMapElemType::DAMAGE_ZONE and TmpType != IAMapElemType::ME and this->_Array[y][x + 1] <= 0) {
        // printf("Boucle Not danger zone: x:%ld y:%ld\n", x + 1, y);
        RetHistory = _SetSafeObjectif(ManageMap, Poss, x + 1, y, count, GameInfo, Inv);
        if (RetHistory != HisPossibleToGoObjectif::IMPOSSIBLE)
            return RetHistory;
    }
    return HisPossibleToGoObjectif::IMPOSSIBLE;
}
