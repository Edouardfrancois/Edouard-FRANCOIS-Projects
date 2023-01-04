/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** FindPath
*/

#include "IA.hpp"

FindArray_s::FindArray_s(size_t SizeX, size_t SizeY)
{
    std::vector<int> Tmp;

    for (size_t y = 0; y != SizeY; ++y) {
        for (size_t x = 0; x != SizeX; ++x)
            Tmp.push_back(0);
        this->_Array.push_back(Tmp);
        Tmp.clear();
    }
}

HisPossibleToGoObjectif FindArray_s::_DoWeHaveTimeToGotoObjecif(const Poss_t& Poss, const PassIaInfoGame_t& GameInfo, const TInveotry& Inv)
{
    size_t NbToParcoure = ((this->_Count - 1) * _SizeOneMapPiece) + 1;

    if (this->_Array[Poss.GetYLikeTabIndex() - 1][Poss.GetXLikeTabIndex()] == 1 or
        this->_Array[Poss.GetYLikeTabIndex() + 1][Poss.GetXLikeTabIndex()])
        NbToParcoure += Poss.GetY() % _SizeOneMapPiece;
    else
        NbToParcoure += Poss.GetX() % _SizeOneMapPiece;
    float TimeToParcour = static_cast<float>(NbToParcoure) / GameInfo.ConfPlayer.Speed;
    // printf("NbToParcoure: %ld, TimeToParcour: %f\n", NbToParcoure, TimeToParcour);
    if (TimeToParcour > GameInfo.ConfBomm.TimeBeaforeExplose) {
        TimeToParcour = static_cast<float>(NbToParcoure) / (GameInfo.ConfPlayer.Speed + GameInfo.ConfSpeed.AddSpeed);
        if (TimeToParcour < GameInfo.ConfBomm.TimeBeaforeExplose) {
            for (const auto& Elem : Inv)
                if (Elem.get()->GetType() == ObjType::OBJSPEED) {
                    // printf("Possible wive bost\n");
                    return HisPossibleToGoObjectif::POSSIBLE_WIVE_BOST;
                }
        }
        // printf("Imposible wive bost\n");
        return HisPossibleToGoObjectif::IMPOSSIBLE;
    }
    // printf("POSSIBLE\n");
    return HisPossibleToGoObjectif::POSSIBLE;
}

HisPossibleToGoObjectif FindArray_s::_SetSafeObjectif(const ManageIa& ManageMap, const Poss_t& Poss, size_t x, size_t y, size_t& count, const PassIaInfoGame_t& GameInfo, const TInveotry& Inv)
{
    // _DisplayDebug();
    const auto TypeMe = this->_Array[y][x];
    // printf("count:%ld, x: %ld,y: %ld, type: %d.\n", count, x, y, TypeMe);
    switch (TypeMe) {
        case static_cast<int>(IAMapElemType::NOFINK):
            {
                this->_Array[y][x] = ++count;
                const auto& RetWeCan = _DoWeHaveTimeToGotoObjecif(Poss, GameInfo, Inv);
                if (RetWeCan == HisPossibleToGoObjectif::IMPOSSIBLE) {
                    this->_Array[y][x] = TypeMe;
                    --count;
                    return HisPossibleToGoObjectif::IMPOSSIBLE;
                } else
                    return RetWeCan;
                break;
            }
        case static_cast<int>(IAMapElemType::DAMAGE_ZONE):
            this->_Array[y][x] = ++count;
            if (_DoWeHaveTimeToGotoObjecif(Poss, GameInfo, Inv) == HisPossibleToGoObjectif::IMPOSSIBLE) {
                this->_Array[y][x] = TypeMe;
                --count;
                return HisPossibleToGoObjectif::IMPOSSIBLE;
            }
            // _DisplayDebug();
            break;
    }
    auto ToRet = _IsSafeZoneNext(ManageMap, Poss, x, y, count, GameInfo, Inv);
    if (ToRet != HisPossibleToGoObjectif::IMPOSSIBLE)
        return ToRet;
    ToRet = _IsGoInNotSafeZone(ManageMap, Poss, x, y, count, GameInfo, Inv);
    if (ToRet != HisPossibleToGoObjectif::IMPOSSIBLE)
        return ToRet;
    this->_Array[y][x] = TypeMe;
    --count;
    return HisPossibleToGoObjectif::IMPOSSIBLE;
}

HisPossibleToGoObjectif FindArray_s::_CreateTab(const ManageIa& ManageMap, const Poss_t& Poss, const PassIaInfoGame_t& GameInfo, const TInveotry& Inv)
{
    const auto& IaMap = ManageMap.GetMappIa();

    for (const auto& Line : IaMap) {
        for (const auto& Elem : Line) {
            switch (Elem.get()->GetBlockType())
            {
                case IAMapElemType::NOFINK:
                    this->_Array[Elem.get()->GetYLikeTabIndex()][Elem.get()->GetXLikeTabIndex()] = static_cast<int>(IAMapElemType::NOFINK);
                    break;
                case IAMapElemType::UNBREAKABLE:
                    this->_Array[Elem.get()->GetYLikeTabIndex()][Elem.get()->GetXLikeTabIndex()] = static_cast<int>(IAMapElemType::UNBREAKABLE);
                    break;
                case IAMapElemType::DAMAGE_ZONE:
                case IAMapElemType::IS_BOOM:
                    this->_Array[Elem.get()->GetYLikeTabIndex()][Elem.get()->GetXLikeTabIndex()] = static_cast<int>(IAMapElemType::DAMAGE_ZONE);
                break;
                default:
                    break;
            }
        }
    }
    this->_Array[Poss.GetYLikeTabIndex()][Poss.GetXLikeTabIndex()] = static_cast<int>(IAMapElemType::ME);
    // _DisplayDebug();
    this->_Count = 0;
    return _FindBestWaiToBegin(ManageMap, Poss, this->_Count, GameInfo, Inv);
}

void FindArray_s::_DisplayDebug()
{
    static size_t contnb = 0;

    printf("------------%ld------------\n", contnb++);
    for (const auto& Line : this->_Array) {
        for (const auto& Elem : Line) {
            if (Elem == 0) {
                printf(" %d ", Elem);
            } else if (Elem == -1) {
                printf("[39m[38;5;33m%d \033[40;37;0m", Elem);
            } else if (Elem >= 1 and Elem <= 9) {
                printf("\e[91;5m %d \033[40;37;0m", Elem);
            } else if (Elem >= 10)
                printf("\e[91;5m%d \033[40;37;0m", Elem);
            else
                printf("%d ", Elem);
        }
        printf("\n");
    }
    printf("--------------------------\n");
}
