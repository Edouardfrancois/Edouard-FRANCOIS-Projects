/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** IEntity
*/

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <vector>
#include <memory>

#include "IObject.hpp"
#include "exeption.hpp"
using TInveotry = std::vector<std::shared_ptr<IObject>>;
#include "IDisplay.hpp"
#include "Timer.hpp"
#include "JsonData.hpp"
#include "Touch.hpp"
#include "Model.hpp"

/**
 * @brief All the Player and Ia
 * 
 */

typedef struct turn_t {
    MyRaylib::Action LastAction;
    bool turn;
} turn;

class IEntity : public IDisplay { 
    public:
        IEntity(ObjType Type, size_t x, size_t y) : IDisplay(Type, x, y), _OldPos(0, 0), _NewPos(0, 0) , Model("assets/indie_bomberman_model_1.iqm", 
        "assets/indie_bomberman_layout_1.png") {};
        ~IEntity() = default;
        /* Geteur */
        const Poss_t& GetOldPoss() {return this->_OldPos;}
        Poss_t& GetNewPoss() {return this->_NewPos;}
        const TInveotry& Getinveotry() const { return this->_Inventory;}
        /* Seteur */
        void SetOldPoss(size_t NewY, size_t NewX);
        void SetNewPoss(const Poss_t& NewPoss) {this->_NewPos = NewPoss;}
        Poss_t& GetNewX() {return this->_NewPos;}
        void AddItemInventory(std::shared_ptr<IDisplay>& Item);
    public:
        size_t Life;
        bool AllREadyLoseLife = false;
        MyRaylib::MyModel Model;
        turn LastAction = {MyRaylib::Action::Nothing, false};

    protected:
        TInveotry _Inventory;
        EntityConf_t _ConfPlayer;
        std::shared_ptr<IObject> _ObjUse;
        bool _IsUse = false;
    private:
        Poss_t _OldPos;
        Poss_t _NewPos;
};

#endif /* !IENTITY_HPP_ */

