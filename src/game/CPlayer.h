//
// Created by tiendat on 22.05.22.
//
#pragma once

#include "CBoard.h"
#include "optional"
#include "Draw.h"

class CPlayer {
public:
    virtual ~CPlayer() noexcept = default;
    // virtual function to make a player choose a movement on board
    virtual bool TakeAction ( CBoard &board, DRAW_STATE &drawState ) = 0;
protected:
};


