//
// Created by tiendat on 22.05.22.
//

#include "CPlayerAI.h"


Move CPlayerAI::ChooseMove ( CBoard &board ) {
    std::vector<Move> moves =  board.generateMoves();
    return moves[0];
}

