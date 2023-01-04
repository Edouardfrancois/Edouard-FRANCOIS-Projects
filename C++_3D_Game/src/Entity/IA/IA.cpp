/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** IA
*/

#include <iostream>

#include "IA.hpp"

#include "StaticElem.hpp"

Ia::Ia(const TAllMap& AllMap, const ManageIa& ManageMap, const PassIaInfoGame_t&& GameInfo, size_t x, size_t y) : IEntity(ObjType::OBJENTITY, x, y), _FindArray(AllMap.at(0).size(), AllMap.size())
{
    this->_ConfPlayer.Speed = GameInfo.ConfPlayer.Speed;
    this->_ConfPlayer.MaxItem = GameInfo.ConfPlayer.MaxItem;
    this->_ConfPlayer.Heal = GameInfo.ConfPlayer.Heal;
    _SetObjectif(AllMap, ManageMap, GameInfo);
    this->SetNewPoss(this->GetPoss());
}

/**
 * @brief Check if the ia is in dangerous zone
 * 
 * @param AllMap AllMap
 * @param ManageMap Obj Map danger
 * @return true dangerous Zone
 * @return false not dagerous Zone
 */
bool Ia::_IsADangerousZone(const TAllMap& AllMap, const ManageIa& ManageMap)
{
    const auto& Poss = this->GetPoss();
    const auto& Type = ManageMap.GetMappIa()[Poss.GetYLikeTabIndex()][Poss.GetXLikeTabIndex()].get()->GetBlockType();

    if (Type == IAMapElemType::IS_BOOM or Type == IAMapElemType::DAMAGE_ZONE)
        return true;
    return false;
}

void Ia::_SetNewGoalOffense(const TAllMap& AllMap, const ManageIa& ManageMap)
{
}

void Ia::_SetNewGoalDefense(const TAllMap& AllMap, const ManageIa& ManageMap, const PassIaInfoGame_t& GameInfo)
{
    std::shared_ptr<IDisplay> t = std::make_shared<Spead>(0, 0);
    this->AddItemInventory(t);
    HisPossibleToGoObjectif IsPossible = this->_FindArray._CreateTab(ManageMap, this->GetPoss(), GameInfo, this->_Inventory);
    this->_FindArray._DisplayDebug();
    if (IsPossible == HisPossibleToGoObjectif::IMPOSSIBLE)
        return;
    this->_Mode = _IAMode::DEF;
}

void Ia::_SetObjectif(const TAllMap& AllMap, const ManageIa& ManageMap, const PassIaInfoGame_t& GameInfo)
{
    if (_IsADangerousZone(AllMap, ManageMap))
        _SetNewGoalDefense(AllMap, ManageMap, GameInfo);
    else
        _SetNewGoalOffense(AllMap, ManageMap);
}

void Ia::Run(const TAllMap& AllMap, const ManageIa& ManageMap, const TAllPlayer& AllPlayer, const PassIaInfoGame_t& GameInfo)
{
    if (ManageMap.GetNew())
        _SetObjectif(AllMap, ManageMap, GameInfo);
    // printf("toto\n");
}
