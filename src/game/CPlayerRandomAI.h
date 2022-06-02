//
// Created by tiendat on 22.05.22.
//
#pragma once

#include "CPlayer.h"
#include "CBoard.h"
#include "Move.h"

/**
 * Random Player choose his movements randomly, when other players for draw, always accept
 */
class CPlayerRandomAI : public CPlayer {
public:
    CPlayerRandomAI () = default;
    bool TakeAction ( CBoard &board, GAME_STATE &gameState ) override;
private:
};


