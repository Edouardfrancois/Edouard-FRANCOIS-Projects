#include "Touch.hpp"
#include "Indi.hpp"
#include "Player.hpp"
#include "IEntity.hpp"

void Indi::_MovePlayer()
{
    for (const auto& OnePlayer : _AllPlayer) {
        const auto& NewPos = OnePlayer.get()->GetNewPoss();
        const auto& ActualPos = OnePlayer.get()->GetPoss();

        if (NewPos.GetX() == ActualPos.GetX() and NewPos.GetY() == ActualPos.GetY())
            continue;
        try {
            _MouveEntityXY(OnePlayer, NewPos.GetX(), NewPos.GetY(), false);
            OnePlayer.get()->SetOldPoss(OnePlayer.get()->GetPoss().GetY(), OnePlayer.get()->GetPoss().GetX());
        } catch (Exception::CanOnlyMouveObjEntity& e) {
            continue;
        }
    }
    // MyRaylib::Action act = touch.GetActionFromTouch();
    // const Poss_t& _OldPos = IEntity::GetOldPoss();
    // const Poss_t& _NewPos = {0, 0};
// 
    // if (act == MyRaylib::Action::Up)
        // _MouveEntityXY(ObjType::OBJENTITY, _OldPos.GetX() - 1, _OldPos.GetY(), true);
    // if (act == MyRaylib::Action::Down)
        // Indi::_MouveEntityXY(ObjType::OBJENTITY, _OldPos.GetX() - 1, _OldPos.GetY(), true);
    //else if (Action.get() == MyRaylib::Action::Left)
    //else if (Action.get() == MyRaylib::Action::Right)
}

// void Indi::_MoveRight(MyRaylib::Action& act)
// {
//     // if (act == MyRaylib::Action::Right)
//         // Player::_MouveEntityXY(ObjType::OBJENTITY, this->SetNewPoss(this->GetPoss());, 0, true);
//        get()->SetNewPoss(Player->get()->GetPoss().GetX() + 1, Player->get()->GetPoss().GetY());
//     //if (act == MyRaylib::Action::Left)
//     //    Player->get()->SetNewPoss(Player->get()->GetPoss().GetX() - 1, Player->get()->GetPoss().GetY());
// }