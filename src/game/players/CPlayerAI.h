//
// Created by tiendat on 22.05.22.
//
#pragma once

#include "CPlayer.h"
#include "../CBoard.h"
#include "../Move.h"

class CPlayerAI : public CPlayer {
public:
    CPlayerAI () = default;
    Move ChooseMove ( CBoard &board ) override;

private:
    Move chosenMove;
};


