//
// Created by tiendat on 22.05.22.
//
#pragma once

#include "CPlayer.h"
#include "CBoard.h"
#include "Move.h"

class CPlayerAI : public CPlayer {
public:
    CPlayerAI () = default;
    bool TakeAction ( CBoard &board, DRAW_STATE drawState ) override;
private:
};


