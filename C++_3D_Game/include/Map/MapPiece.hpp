/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** MapPiece
*/

#ifndef MAPPIECE_HPP_
#define MAPPIECE_HPP_

#include <vector>
#include <memory>

#include "exeption.hpp"
#include "IDisplay.hpp"

using TypePile = std::vector<std::shared_ptr<IDisplay>>;

class MapPiece {
    public:
        MapPiece(size_t x, size_t y);
        ~MapPiece() = default;
    /* Geteur */
    public:
        const TypePile& GetPile();
        const Poss_t& GetPoss() const;
        int GetIndexInPile(std::shared_ptr<IDisplay>& Element) const;
    /* Checker */
    public:
        bool IsWallInPile() const;
        bool IsBombAtThisPile() const;
        bool IsFireAtThisPile() const;
        bool IsSpeadAtThisPile() const;
        bool IsHealAtThisPile() const;
        
    /* Seteur */
    public:
        void PushBackNotThrow(std::shared_ptr<IDisplay> ToAdd);
        void PushBack(std::shared_ptr<IDisplay> ToAdd);
        /**
         * @brief Put a New Object in the _Pile: the elem is Create
         * 
         * @tparam T 
         */
        template<typename T>
        void PutNewObj()
        {
            if (IsWallInPile())
                throw Exception::ImposibleToPutObj();
            this->_Pile.push_back(std::make_shared<T>(this->_Poss.GetX(), this->_Poss.GetY()));
        }
    /* Deleter */
    public:
        std::shared_ptr<IDisplay> RemouveObject(size_t index);
        std::shared_ptr<IDisplay> RemouveObject(std::shared_ptr<IDisplay>& Element);
    private:
        TypePile _Pile;
        const Poss_t _Poss;
};

#endif /* !MAPPIECE_HPP_ */
