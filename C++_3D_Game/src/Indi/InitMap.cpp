/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** InitMap
*/

#include <iostream>
#include <cmath>

#include "Indi.hpp"
#include "StaticElem.hpp"
#include "Player.hpp"
#include "IA.hpp"
#include "Touch.hpp"
#include "Menu.hpp"
#include "IEntity.hpp"

Indi::Indi(): _graphic()
{
    this->_Touch[0] = {'m', 'w', 'x', 'z', 's', 'q', 'd'};
    this->_Touch[1] = {'a', 'w', 'w', 'z', 's', 'q', 'd'};
    this->_Touch[2] = {'a', 'w', 'w', 'z', 's', 'q', 'd'};
    this->_Touch[3] = {'a', 'w', 'w', 'z', 's', 'q', 'd'};
}

/**
 * @brief Check if Entity Can Mouve
 * @warning ALL calcul have to be division (like index for a tab)
 * 
 * @param ActuallyPoss 
 * @param NewX 
 * @param NewY 
 */
void Indi::_CheckMouveIsPossible(const Poss_t& ActuallyPoss __attribute__((unused)), size_t NewX, size_t NewY) const
{
    if (this->_AllMap[NewY][NewX].get()->IsWallInPile())
        throw Exception::ImpossibleMouve("Can't mouve on a Wall");
}

void Indi::_ChangePileIfnecessary(std::shared_ptr<IDisplay>& Entity, size_t BeaforeX, size_t BeaforeY)
{
    const Poss_t& Poss = Entity.get()->GetPoss();

    if (this->_AllMap[Poss.GetYLikeTabIndex()][Poss.GetXLikeTabIndex()].get()->GetIndexInPile(Entity) != -1)
        return;
    std::shared_ptr<IDisplay> Tmp = this->_AllMap[BeaforeY][BeaforeX].get()->RemouveObject(Entity);
    this->_AllMap[Poss.GetYLikeTabIndex()][Poss.GetXLikeTabIndex()].get()->PushBack(Tmp);
}

/**
 * @brief 
 * 
 * @param Entity the entity
 * @param NewX new X
 * @param HaveToDivise if HaveToDivise = false then set this->_AllMap[y][x]
 * @param HaveToDivise if HaveToDivise = true then set this->_AllMap[y / _SizeOneMapPiece][x / _SizeOneMapPiece]
 * @throw Exception::CanOnlyMouveObjEntity can only mouve entity
 */
void Indi::_MouveEntityX(std::shared_ptr<IDisplay> Entity, size_t NewX, bool HaveToDivise)
{
    size_t BeaforeX;
    size_t BeaforeY;

    if (Entity.get()->GetType() != ObjType::OBJENTITY)
        throw Exception::CanOnlyMouveObjEntity();
    BeaforeX = Entity.get()->GetPoss().GetXLikeTabIndex();
    BeaforeY = Entity.get()->GetPoss().GetYLikeTabIndex();
    if (NewX / _SizeOneMapPiece > GetAllMapSizeX())
        NewX = 0;
    _CheckMouveIsPossible(Entity.get()->GetPoss(), \
    HaveToDivise ? NewX / _SizeOneMapPiece : NewX, Entity.get()->GetPoss().GetYLikeTabIndex());
    if (HaveToDivise) {
        Entity.get()->GetPoss().SetX(NewX);
    } else
        Entity.get()->GetPoss().SetXLikeTabIndex(NewX);
    _ChangePileIfnecessary(Entity, BeaforeX, BeaforeY);
    IEntity& E = *dynamic_cast<IEntity *>(Entity.get());
    E.SetOldPoss(Entity.get()->GetPoss().GetY(), Entity.get()->GetPoss().GetX());
}

/**
 * @brief 
 * 
 * @param Entity the entity
 * @param NewY new Y
 * @param HaveToDivise if HaveToDivise = false then set this->_AllMap[y][x]
 * @param HaveToDivise if HaveToDivise = true then set this->_AllMap[y / _SizeOneMapPiece][x / _SizeOneMapPiece]
 * @throw Exception::CanOnlyMouveObjEntity can only mouve entity
 */
