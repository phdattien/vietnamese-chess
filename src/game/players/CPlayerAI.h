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
    std::optional<Move> TakeAction ( CBoard &board ) override;

private:
    Move chosenMove;
};


