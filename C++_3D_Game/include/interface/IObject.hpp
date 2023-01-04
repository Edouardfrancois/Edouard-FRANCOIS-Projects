/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** IObject
*/

#ifndef IOBJECT_HPP_
#define IOBJECT_HPP_

#include "IDisplay.hpp"
#include "IEntity.hpp"

/**
 * @brief All the static elements
 * 
 */
class IObject : public IDisplay {
    friend class IEntity;
    public:
        IObject(ObjType Type, size_t x, size_t y) : IDisplay(Type, x, y) {};
        ~IObject() = default;
    private:
        // virtual void UseThisItem() = 0;
};

#endif /* !IOBJECT_HPP_ */