void Indi::_MouveEntityY(std::shared_ptr<IDisplay> Entity, size_t NewY, bool HaveToDivise)
{
    size_t BeaforeX;
    size_t BeaforeY;

    if (Entity.get()->GetType() != ObjType::OBJENTITY)
        throw Exception::CanOnlyMouveObjEntity();
    BeaforeX = Entity.get()->GetPoss().GetXLikeTabIndex();
    BeaforeY = Entity.get()->GetPoss().GetYLikeTabIndex();
    if (NewY / _SizeOneMapPiece > GetAllMapSizeY())
        NewY = 0;
    _CheckMouveIsPossible(Entity.get()->GetPoss(), \
    Entity.get()->GetPoss().GetXLikeTabIndex(), HaveToDivise ? NewY / _SizeOneMapPiece : NewY);
    if (HaveToDivise) {
        Entity.get()->GetPoss().SetY(NewY);
    } else
        Entity.get()->GetPoss().SetYLikeTabIndex(NewY);
    _ChangePileIfnecessary(Entity, BeaforeX, BeaforeY);
    IEntity& E = *dynamic_cast<IEntity *>(Entity.get());
    E.SetOldPoss(Entity.get()->GetPoss().GetY(), Entity.get()->GetPoss().GetX());
}

/**
 * @brief 
 * 
 * @param Entity the entity
 * @param NewX new X
 * @param NewY new Y
 * @param HaveToDivise if HaveToDivise = false then set this->_AllMap[y][x]
 * @param HaveToDivise if HaveToDivise = true then set this->_AllMap[y / _SizeOneMapPiece][x / _SizeOneMapPiece]
 * @throw Exception::CanOnlyMouveObjEntity can only mouve entity
 */
void Indi::_MouveEntityXY(std::shared_ptr<IDisplay> Entity, size_t NewX, size_t NewY, bool HaveToDivise)
{
    size_t BeaforeX;
    size_t BeaforeY;

    if (Entity.get()->GetType() != ObjType::OBJENTITY)
        throw Exception::CanOnlyMouveObjEntity();
    BeaforeX = Entity.get()->GetPoss().GetXLikeTabIndex();
    BeaforeY = Entity.get()->GetPoss().GetYLikeTabIndex();
    if (NewY / _SizeOneMapPiece > GetAllMapSizeY())
        NewY = 0;
    if (NewX / _SizeOneMapPiece > GetAllMapSizeX())
        NewX = 0;
    _CheckMouveIsPossible(Entity.get()->GetPoss(), \
    HaveToDivise ? NewX / _SizeOneMapPiece : NewX, HaveToDivise ? NewY / _SizeOneMapPiece : NewY);
    if (HaveToDivise) {
        Entity.get()->GetPoss().SetXY(NewX, NewY);
    } else
        Entity.get()->GetPoss().SetXYLikeTabIndex(NewX, NewY);
    _ChangePileIfnecessary(Entity, BeaforeX, BeaforeY);
    IEntity& E = *dynamic_cast<IEntity *>(Entity.get());
    E.SetOldPoss(Entity.get()->GetPoss().GetY(), Entity.get()->GetPoss().GetX());
}

/**
 * @brief Set Obj In the Map
 * 
 * @param ToPut 
 */
void Indi::_SetObjAtPoss(std::shared_ptr<IDisplay> ToPut)
{
    const auto& Poss = ToPut.get()->GetPoss();

    this->_AllMap[Poss.GetYLikeTabIndex()][Poss.GetXLikeTabIndex()].get()->PushBack(ToPut);
}

/**
 * @brief Generate _AllMap by index
 * 
 * @param index the index
 * @throw Exception::RongIndexForGenerateMap rong index in json file
 * @throw Exception::ToMushSpawn max 4 spawn
 */
