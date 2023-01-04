
/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** Indi
*/

#ifndef INDI_HPP_
#define INDI_HPP_

#include <array>

#include "IEntity.hpp"
#include "MapPiece.hpp"
#include "ManageIa.hpp"
#include "Touch.hpp"
#include "Json.hpp"
#include "Graphic.hpp"
#include "JsonData.hpp"
#include "IA.hpp"
#include "Timer.hpp"
#include "StaticElem.hpp"

using TAllPlayer = std::vector<std::shared_ptr<IEntity>>;

using TAllIa = std::vector<std::shared_ptr<Ia>>;

using TAllStrMap = std::vector<std::vector<std::string>>;

class JsonConfig {
    public:
        JsonConfig(std::string&& filename = "conf.json") : _Js(filename) {}
        ~JsonConfig() = default;
        BommConf_t _ConfBomm;
    private:
        void _CheckMapJson();
        void _SetEntityConf();
        void _SetItemConf();
    protected:
        bool _SetupAllConfig();
        Json::Json& _GetMapTab() {return this->_Js["config"]["map"]; }
        Json::Json& _GetTexture() {return this->_Js["Texture"];}
    protected:
        TAllStrMap _AllMapString;
        EntityConf_t _ConfPlayer;
        Speed_t _ConfSpeed;
    private:
        Json::Json _Js;
};

class Indi : public ManageIa, public JsonConfig {
    public:
        Indi();
        ~Indi() = default;
    private:
        void _ChangePileIfnecessary(std::shared_ptr<IDisplay>& Entity, size_t BeaforeX, size_t BeaforeY);
        void _CheckMouveIsPossible(const Poss_t& ActuallyPoss, size_t NewX, size_t NewY) const;
        void _MouveEntityX(std::shared_ptr<IDisplay> Entity, size_t NewX, bool HaveToDivise);
        void _MouveEntityY(std::shared_ptr<IDisplay> Entity, size_t NewY, bool HaveToDivise);
        void _MouveEntityXY(std::shared_ptr<IDisplay> Entity, size_t NewX, size_t NewY, bool HaveToDivise);
        void _SetObjAtPoss(std::shared_ptr<IDisplay> ToPut);
        void _SetUpRoundm();
        void _MovePlayer();
        void _MoveRight(MyRaylib::Action& act);

        void _MangeLife(std::shared_ptr<IEntity>& Entity, const bool isIa);

        void _MapSetDangerZoneLeft(const TAllMap& AllMap, const int y, int x);
        void _MapSetDangerZoneRight(const TAllMap& AllMap, const int y, int x);
        void _MapSetExploseZoneDown(TAllMap& AllMap, int y, const int x);
        void _MapSetExploseZoneUp(TAllMap& AllMap, int y, const int x);

        void _ExploseBomb(Bomb& B, const size_t & index, TypePile &MapPiece);
        void _ManageBoomAndFire();
        void _PutABoom(size_t y, size_t x);

        void _GenerateAllMapByIndexInJsonFile(size_t index);
        void SetUpGraphic();
        void _PutIaOnSpawn(const size_t IndexSpawnInTab);
        void _PutPlayerOnSpawn(const size_t IndexSpawnInTab, size_t IndexTouch);
    public:
        const TAllMap& GetAllMap() const { return this->_AllMap;}
        size_t GetAllMapSizeX() {return this->_AllMap.at(0).size();}
        size_t GetAllMapSizeY() {return this->_AllMap.size();}
    public:
        void SetUpMap(size_t NbPlayer, size_t Map);
    private:
        void _MouveAll();
    public:
        void Run();
        // bool Menu();
        // bool Game();
    private:
        TAllMap _AllMap;
        TAllPlayer _AllPlayer;
        TAllIa _AllIa;
        std::vector<std::shared_ptr<IDisplay>> _AllSpawn;
        std::array<std::vector<char>, 4> _Touch;
        Graphic::Graphic _graphic;
        Timer _Timer;
};

void __DebugSizeAllMap(const TAllMap& _AllMap);

#define DEBUG_BALISE_BEGIN std::cerr << "--[DEBUG]--" << std::endl;
#define DEBUG_BALISE_END std::cerr << "--[END DEBUG]--" << std::endl;

#endif /* !INDI_HPP_ */
