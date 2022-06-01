//
// Created by tiendat on 22.05.22.
//

#include "CPlayerAI.h"

bool CPlayerAI::TakeAction ( CBoard &board, DRAW_STATE drawState ) {

    std::vector<Move> moves =  board.generateMoves();
    if ( moves.empty() ) {
        return false;
    }
    int k = rand();
    Move move = moves[k % moves.size()];
    board.MakeMove ( move );
    return true;
}

