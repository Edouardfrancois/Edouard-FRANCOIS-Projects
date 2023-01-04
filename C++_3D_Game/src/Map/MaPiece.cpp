/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** MaPiece
*/

#include "MapPiece.hpp"
#include "IEntity.hpp"

/**
 * @brief Construct a new Map Piece:: Map Piece object
 * 
 * @param x Will be LikeTabIndex _SizeOneMapPiece
 * @param y Will be LikeTabIndex _SizeOneMapPiece
 */
MapPiece::MapPiece(size_t x, size_t y) : _Poss(x * _SizeOneMapPiece, y * _SizeOneMapPiece)
{
}

/**
 * @brief Get the pile
 * 
 * @return TypePile& 
 */
const TypePile& MapPiece::GetPile()
{
    return this->_Pile;
}

/**
 * @brief Get poss of MapPiece
 * 
 * @return Poss_t& 
 */
const Poss_t& MapPiece::GetPoss() const
{
    return this->_Poss;
}

/**
 * @brief Get Index in pile
 * 
 * @param Element the elem to find
 * @return int the index -1 if not found
 */
int MapPiece::GetIndexInPile(std::shared_ptr<IDisplay>& Element) const
{
    int index = 0;

    for (const auto& i : this->_Pile)
        if (Element.get() == i.get())
            return index;
    return -1;
}

/**
 * @brief Check if have wall or bloc in the pile
 * 
 * @return true 
 * @return false 
 */
bool MapPiece::IsWallInPile() const
{
    for (auto elem : this->_Pile)
        if (elem.get()->GetType() == ObjType::OBJBLOC || elem.get()->GetType() == ObjType::OBJWALL)
            return true;
    return false;
}

/**
 * @brief Check if there is a FireUp on the pile
 * 
 * @return true 
 * @return false 
 */
bool MapPiece::IsFireAtThisPile() const
{
    for (auto elem : this->_Pile)
        if (elem.get()->GetType() == ObjType::OBJFIRE)
            return true;
    return false;
}

/**
 * @brief Check if there is a SpeadUp on the pile
 * 
 * @return true 
 * @return false 
 */
bool MapPiece::IsSpeadAtThisPile() const
{
    for (auto elem : this->_Pile)
        if (elem.get()->GetType() == ObjType::OBJSPEED)
            return true;
    return false;
}

/**
 * @brief Check if there is a HealUp on the pile
 * 
 * @return true 
 * @return false 
 */
bool MapPiece::IsHealAtThisPile() const
{
    for (auto elem : this->_Pile)
        if (elem.get()->GetType() == ObjType::OBJHEAL)
            return true;
    return false;
}

/** 
* @brief return true if there is a bombe in the pile sended to the function
*/
bool MapPiece::IsBombAtThisPile() const
{
    for (auto obj : this->_Pile)
        if (obj.get()->GetType() == ObjType::OBJBOMB)
            return (true);
    return (false);
}

/**
 * @brief Add elem to pile
 * 
 * @param ToAdd 
 * @throw Exception::TryPushBackWhenHaveWall Push back up of a wall or bloc
 */
void MapPiece::PushBack(std::shared_ptr<IDisplay> ToAdd)
{
    if (IsWallInPile())
        throw Exception::TryPushBackWhenHaveWall();
    this->_Pile.push_back(ToAdd);
}

/**
 * @brief Add elem to pile
 * 
 * @param ToAdd 
 */
void MapPiece::PushBackNotThrow(std::shared_ptr<IDisplay> ToAdd)
{
    this->_Pile.push_back(ToAdd);
}

/**
 * @brief Remouve a Object and return it by index
 * 
 * @param index 
 * @return std::shared_ptr<IDisplay> 
 */
std::shared_ptr<IDisplay> MapPiece::RemouveObject(size_t index)
{
    std::shared_ptr<IDisplay> ToRet;

    for (TypePile::iterator i = this->_Pile.begin(); i != _Pile.end(); ++i) {
        if (static_cast<size_t>(std::distance(this->_Pile.begin(), i)) == index) {
            ToRet = *i.base();
            this->_Pile.erase(i);
            break;
        }
    }
    return ToRet;
}

/**
 * @brief Remouve The element in the pile and return it
 * 
 * @param Element 
 * @return std::shared_ptr<IDisplay> 
 */
std::shared_ptr<IDisplay> MapPiece::RemouveObject(std::shared_ptr<IDisplay>& Element)
{
    std::shared_ptr<IDisplay> ToRet;

    if (this->GetIndexInPile(Element) == -1)
        throw Exception::ObjectNotInPile();
    for (TypePile::iterator i = this->_Pile.begin(); i != _Pile.end(); ++i) {
        if (i.base()->get() == Element.get()) {
            ToRet = *i.base();
            this->_Pile.erase(i);
            break;
        }
    }
    return ToRet;
}
