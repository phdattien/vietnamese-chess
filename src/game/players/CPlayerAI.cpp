//
// Created by tiendat on 22.05.22.
//

#include "CPlayerAI.h"
#include "cstdio"


std::optional<Move> CPlayerAI::TakeAction ( CBoard &board ) {

    std::vector<Move> moves =  board.generateMoves();
    if ( moves.empty() ) {
        return {};
    }
    int k = rand();
    return moves[k % moves.size()];
}