void Indi::_GenerateAllMapByIndexInJsonFile(size_t index)
{
    if (index >= this->_GetMapTab().GetSize())
        throw Exception::RongIndexForGenerateMap();

    this->_AllMap.clear();
    Json::Json& Tab = this->_GetMapTab()[index];
    std::vector<std::shared_ptr<MapPiece>> Tmp;

    for (size_t y = 0; y != Tab.GetSize(); ++y) {
        size_t x = 0;
        for (const auto& Elem : Tab[y].GetData<std::string>()) {
            std::shared_ptr<MapPiece> TmpMapPiece = std::make_shared<MapPiece>(x++, y);
            size_t PossElemX = TmpMapPiece.get()->GetPoss().GetX() + (_SizeOneMapPiece / 2);
            size_t PossElemY = TmpMapPiece.get()->GetPoss().GetY() + (_SizeOneMapPiece / 2);
            switch (Elem) {
                case '.':
                    break;
                case 'x':
                    TmpMapPiece.get()->PushBackNotThrow(std::make_shared<Block>(PossElemX, PossElemY));
                    break;
                case 'S':
                    {
                        std::shared_ptr<IDisplay> ToPut1 = std::make_shared<Spawn>(PossElemX, PossElemY);
                        this->_AllSpawn.push_back(ToPut1);
                        TmpMapPiece.get()->PushBackNotThrow(ToPut1);
                    }
                    break;
                case 's':
                    {
                        std::shared_ptr<IDisplay> ToPut = std::make_shared<Spawn>(PossElemX, PossElemY);
                        this->_AllSpawn.push_back(ToPut);
                        TmpMapPiece.get()->PushBackNotThrow(ToPut);
                        TmpMapPiece.get()->PushBackNotThrow(std::make_shared<Bomb>(PossElemX, PossElemY));
                    }
                    break;
                case 'B':
                    TmpMapPiece.get()->PushBackNotThrow(std::make_shared<Bomb>(PossElemX, PossElemY));
                    break;
                case 'V':
                    TmpMapPiece.get()->PushBackNotThrow(std::make_shared<Spead>(PossElemX, PossElemY));
                    break;
                case 'H':
                    TmpMapPiece.get()->PushBackNotThrow(std::make_shared<Heal>(PossElemX, PossElemY));
                    break;
                default:
                    std::cerr << "Warrning: Unkow char in map: " << Elem << std::endl;
            }
            Tmp.push_back(TmpMapPiece);
        }
        this->_AllMap.push_back(Tmp);
        Tmp.clear();
    }
    if (this->_AllSpawn.size() > 4)
        throw Exception::ToMushSpawn();
    _InitMappWall(this->_AllMap);
}

/**
 * @brief Put en Ia on a spwan
 * 
 * @param IndexSpawnInTab index in _AllSpawn
 */
void Indi::_PutIaOnSpawn(const size_t IndexSpawnInTab)
{
    const auto& PossMapPieceToPut = this->_AllSpawn[IndexSpawnInTab].get()->GetPoss();
    std::shared_ptr<Ia> NewIa = std::make_shared<Ia>(this->_AllMap, *this,
        (PassIaInfoGame_t&&){this->_ConfPlayer, this->_ConfBomm, this->_ConfSpeed},
        PossMapPieceToPut.GetX(), PossMapPieceToPut.GetY());
    NewIa.get()->Life = this->_ConfPlayer.Heal;
    this->_AllIa.push_back(NewIa);
    this->_SetObjAtPoss(NewIa);
}

/**
 * @brief Put the player on a spawn
 * 
 * @param IndexSpawnInTab index in _AllSpawn
 */
void Indi::_PutPlayerOnSpawn(const size_t IndexSpawnInTab, size_t IndexTouch)
{
    const auto& PossMapPieceToPut = this->_AllSpawn[IndexSpawnInTab].get()->GetPoss();
    std::shared_ptr<Player> NewPlayer = std::make_shared<Player>(PossMapPieceToPut.GetX(), PossMapPieceToPut.GetY(), \
        this->_Touch[IndexTouch]);
    NewPlayer.get()->Life = this->_ConfPlayer.Heal;
    this->_AllPlayer.push_back(NewPlayer);
    this->_SetObjAtPoss(NewPlayer);
}

/**
 * @brief Set up a basic map
 * 
 */
