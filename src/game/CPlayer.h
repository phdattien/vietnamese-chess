//
// Created by tiendat on 22.05.22.
//
#pragma once

#include "CBoard.h"
#include "optional"
#include "Draw.h"

/**
 * Abstract class of players
 */
class CPlayer {
public:
    virtual ~CPlayer() noexcept = default;
    /**
     * Method to choose and make a move on board.
     * @param board current postion
     * @param gameState current game State
     * @return false if we no longer have any possible movement, true otherwise
     */
    virtual bool TakeAction ( CBoard &board, GAME_STATE &gameState ) = 0;
protected:
};


