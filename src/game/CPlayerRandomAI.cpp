//
// Created by tiendat on 22.05.22.
//

#include "CPlayerRandomAI.h"

bool CPlayerRandomAI::TakeAction ( CBoard &board, GAME_STATE &gameState ) {
    if ( gameState == GAME_STATE::SUGGEST ) {
        gameState = GAME_STATE::ACCEPT;
        board.ChangeSide();
        return true;
    }

    std::vector<Move> moves =  board.generateMoves();
    if ( moves.empty() ) {
        return false;
    }
    int k = rand();
    Move move = moves[k % moves.size()];
    board.MakeMove ( move );
    return true;
}

