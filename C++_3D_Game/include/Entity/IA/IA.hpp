/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** IA
*/

#ifndef IA_HPP_
#define IA_HPP_

#include <vector>
#include <memory>

#include "IEntity.hpp"
#include "MapPiece.hpp"
#include "ManageIa.hpp"
#include "JsonData.hpp"

using TAllMap = std::vector<std::vector<std::shared_ptr<MapPiece>>>;
using TFindArray = std::vector<std::vector<int>>;

using TAllPlayer = std::vector<std::shared_ptr<IEntity>>;

enum class HisPossibleToGoObjectif
{
    IMPOSSIBLE,
    POSSIBLE,
    POSSIBLE_WIVE_BOST
};

typedef struct PassIaInfoGame_s
{
    PassIaInfoGame_s(const EntityConf_t& ConfPlayer, const BommConf_t& ConfBomm, const Speed_t& ConfSpeed) : ConfPlayer(ConfPlayer), ConfBomm(ConfBomm), ConfSpeed(ConfSpeed) {}
    ~PassIaInfoGame_s() = default;
    const EntityConf_t& ConfPlayer;
    const BommConf_t& ConfBomm;
    const Speed_t& ConfSpeed;
} PassIaInfoGame_t;

typedef struct IaObjectif_s {
    public:
        IaObjectif_s() {};
        ~IaObjectif_s() = default;
        void SetNewObjectifX(const TAllMap& AllMap, const size_t ObjectifX);
        void SetNewObjectifY(const TAllMap& AllMap, const size_t ObjectifY);
        void SetNewObjectifXY(const TAllMap& AllMap, const size_t ObjectifX, const size_t ObjectifY);
    private:
        size_t _DirectionObjectifX;
        size_t _DirectionObjectifY;
} IaObjectif_t;

typedef struct FindArray_s
{
    friend class Ia;
    public:
        FindArray_s(size_t SizeX, size_t SizeY);
        ~FindArray_s() = default;
    private:
        const Poss_t _GetNearestPieceMap(const Poss_t& Poss);
    private:
        HisPossibleToGoObjectif _IsGoInNotSafeZone(const ManageIa& ManageMap, const Poss_t& Poss, size_t x, size_t y, size_t& count, const PassIaInfoGame_t& GameInfo, const TInveotry& Inv);
        HisPossibleToGoObjectif _DoWeHaveTimeToGotoObjecif(const Poss_t& Poss, const PassIaInfoGame_t& GameInfo, const TInveotry& Inv);
        HisPossibleToGoObjectif _IsSafeZoneNext(const ManageIa& ManageMap, const Poss_t& Poss, size_t x, size_t y, size_t& count, const PassIaInfoGame_t& GameInfo, const TInveotry& Inv);
        HisPossibleToGoObjectif _SetSafeObjectif(const ManageIa& ManageMap, const Poss_t& Poss, size_t x, size_t y, size_t& count, const PassIaInfoGame_t& GameInfo, const TInveotry& Inv);
        HisPossibleToGoObjectif _FindNearest(const ManageIa& ManageMap, const Poss_t& Poss, size_t& count, const PassIaInfoGame_t& GameInfo, const TInveotry& Inv);
        HisPossibleToGoObjectif _FindBestWaiToBegin(const ManageIa& ManageMap, const Poss_t& Poss, size_t& count, const PassIaInfoGame_t& GameInfo, const TInveotry& Inv);
    private:
        HisPossibleToGoObjectif _CreateTab(const ManageIa& ManageMap, const Poss_t& Poss,  const PassIaInfoGame_t& GameInfo, const TInveotry& Inv);
        void _DisplayDebug();
    private:
        size_t _Count;
        TFindArray _Array;
} FindArray_t;

class IaAttack {
    public:
        IaAttack() {};
        ~IaAttack() = default;
    protected:
        // void _SetTarget(const TAllMap& AllMap, const TAllPlayer& AllPlayer);
        // void _SetPath(const TAllMap& AllMap, const TAllPlayer& AllPlayer);
        // void _(const TAllMap& AllMap, const TAllPlayer& AllPlayer);
    private:
        IaObjectif_t _Target;
};

class Ia : public IEntity, private IaAttack {
    public:
        Ia(const TAllMap& AllMap, const ManageIa& ManageMap, const PassIaInfoGame_t&& _GameInfo, size_t x, size_t y);
        ~Ia() = default;
    private:
        /* Checker */
        bool _IsADangerousZone(const TAllMap& AllMap, const ManageIa& ManageMap);
        /* Seteur */
        void _SetNewGoalOffense(const TAllMap& AllMap, const ManageIa& ManageMap);
        void _SetNewGoalDefense(const TAllMap& AllMap, const ManageIa& ManageMap, const PassIaInfoGame_t& GameInfo);
        void _SetObjectif(const TAllMap& AllMap, const ManageIa& ManageMap, const PassIaInfoGame_t& GameInfo);
        /* Attack */
    public:
        void Run(const TAllMap& AllMap, const ManageIa& ManageMap, const TAllPlayer& AllPlayer, const PassIaInfoGame_t& GameInfo);
    private:
        IaObjectif_t _DirectionObjectif;
        FindArray_t _FindArray;
        enum class _IAMode {
            DEF,
            ATTAK,
        };
        _IAMode _Mode;
};

#endif /* !IA_HPP_ */