void Indi::SetUpMap(size_t NbPlayer, size_t Map)
{
    // size_t nbIa = 4 - NbPlayer;
    // size_t cNbSpawn = this->_AllSpawn.size();

    this->_PutPlayerOnSpawn(0, 0);
    this->_PutPlayerOnSpawn(1, 1);
    // this->_PutIaOnSpawn(0);
}

void Indi::SetUpGraphic()
{
    _graphic.SetUp(GetAllMapSizeX(), GetAllMapSizeY(), 
    this->_GetTexture());
    // const Json::Json&
    // this->_GetTexture()[0].GetData<std::string>()
}

void Indi::_PutABoom(size_t y, size_t x)
{
    auto Elem = this->_AllMap[y][x].get();
    if (Elem->IsBombAtThisPile())
        return;
    printf("%ld, %ld\n", y, x);
    Elem->PutNewObj<Bomb>();
    _UpdateIaMap(this->_AllMap);
}

void Indi::_MapSetDangerZoneLeft(const TAllMap& AllMap, const int y, int x)
{
    --x;
    for (size_t tmp = 0; tmp != 5; ++tmp, --x) {
        if (x == -1)
            x = AllMap[0].size() - 1;
        if (AllMap[y][x].get()->IsWallInPile())
            break;
        if (AllMap[y][x].get()->IsFireAtThisPile())
            continue;
        else if (AllMap[y][x].get()->IsBombAtThisPile()) {
            Bomb *B;
            int index = 0;
            for (const auto& Elem : AllMap[y][x].get()->GetPile()) {
                if (Elem.get()->GetType() == ObjType::OBJBOMB) {
                    B = dynamic_cast<Bomb *>(Elem.get());
                    break;
                }
                ++index;
            }
            _ExploseBomb(*B, index, const_cast<TypePile&>(AllMap[y][x].get()->GetPile()));
            continue;
        }
        AllMap[y][x].get()->PutNewObj<Fire>();
    }
}

void Indi::_MapSetDangerZoneRight(const TAllMap& AllMap, const int y, int x)
{
    for (size_t tmp = 0; tmp != 5; ++tmp, ++x) {
        if (static_cast<size_t>(x) > AllMap[0].size())
            x = 0;
        if (AllMap[y][x].get()->IsWallInPile())
            break;
        if (AllMap[y][x].get()->IsFireAtThisPile())
            continue;
        else if (AllMap[y][x].get()->IsBombAtThisPile()) {
            Bomb *B;
            int index = 0;
            for (const auto& Elem : AllMap[y][x].get()->GetPile()) {
                if (Elem.get()->GetType() == ObjType::OBJBOMB) {
                    B = dynamic_cast<Bomb *>(Elem.get());
                    break;
                }
                ++index;
            }
            _ExploseBomb(*B, index, const_cast<TypePile&>(AllMap[y][x].get()->GetPile()));
            continue;
        }
        AllMap[y][x].get()->PutNewObj<Fire>();
    }
}

void Indi::_MapSetExploseZoneDown(TAllMap& AllMap, int y, const int x)
{
    ++y;
    for (size_t tmp = 0; tmp != 4; ++tmp, ++y) {
        if (y == -1)
            y = AllMap.size() - 1;
        if (AllMap[y][x].get()->IsWallInPile())
            break;
        if (AllMap[y][x].get()->IsFireAtThisPile())
            continue;
        else if (AllMap[y][x].get()->IsBombAtThisPile()) {
            Bomb *B;
            int index = 0;
            for (const auto& Elem : AllMap[y][x].get()->GetPile()) {
                if (Elem.get()->GetType() == ObjType::OBJBOMB) {
                    B = dynamic_cast<Bomb *>(Elem.get());
                    break;
                }
                ++index;
            }
            _ExploseBomb(*B, index, const_cast<TypePile&>(AllMap[y][x].get()->GetPile()));
            continue;
        }
        AllMap[y][x].get()->PutNewObj<Fire>();
    }
}

