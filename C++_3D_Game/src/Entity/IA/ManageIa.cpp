/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** ManageIa
*/

#include "Indi.hpp"

void ManageIa::_SetDangerZoneLeft(const TAllMap& AllMap, const int y, int x)
{
    --x;
    for (size_t tmp = 0; tmp != 5; ++tmp, --x) {
        if (x == -1)
            x = AllMap[0].size() - 1;
        if (AllMap[y][x].get()->IsWallInPile())
            break;
        if (this->_IAMapp[y][x].get()->GetBlockType() == IAMapElemType::IS_BOOM)
            continue;
        this->_IAMapp[y][x].get()->SetBlockType(IAMapElemType::DAMAGE_ZONE);
    }
}

void ManageIa::_SetDangerZoneRight(const TAllMap& AllMap, const int y, int x)
{
    for (size_t tmp = 0; tmp != 5; ++tmp, ++x) {
        if (static_cast<size_t>(x) > AllMap[0].size())
            x = 0;
        if (AllMap[y][x].get()->IsWallInPile())
            break;
        if (this->_IAMapp[y][x].get()->GetBlockType() == IAMapElemType::IS_BOOM)
            continue;
        this->_IAMapp[y][x].get()->SetBlockType(IAMapElemType::DAMAGE_ZONE);
    }
}

void ManageIa::_SetDangerZoneDown(const TAllMap& AllMap, int y, const int x)
{
    ++y;
    for (size_t tmp = 0; tmp != 4; ++tmp, ++y) {
        if (static_cast<size_t>(y) > AllMap.size())
            y = 0;
        if (AllMap[y][x].get()->IsWallInPile())
            break;
        if (this->_IAMapp[y][x].get()->GetBlockType() == IAMapElemType::IS_BOOM)
            continue;
        this->_IAMapp[y][x].get()->SetBlockType(IAMapElemType::DAMAGE_ZONE);
    }
}


void ManageIa::_SetDangerZoneUp(const TAllMap& AllMap, int y, const int x)
{
    --y;
    for (size_t tmp = 4; tmp != 0; --tmp) {
        if (y == -1)
            y = AllMap.size() - 1;
        if (AllMap[y][x].get()->IsWallInPile())
            break;
        if (this->_IAMapp[y][x].get()->GetBlockType() == IAMapElemType::IS_BOOM)
            continue;
        this->_IAMapp[y--][x].get()->SetBlockType(IAMapElemType::DAMAGE_ZONE);
    }
}

void ManageIa::_FillMapDanger(const TAllMap& AllMap, int y, int x)
{
    _SetDangerZoneUp(AllMap, y, x);
    _SetDangerZoneDown(AllMap, y, x);
    _SetDangerZoneRight(AllMap, y, x);
    _SetDangerZoneLeft(AllMap, y, x);
}

/**
 * @brief Setup DAnger Zone
 * 
 * @param AllMap 
 */
void ManageIa::_SetDangerZone(const TAllMap& AllMap)
{
    for (auto Line : AllMap) {
        for (auto Elem : Line)
            if (Elem.get()->IsBombAtThisPile())
                _FillMapDanger(AllMap, Elem.get()->GetPoss().GetYLikeTabIndex(), \
                    Elem.get()->GetPoss().GetXLikeTabIndex());
    }
}

void ManageIa::_UpdateIaMap(const TAllMap& AllMap)
{
    for (const auto& Line : AllMap) {
        for (const auto& Elem : Line) {
            if (Elem.get()->GetPile().empty())
                this->_IAMapp[Elem.get()->GetPoss().GetYLikeTabIndex()][Elem.get()->GetPoss().GetXLikeTabIndex()].get()->SetBlockType(IAMapElemType::NOFINK);
            else if (this->_IAMapp[Elem.get()->GetPoss().GetYLikeTabIndex()][Elem.get()->GetPoss().GetXLikeTabIndex()].get()->GetBlockType() == IAMapElemType::UNBREAKABLE)
                continue;
            else if (Elem.get()->IsBombAtThisPile())
                this->_IAMapp[Elem.get()->GetPoss().GetYLikeTabIndex()][Elem.get()->GetPoss().GetXLikeTabIndex()].get()->SetBlockType(IAMapElemType::IS_BOOM);
            else if (Elem.get()->IsFireAtThisPile())
                this->_IAMapp[Elem.get()->GetPoss().GetYLikeTabIndex()][Elem.get()->GetPoss().GetXLikeTabIndex()].get()->SetBlockType(IAMapElemType::DAMAGE_ZONE);
            else
                this->_IAMapp[Elem.get()->GetPoss().GetYLikeTabIndex()][Elem.get()->GetPoss().GetXLikeTabIndex()].get()->SetBlockType(IAMapElemType::NOFINK);
        }
    }
    _SetDangerZone(AllMap);
    SetNew(true);
    __DebugPrintMapWall(this->_IAMapp);
}

/**
 * @brief set up the map that contain the walls
 * 
 * @param AllMap All the Map
 */
void ManageIa::_InitMappWall(const TAllMap& AllMap)
{
    std::vector<std::shared_ptr<IaMap_t>> Tmp;

    this->_IAMapp.clear();
    for (std::size_t y = 0; y != GetAllMapSizeY(); ++y) {
        for (std::size_t x = 0; x != GetAllMapSizeX(); ++x) {
            if (AllMap[y][x].get()->GetPile().empty())
                Tmp.push_back(std::make_shared<IaMap_t>(x, y, IAMapElemType::NOFINK));
            else if (AllMap[y][x].get()->GetPile()[0].get()->GetType() == ObjType::OBJBLOC)
                Tmp.push_back(std::make_shared<IaMap_t>(x, y, IAMapElemType::UNBREAKABLE));
            else if (AllMap[y][x].get()->GetPile()[0].get()->GetType() == ObjType::OBJBOMB)
                Tmp.push_back(std::make_shared<IaMap_t>(x, y, IAMapElemType::IS_BOOM));
            else
                Tmp.push_back(std::make_shared<IaMap_t>(x, y, IAMapElemType::NOFINK));
        }
        this->_IAMapp.push_back(Tmp);
        Tmp.clear();
    }
    _SetDangerZone(AllMap);
    __DebugPrintMapWall(this->_IAMapp);
    SetNew(true);
}
