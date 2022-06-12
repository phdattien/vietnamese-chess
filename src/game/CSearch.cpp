//
// Created by tiendat on 01.06.22.
//

#include "CSearch.h"
#include <vector>
#include <climits>
#include <algorithm>

Move CSearch::GetBestMove () const {
    return m_BestMove;
}


int CSearch::Search ( int depth, int alpha, int beta ) {
    if ( depth == 0 )
        return m_Evaluation.Evaluate (m_Board);

    std::vector<Move> possibleMoves = m_Board.generateMoves();
    if ( possibleMoves.empty() ) {
        return -10000;
    }
    OrderMoves (possibleMoves);
    Move bestMove{};

    for ( const auto & move : possibleMoves ) {
        m_Board.MakeMove (move);
        int eval = -Search ( depth - 1, -beta, -alpha );
        m_Board.UnMakeMove ( move );

        if ( eval >= beta )
            return beta;

        if ( eval > alpha ) {
            bestMove = move;
            alpha = eval;
        }
    }

    m_BestMove = bestMove;
    return alpha;
}

void CSearch::StartSearch () {
    m_BestEval = Search ( DEPTH, -9999999, 9999999 );
}

/* order from more valuable moves to least, by a capture move */
void CSearch::OrderMoves ( std::vector<Move> &moves ) {
    for ( auto & move : moves ) {
        auto capturedTroop = m_Board.getTroopOnCoord ( move.m_To );
        if ( capturedTroop )
            move.m_Score += 30;
    }
    std::sort( moves.begin(), moves.end() );
}

int CSearch::GetBestEval () const {
    return m_BestEval;
}
