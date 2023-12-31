//
// Created by tiendat on 01.06.22.
//

#include "CPlayerSmartAI.h"

bool CPlayerSmartAI::TakeAction ( CBoard &board, GAME_STATE &gameState ) {
    // if best evaluation for a best move is below zero we accpet a draw
    if ( gameState == GAME_STATE::SUGGEST ) {
        CSearch search( board, m_Depth );
        search.StartSearch ();
        gameState = search.GetBestEval() < 0 ? GAME_STATE::ACCEPT : GAME_STATE::NEUTRAL;
        board.ChangeSide();
        return true;
    }

    std::vector<Move> moves =  board.generateMoves();
    if ( moves.empty() ) {
        return false;
    }

    CSearch search( board, m_Depth );
    search.StartSearch ();
    Move move = search.GetBestMove();
    board.MakeMove ( move );
    return true;
}
