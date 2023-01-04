/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_

#include <sys/types.h>

enum class ObjType {
    OBJMAPECE,
    OBJWALL,
    OBJBLOC,
    OBJBOMB,
    OBJFIRE,
    OBJSPEED,
    OBJENTITY,
    OBJSPAWN,
    OBJHEAL
};

static const size_t _SizeOneMapPiece = 10;
static const size_t ___TimeMaster = 0.05;
static const size_t ___TimeForExplosion = 3;
static const size_t ___TimeBeaforeCanPutANewBoom = 3;

/**
 * @brief Le stockage des possition doit toujours etre le meme interpreter par le graphique
 * si 1 case fait 100 * 100 alor _SizeOneMapPiece = 100.
 * AllMap[0][0] fera 100 * 100
 * Bien recompiler quand on chage _SizeOneMapPiece: make -j && make && clear
 * 
 */
typedef struct Poss_s {
    public:
        /**
         * @brief Construct a new Poss_s object
         * 
         * @param x Basse Poss X
         * @param y Basse Poss Y
         */
        Poss_s(size_t x, size_t y): _X(x), _Y(y) {};
        /**
         * @brief Get X LikeTabIndex _SizeOneMapPiece
         * 
         * @return size_t 
         */
        size_t GetXLikeTabIndex() const {return (_X / _SizeOneMapPiece);}
        /**
         * @brief Get Y LikeTabIndex _SizeOneMapPiece
         * 
         * @return size_t 
         */
        size_t GetYLikeTabIndex() const {return (_Y / _SizeOneMapPiece);}
        /**
         * @brief Get X
         * 
         * @return size_t 
         */
        size_t GetX() const {return (_X);}
        /**
         * @brief Get Y
         * 
         * @return size_t 
         */
        size_t GetY() const {return (_Y);}
        /**
         * @brief Set New value to X
         * 
         * @param NewX 
         */
        void SetX(size_t NewX) { this->_X = NewX;}
        /**
         * @brief Set new value to Y
         * 
         * @param NewY 
         */
        void SetY(size_t NewY) { this->_Y = NewY;}
        /**
         * @brief Set X and Y
         * 
         * @param NewX 
         * @param NewY 
         */
        void SetXY(size_t NewX, size_t NewY) {this->_X = NewX; this->_Y = NewY;}
        /**
         * @brief Destroy the Poss_s object
         * 
         */
        void SetXLikeTabIndex(size_t NewX) { this->_X = NewX * _SizeOneMapPiece;}
        /**
         * @brief Set new value to Y
         * 
         * @param NewY 
         */
        void SetYLikeTabIndex(size_t NewY) { this->_Y = NewY * _SizeOneMapPiece;}
        /**
         * @brief Set X and Y
         * 
         * @param NewX 
         * @param NewY 
         */
        void SetXYLikeTabIndex(size_t NewX, size_t NewY) {this->_X = NewX; this->_Y = NewY;}
        /**
         * @brief Destroy the Poss_s object
         * 
         */
        ~Poss_s() = default;
    private:
        size_t _X;
        size_t _Y;
} Poss_t;

/**
 * @brief Has all functions to display
 * 
 */
class IDisplay {
    public:
        IDisplay(ObjType Type, size_t x, size_t y): _Objects(Type), _Poss(x, y) {};
        virtual ~IDisplay() = default;
        /**
         * @brief Get the Type object
         * 
         * @return ObjType 
         */
        ObjType GetType(void) const {
            return this->_Objects;
        }
        Poss_s& GetPoss(void) {
            return this->_Poss;
        }
    private:
        const ObjType _Objects;
        Poss_s _Poss;
};

#endif /* !IDISPLAY_HPP_ */
