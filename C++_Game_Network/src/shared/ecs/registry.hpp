/*
** EPITECH PROJECT, 2022
** boostrap
** File description:
** step1
*/

#ifndef STEP1_HPP_
#define STEP1_HPP_

#include <optional>
#include <vector>
#include <typeindex>
#include <any>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <functional>
#include <queue>

#include "SparseArray.hpp"
#include "Entity.hpp"

class registry
{
public:
    template <class Component>
    sparse_array<Component> &register_component()
    {
        _components_arrays[std::type_index(typeid(Component))] = (sparse_array<Component>());

            this->del_funcs.push_back(std::function<void(registry &r, Entity const &e)>([=] (registry &r, Entity const &e) {
                r.remove_component<Component>(e);
            }));
            return (std::any_cast<sparse_array<Component> &>
            (_components_arrays[std::type_index(typeid(Component))]));
        }
        template<class Component>
        sparse_array<Component> &get_components() {
            if (!_components_arrays[std::type_index(typeid(Component))].has_value()) {
                register_component<Component>();
            }
            return (std::any_cast<sparse_array<Component> &>
            (_components_arrays[std::type_index(typeid(Component))]));
        }
        template<class Component>
        sparse_array<Component> const &get_components() const {
            if (!_components_arrays.at(std::type_index(typeid(Component))).has_value()) {
                register_component<Component>();
            }
            return (std::any_cast<sparse_array<Component> const &>
            (_components_arrays.at(std::type_index(typeid(Component)))));
        }
        
        Entity spawn_entity() {
            if (this->_free_entity.size()) {
                Entity res = this->_free_entity.front();
                _free_entity.pop();
                return res;
            }
            return Entity(_count_entity++);
        }

    Entity entity_from_index(std::size_t idx)
    {
        if (idx > _count_entity) {
            for (size_t i = _count_entity; i < idx; i += 1) {
                this->_free_entity.push(Entity(i));
            }
            _count_entity = idx;
            return Entity(_count_entity++);
        }
        return Entity(idx);
    }

    void kill_entity(Entity const &e)
    {
        for (size_t i = 0; this->del_funcs.size() > i; i += 1)
        {
            this->del_funcs[i](std::forward<registry &>(*this), (e));
        }
        this->_free_entity.push(Entity(e));
    }


    /*Component avait de base 2 & on a enlever une car on ne 
    pouvais pas mettre des variable */
    template <typename Component>
    typename sparse_array<Component>::reference_type add_component(Entity const &to, Component &&c)
    {
        if (!_components_arrays[std::type_index(typeid(Component))].has_value())
        {
            register_component<Component>();
        }
        get_components<Component>().insert_at(to._size, c);
        return this->get_components<Component>()[to._size];
    }

    template <typename Component, typename... Params>
    typename sparse_array<Component>::reference_type emplace_component(Entity const &to, Params &&...p)
    {
        if (!_components_arrays[std::type_index(typeid(Component))].has_value())
        {
            register_component<Component>();
        }
        this->get_components<Component>().emplace_at(to._size, std::forward<Params>(p)...);
        return this->get_components<Component>()[to._size];
    }

    template <typename Component>
    void remove_component(Entity const &from)
    {
        this->get_components<Component>().erase(from._size);
    }

private:
    size_t _count_entity = 0;
    std::queue<Entity> _free_entity;
    // std::vector<std::type_index> _dict_type;
    std::vector<std::function<void(registry &, Entity const &)>> del_funcs;
    std::unordered_map<std::type_index, std::any> _components_arrays;
};

#endif /* !STEP1_HPP_ */

// registry contient un vector de sparse array qui sont eux-même des vector
// les idx des sparse array corespondent aux entitées
// les sparse array peuvent contenire n'importe quel type de donnée
// ils s'agrandissent en fonction de l'index choisit pour mettre la data