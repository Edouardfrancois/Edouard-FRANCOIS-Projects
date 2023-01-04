/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** entity.hpp
*/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>

class registry;

class Entity
{
    public:
        friend class registry;
        size_t get_size() {return(_size);}

    private:
        explicit Entity(size_t size) : _size(size) {};
        size_t _size;
};

#endif