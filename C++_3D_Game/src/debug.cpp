/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** debug
*/

#include <iostream>

#include "Indi.hpp"

void __DebugSizeAllMap(const TAllMap& _AllMap)
{
    DEBUG_BALISE_BEGIN
    dprintf(2, "Map hauteur size: %ld.\n", _AllMap.size());
    dprintf(2, "Map horizontal size: %ld.\n", _AllMap[0].size());
    DEBUG_BALISE_END
}

void __DebugPrintMapWall(const TMappWall& _MappWall) 
{
    DEBUG_BALISE_BEGIN
    dprintf(2, "PRINT _MappWall.\n");
    dprintf(2, "-----------\n");
    for (auto Line : _MappWall) {
        for (auto MapPiece : Line) {
                if (static_cast<int>(MapPiece.get()->GetBlockType()) >= 0 and static_cast<int>(MapPiece.get()->GetBlockType()) <= 9)
                    dprintf(2, " %d ", static_cast<int>(MapPiece.get()->GetBlockType()));
                else
                    dprintf(2, "%d ", static_cast<int>(MapPiece.get()->GetBlockType()));
        }
        dprintf(2, "\n");
    }
    DEBUG_BALISE_END
}
