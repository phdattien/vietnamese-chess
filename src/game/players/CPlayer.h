//
// Created by tiendat on 22.05.22.
//
#pragma once

#include "../Move.h"
#include "../CBoard.h"
#include "optional"

class CPlayer {
public:
    virtual ~CPlayer() noexcept = default;
    // virtual function to make a player choose a movement on board
    virtual std::optional<Move> TakeAction ( CBoard &board ) = 0;
protected:
};


