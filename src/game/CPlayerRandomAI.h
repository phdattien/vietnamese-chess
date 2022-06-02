//
// Created by tiendat on 22.05.22.
//
#pragma once

#include "CPlayer.h"
#include "CBoard.h"
#include "Move.h"

class CPlayerRandomAI : public CPlayer {
public:
    CPlayerRandomAI () = default;
    bool TakeAction ( CBoard &board, GAME_STATE &gameState ) override;
private:
};


