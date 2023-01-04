/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** FindFistTime
*/

#include "IA.hpp"

const Poss_t FindArray_s::_GetNearestPieceMap(const Poss_t& Poss)
{
    Poss_t ToRet(0, 0);

    if (Poss.GetX() % _SizeOneMapPiece < 5)
        ToRet.SetX(Poss.GetX() - (Poss.GetX() % _SizeOneMapPiece) - 1);
    else
        ToRet.SetX(Poss.GetX() - (Poss.GetX() % _SizeOneMapPiece) + _SizeOneMapPiece + 1);
    if (Poss.GetY() % _SizeOneMapPiece < 5)
        ToRet.SetY(Poss.GetY() - (Poss.GetY() % _SizeOneMapPiece) - 1);
    else
        ToRet.SetY(Poss.GetY() - (Poss.GetY() % _SizeOneMapPiece) + _SizeOneMapPiece + 1);
    return ToRet;
}

HisPossibleToGoObjectif FindArray_s::_FindNearest(const ManageIa& ManageMap, const Poss_t& Poss, size_t& count, const PassIaInfoGame_t& GameInfo, const TInveotry& Inv)
{
    const Poss_t NearPieceMap = _GetNearestPieceMap(Poss);
    // _DisplayDebug();
    IAMapElemType TmpType = static_cast<IAMapElemType>(this->_Array[Poss.GetYLikeTabIndex()][NearPieceMap.GetXLikeTabIndex()]);
    /* rechercher le plus proche en x */
    if (TmpType != IAMapElemType::UNBREAKABLE and TmpType != IAMapElemType::DAMAGE_ZONE) {
        return _SetSafeObjectif(ManageMap, Poss, NearPieceMap.GetXLikeTabIndex(), Poss.GetYLikeTabIndex(), count, GameInfo, Inv);
    }
    /* rechercher le plus proche en Y */
    TmpType = static_cast<IAMapElemType>(this->_Array[NearPieceMap.GetYLikeTabIndex()][Poss.GetXLikeTabIndex()]);
    if (TmpType != IAMapElemType::UNBREAKABLE and TmpType != IAMapElemType::DAMAGE_ZONE) {
        return _SetSafeObjectif(ManageMap, Poss, Poss.GetXLikeTabIndex(), NearPieceMap.GetYLikeTabIndex(), count, GameInfo, Inv);
    }
    return HisPossibleToGoObjectif::IMPOSSIBLE;
}