void Indi::_MapSetExploseZoneUp(TAllMap& AllMap, int y, const int x)
{
    --y;
    for (size_t tmp = 4; tmp != 0; --tmp) {
        if (y == -1)
            y = AllMap.size() - 1;
        if (AllMap[y][x].get()->IsWallInPile())
            break;
        if (AllMap[y][x].get()->IsFireAtThisPile())
            continue;
        else if (AllMap[y][x].get()->IsBombAtThisPile()) {
            Bomb *B;
            int index = 0;
            for (const auto& Elem : AllMap[y][x].get()->GetPile()) {
                if (Elem.get()->GetType() == ObjType::OBJBOMB) {
                    B = dynamic_cast<Bomb *>(Elem.get());
                    break;
                }
                ++index;
            }
            _ExploseBomb(*B, index, const_cast<TypePile&>(AllMap[y][x].get()->GetPile()));
            continue;
        }
        AllMap[y--][x].get()->PutNewObj<Fire>();
    }
}

void Indi::_ExploseBomb(Bomb& B, const size_t& index, TypePile &MapPiece)
{
    Poss_t Poss = B.GetPoss();
    this->_AllMap[B.GetPoss().GetYLikeTabIndex()][B.GetPoss().GetXLikeTabIndex()].get()->RemouveObject(MapPiece[index]);
    this->_AllMap[Poss.GetYLikeTabIndex()][Poss.GetXLikeTabIndex()].get()->PutNewObj<Fire>();
    _MapSetExploseZoneUp(this->_AllMap, Poss.GetYLikeTabIndex(), Poss.GetXLikeTabIndex());
    _MapSetExploseZoneDown(this->_AllMap, Poss.GetYLikeTabIndex(), Poss.GetXLikeTabIndex());
    _MapSetDangerZoneRight(this->_AllMap, Poss.GetYLikeTabIndex(), Poss.GetXLikeTabIndex());
    _MapSetDangerZoneLeft(this->_AllMap, Poss.GetYLikeTabIndex(), Poss.GetXLikeTabIndex());
}

void Indi::_ManageBoomAndFire()
{
    bool HaveToRealoadIaMap = false;

    for (auto& Line : this->_AllMap) {
        for (auto& Piece : Line) {
            if (Piece.get()->IsBombAtThisPile() or Piece.get()->IsFireAtThisPile()) {
                size_t index = 0;
                for (auto& Item : Piece.get()->GetPile()) {
                    if (Item.get()->GetType() == ObjType::OBJBOMB) {
                        Bomb &B = *dynamic_cast<Bomb *>(Item.get());
                        if (B.TimerExplose.GetTimerInSeconds() >= this->_ConfBomm.TimeBeaforeExplose) {
                            _ExploseBomb(B, index, const_cast<TypePile& >(Piece.get()->GetPile()));
                            HaveToRealoadIaMap = true;
                            break;
                        }
                    } else if (Item.get()->GetType() == ObjType::OBJFIRE) {
                        Fire &F = *dynamic_cast<Fire *>(Item.get());
                        if (F.TimerExplose.GetTimerInSeconds() >= ___TimeForExplosion) {
                            std::shared_ptr<IDisplay> Tmp = std::const_pointer_cast<IDisplay>(Item);
                            Piece.get()->RemouveObject(Tmp);
                            HaveToRealoadIaMap = true;
                            break;
                        }
                    }  else
                        ++index;
                }
            }
        }
    }
    if (HaveToRealoadIaMap)
        this->_UpdateIaMap(GetAllMap());
}

