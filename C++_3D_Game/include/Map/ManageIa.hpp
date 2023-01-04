/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** ManageIa
*/

#ifndef MANAGEIA_HPP_
#define MANAGEIA_HPP_

#include <vector>
#include <memory>

#include "IDisplay.hpp"

using TAllMap = std::vector<std::vector<std::shared_ptr<MapPiece>>>;

enum class IAMapElemType {
    NOFINK = 0,
    ME = -1,
    UNBREAKABLE = -2,
    IS_BOOM = -3,
    DAMAGE_ZONE = -4,
};

typedef struct IaMap_s: public Poss_t {
    public:
        /**
         * @brief Construct a new IaMap_s object
         * 
         * @param x 
         * @param y 
         * @param BlockType 
         */
        IaMap_s(int x, int y, IAMapElemType BlockType) : Poss_s(x * _SizeOneMapPiece, y * _SizeOneMapPiece), _BlockType(BlockType) {};
        void SetBlockType(IAMapElemType&& NewBlockType) {
            this->_BlockType = NewBlockType;
        }
        IAMapElemType GetBlockType() const {
            return this->_BlockType;
        }
    private:
        IAMapElemType _BlockType;
} IaMap_t;

using TMappWall = std::vector<std::vector<std::shared_ptr<IaMap_t>>>;

class ManageIa {
    public:
        ManageIa() {};
        ~ManageIa() = default;
    public:
        const TMappWall& GetMappIa() const { return this->_IAMapp; }
        const bool& GetNew() const { return this->_New; }
        void SetNew(const bool New) { this->_New = New; }
    private:
        void _SetDangerZoneLeft(const TAllMap& AllMap, const int y, int x);
        void _SetDangerZoneRight(const TAllMap& AllMap, const int y, int x);
        void _SetDangerZoneDown(const TAllMap& AllMap, int y, const int x);
        void _SetDangerZoneUp(const TAllMap& AllMap, int y, const int x);
        void _FillMapDanger(const TAllMap& AllMap, int y, int x);
        void _SetDangerZone(const TAllMap& AllMap);
    protected:
        void _UpdateIaMap(const TAllMap& AllMap);
        void _InitMappWall(const TAllMap& AllMap);
    private:
        virtual size_t GetAllMapSizeX() = 0;
        virtual size_t GetAllMapSizeY() = 0;
    private:
        TMappWall _IAMapp;
        bool _New;
};

void __DebugPrintMapWall(const TMappWall& _MappWall);

#endif /* !MANAGEIA_HPP_ */