HisPossibleToGoObjectif FindArray_s::_FindBestWaiToBegin(const ManageIa& ManageMap, const Poss_t& Poss, size_t& count, const PassIaInfoGame_t& GameInfo, const TInveotry& Inv)
{
    HisPossibleToGoObjectif Ret = _FindNearest(ManageMap, Poss, count, GameInfo, Inv);
    if (Ret != HisPossibleToGoObjectif::IMPOSSIBLE)
        return Ret;
    /* regarde en haut */
    auto TmpType = ManageMap.GetMappIa()[Poss.GetYLikeTabIndex() - 1][Poss.GetXLikeTabIndex()].get()->GetBlockType();
    if (TmpType != IAMapElemType::UNBREAKABLE and TmpType != IAMapElemType::DAMAGE_ZONE and TmpType != IAMapElemType::IS_BOOM) {
        // printf("Fist Time Not danger zone: x:%ld y:%ld\n", Poss.GetXLikeTabIndex(), Poss.GetYLikeTabIndex() - 1);
        // printf("Type:%d\n", static_cast<int>(TmpType));
        if (_SetSafeObjectif(ManageMap, Poss, Poss.GetXLikeTabIndex(), Poss.GetYLikeTabIndex() - 1, count, GameInfo, Inv) == HisPossibleToGoObjectif::POSSIBLE) {
            return HisPossibleToGoObjectif::POSSIBLE;
        }
    }
    /* regarde en bas */
    TmpType = ManageMap.GetMappIa()[Poss.GetYLikeTabIndex() + 1][Poss.GetXLikeTabIndex()].get()->GetBlockType();
    if (TmpType != IAMapElemType::UNBREAKABLE and TmpType != IAMapElemType::DAMAGE_ZONE and TmpType != IAMapElemType::IS_BOOM) {
        // printf("Fist Time Not danger zone: x:%ld y:%ld\n", Poss.GetXLikeTabIndex(), Poss.GetYLikeTabIndex() + 1);
        // printf("Type:%d\n", static_cast<int>(TmpType));
        if (_SetSafeObjectif(ManageMap, Poss, Poss.GetXLikeTabIndex(), Poss.GetYLikeTabIndex() + 1, count, GameInfo, Inv) == HisPossibleToGoObjectif::POSSIBLE) {
            return HisPossibleToGoObjectif::POSSIBLE;
        }
    }
    /* regarde a gauche */
    TmpType = ManageMap.GetMappIa()[Poss.GetYLikeTabIndex()][Poss.GetXLikeTabIndex() - 1].get()->GetBlockType();
    if (TmpType != IAMapElemType::UNBREAKABLE and TmpType != IAMapElemType::DAMAGE_ZONE and TmpType != IAMapElemType::IS_BOOM) {
        // printf("Fist Time Not danger zone: x:%ld y:%ld\n", Poss.GetXLikeTabIndex() - 1, Poss.GetYLikeTabIndex());
        // printf("Type:%d\n", static_cast<int>(TmpType));
        if (_SetSafeObjectif(ManageMap, Poss, Poss.GetXLikeTabIndex() - 1, Poss.GetYLikeTabIndex(), count, GameInfo, Inv) == HisPossibleToGoObjectif::POSSIBLE) {
            return HisPossibleToGoObjectif::POSSIBLE;
        }
    }
    /* regarde a droite */
    TmpType = ManageMap.GetMappIa()[Poss.GetYLikeTabIndex()][Poss.GetXLikeTabIndex() + 1].get()->GetBlockType();
    if (TmpType != IAMapElemType::UNBREAKABLE and TmpType != IAMapElemType::DAMAGE_ZONE and TmpType != IAMapElemType::IS_BOOM) {
        // printf("Fist Time Not danger zone: x:%ld y:%ld\n", Poss.GetXLikeTabIndex() + 1, Poss.GetYLikeTabIndex());
        // printf("Type:%d\n", static_cast<int>(TmpType));
        if (_SetSafeObjectif(ManageMap, Poss, Poss.GetXLikeTabIndex() + 1, Poss.GetYLikeTabIndex(), count, GameInfo, Inv) == HisPossibleToGoObjectif::POSSIBLE) {
            return HisPossibleToGoObjectif::POSSIBLE;
        }
    }
    /* regarde en haut mais peut etre zone de dager */
    TmpType = ManageMap.GetMappIa()[Poss.GetYLikeTabIndex() - 1][Poss.GetXLikeTabIndex()].get()->GetBlockType();
    if (TmpType != IAMapElemType::UNBREAKABLE) {
        // printf("Fist Time DDanger zone: x:%ld y:%ld\n", Poss.GetXLikeTabIndex(), Poss.GetYLikeTabIndex() - 1);
        // printf("Type:%d\n", static_cast<int>(TmpType));
        if (_SetSafeObjectif(ManageMap, Poss, Poss.GetXLikeTabIndex(), Poss.GetYLikeTabIndex() - 1, count, GameInfo, Inv) == HisPossibleToGoObjectif::POSSIBLE) {
            return HisPossibleToGoObjectif::POSSIBLE;
        }
    }
    /* regarde en bas mais peut etre zone de dager */
    TmpType = ManageMap.GetMappIa()[Poss.GetYLikeTabIndex() + 1][Poss.GetXLikeTabIndex()].get()->GetBlockType();
    if (TmpType != IAMapElemType::UNBREAKABLE) {
        // printf("Fist Time DDanger zone: x:%ld y:%ld\n", Poss.GetXLikeTabIndex(), Poss.GetYLikeTabIndex() + 1);
        // printf("Type:%d\n", static_cast<int>(TmpType));
        if (_SetSafeObjectif(ManageMap, Poss, Poss.GetXLikeTabIndex(), Poss.GetYLikeTabIndex() + 1, count, GameInfo, Inv) == HisPossibleToGoObjectif::POSSIBLE) {
            return HisPossibleToGoObjectif::POSSIBLE;
        }
    }
    /* regarde a gauche mais peut etre zone de dager */
    TmpType = ManageMap.GetMappIa()[Poss.GetYLikeTabIndex()][Poss.GetXLikeTabIndex() - 1].get()->GetBlockType();
    if (TmpType != IAMapElemType::UNBREAKABLE) {
        // printf("Fist Time DDanger zone: x:%ld y:%ld\n", Poss.GetXLikeTabIndex() - 1, Poss.GetYLikeTabIndex());
        // printf("Type:%d\n", static_cast<int>(TmpType));
        if (_SetSafeObjectif(ManageMap, Poss, Poss.GetXLikeTabIndex() - 1, Poss.GetYLikeTabIndex(), count, GameInfo, Inv) == HisPossibleToGoObjectif::POSSIBLE) {
            return HisPossibleToGoObjectif::POSSIBLE;
        }
    }
    /* regarde a droite mais peut etre zone de dager */
    TmpType = ManageMap.GetMappIa()[Poss.GetYLikeTabIndex()][Poss.GetXLikeTabIndex() + 1].get()->GetBlockType();
    if (TmpType != IAMapElemType::UNBREAKABLE) {
        // printf("Fist Time DDanger zone: x:%ld y:%ld\n", Poss.GetXLikeTabIndex() + 1, Poss.GetYLikeTabIndex());
        // printf("Type:%d\n", static_cast<int>(TmpType));
        if (_SetSafeObjectif(ManageMap, Poss, Poss.GetXLikeTabIndex() + 1, Poss.GetYLikeTabIndex(), count, GameInfo, Inv) == HisPossibleToGoObjectif::POSSIBLE) {
            return HisPossibleToGoObjectif::POSSIBLE;
        }
    }
    return HisPossibleToGoObjectif::IMPOSSIBLE;
}