void Indi::_MangeLife(std::shared_ptr<IEntity>& Entity, const bool isIa)
{
    const auto& Pile = this->_AllMap[Entity.get()->GetPoss().GetYLikeTabIndex()][Entity.get()->GetPoss().GetXLikeTabIndex()].get();

    if (Pile->IsFireAtThisPile()) {
        if (Entity.get()->AllREadyLoseLife == false)
            --Entity.get()->Life;
        if (Entity.get()->Life == 0) {
            IDisplay *TmpAddr = Entity.get();
            if (isIa) {
                std::shared_ptr<Ia> Tmp = std::dynamic_pointer_cast<Ia>(Entity);
                for (std::vector<std::shared_ptr<Ia>>::iterator i = this->_AllIa.begin(); i != this->_AllIa.end(); i++) {
                    if (i.base()->get() == Tmp.get()) {
                        this->_AllIa.erase(i);
                        break;
                    }
                }
            } else {
                std::shared_ptr<Player> Tmp = std::dynamic_pointer_cast<Player>(Entity);
                for (std::vector<std::shared_ptr<IEntity>>::iterator i = this->_AllPlayer.begin(); i != this->_AllPlayer.end(); i++) {
                    if (i.base()->get() == Tmp.get()) {
                        this->_AllPlayer.erase(i);
                        break;
                    }
                }
            }
            for (auto& P : Pile->GetPile()) {
                if (P.get() == TmpAddr) {
                    std::shared_ptr<IDisplay> TmpDisplay = std::dynamic_pointer_cast<IDisplay>(P);
                    Pile->RemouveObject(TmpDisplay);
                    break;
                }
            }
            printf("REmouve\n");
            throw Exception::RemouveOneEntity();
        }
        Entity.get()->AllREadyLoseLife = true;
    } else if (Entity.get()->AllREadyLoseLife == true)
        Entity.get()->AllREadyLoseLife = false;
}

void Indi::_MouveAll()
{
    if (this->_AllPlayer.empty())
        exit(0);
    for (auto& Elem : this->_AllIa) {
        try {
            Elem.get()->Run(this->_AllMap, *this, this->_AllPlayer, \
                (PassIaInfoGame_t &&){this->_ConfPlayer, this->_ConfBomm, this->_ConfSpeed});
            _MouveEntityXY(std::dynamic_pointer_cast<IDisplay>(Elem), 
                Elem.get()->GetNewPoss().GetX(), Elem.get()->GetNewPoss().GetY(), true);
        } catch(Exception::ImpossibleMouve &e) {
            printf("touch un mure\n");
        }
        // printf("Poss: x:%ld, y:%ld\n", Elem.get()->GetNewPoss().GetX(), Elem.get()->GetNewPoss().GetY());
        std::shared_ptr<IEntity> Tmp = Elem;
        // _MangeLife(Tmp, true);
    }
    for (auto& Elem : this->_AllPlayer) {
        Player &P = *dynamic_cast<Player *>(Elem.get());

        const auto Action = P.Run(P.GetTouch().GetActionFromTouch(), (PassIaInfoGame_t &&){this->_ConfPlayer, this->_ConfBomm, this->_ConfSpeed});
        try {
            _MouveEntityXY(std::dynamic_pointer_cast<IDisplay>(Elem), Elem.get()->GetNewPoss().GetX(), \
            Elem.get()->GetNewPoss().GetY(), true);
            if (Action == MyRaylib::Action::Put)
                _PutABoom(P.GetPoss().GetYLikeTabIndex(), P.GetPoss().GetXLikeTabIndex());
        } catch(Exception::ImpossibleMouve &e) {
            printf("touch un mure\n");
        }
        try {
            _MangeLife(Elem, false);
        } catch(Exception::RemouveOneEntity &e) {
            break;
        }
    }
    _ManageBoomAndFire();
}

void Indi::Run()
{
    int loop = MENU;
    bool setup = false;

    this->_SetupAllConfig();
    this->_GenerateAllMapByIndexInJsonFile(2);


    _graphic.SetUp(GetAllMapSizeX(), GetAllMapSizeY(), this->_GetTexture());


    // ShowCursor();
    EnableCursor();
    while (loop != END) {
        if (loop == MENU)
            loop = _graphic.MyMenu(_Touch);
        else if (loop == GAME){
            if (setup == false) {
                this->_Timer.Start();
                SetUpMap(0, 2);
                setup = true;
            }
            EnableCursor();
            loop = _graphic.MyGame(_AllMap);
            if (this->_Timer.GetTimerInSeconds() < ___TimeMaster)
                continue;
            _MouveAll();
            this->_Timer.Reset();
        }
        // std::cout << loop <<  "\n";
    }

}