/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** BombDetonation
*/

#include <chrono>
#include "BombDetonation.hpp"

BombDetonation::BombDetonation()
{
}

BombDetonation::~BombDetonation()
{
}

bool BombDetonation::Detonation(const TypePile &pile, BommConf_t *BommConf)
{
    // for (const auto Elem : pile) {
        // if (Elem.get()->GetType() == ObjType::OBJBOMB) {
            // 
        // }
    // }
    // if (pile == TypePile::Bomb) {
        // pile.get()->SetBlockType(IAMapElemType::IS_BOOM);
    // }
    // if (BommConf->ExplosionSize)
    //   if ()
  //if (BommConf->TimeBeaforeExplose == )

}

bool BombDetonation::CheckDetonation(const TAllMap& AllMap, BommConf_t *BommConf)
{
    current_time = 0;
    time(&current_time);
    for (const auto& Line : AllMap) {
        for (const auto& Elem : Line) {
            if (Elem.get()->IsBombAtThisPile() && BommConf->TimeBeaforeExplose == current_time) {
                std::cout << current_time << std::endl;
                Detonation(Elem.get()->GetPile(), BommConf);
            }
        }
    }
    return NULL;
}