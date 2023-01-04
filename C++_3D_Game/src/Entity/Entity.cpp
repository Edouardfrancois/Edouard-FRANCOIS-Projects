/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Entity
*/

#include "IEntity.hpp"

/**
 * @brief 
 * 
 * @param NewY 
 * @param NewX 
 */
void IEntity::SetOldPoss(size_t NewY, size_t NewX) {
    this->_OldPos.SetX(NewX);
    this->_OldPos.SetY(NewY);
}

/**
 * @brief Add intem In Inventory
 * 
 * @throw ImPossibleToGiveEntityInsideEntity
 * @param Item 
 */
void IEntity::AddItemInventory(std::shared_ptr<IDisplay>& Item) {
    if (Item.get()->GetType() == ObjType::OBJENTITY)
        throw Exception::ImPossibleToGiveEntityInsideEntity();
    this->_Inventory.push_back(std::dynamic_pointer_cast<IObject>(Item));
}
