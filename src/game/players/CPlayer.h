//
// Created by tiendat on 22.05.22.
//
#pragma once

#include "../Move.h"
#include "game/CBoard.h"

class CPlayer {
public:
    virtual ~CPlayer() noexcept = default;
    // virtual function to make a player choose a movement on board
    virtual Move ChooseMove ( CBoard &board ) = 0;
protected:

};


