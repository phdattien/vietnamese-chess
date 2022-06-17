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


int CSearch::Search ( int depth, int alpha, int beta, int recCnt ) {

    if ( recCnt > 0 ) { // try to not repeat moves -> AI won't move the same move twice if do is a draw
        if ( m_Board.isRepetition() )
            return 0;
    }

    if ( depth == 0 ) {
        return m_Evaluation.Evaluate (m_Board);
//        return QuiescenceSearch (alpha, beta);
    }

    std::vector<Move> possibleMoves = m_Board.generateMoves();
    if ( possibleMoves.empty() ) {
        return CHECKED - recCnt; // we want to choose moves that checked us later - a way to order checks
    }
    OrderMoves (possibleMoves);
    Move bestMove{};

    for ( const auto & move : possibleMoves ) {
        m_Board.MakeMove (move, true);
        int eval = -Search ( depth - 1, -beta, -alpha, recCnt + 1 );
        m_Board.UnMakeMove ( move, true );

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
    m_BestEval = Search ( m_Depth, NEG_INFINITY, INFINITY, 0 );
}

/* order from more valuable moves to least, by a capture move */
void CSearch::OrderMoves ( std::vector<Move> &moves ) {
    for ( auto & move : moves ) {
        auto capturedTroop = m_Board.getTroopOnCoord ( move.m_To );
        if ( capturedTroop )
            move.m_Score += 50;
    }
    std::sort( moves.begin(), moves.end() );
}

int CSearch::GetBestEval () const {
    return m_BestEval;
}

int CSearch::QuiescenceSearch ( int alpha, int beta ) {
    int eval = m_Evaluation.Evaluate (m_Board);
    if (eval >= beta) {
        return beta;
    }
    if (eval > alpha) {
        alpha = eval;
    }

    std::vector<Move> possibleMoves = m_Board.generateMoves();
    OrderMoves (possibleMoves);
    for ( auto & move : possibleMoves ) {
        if ( ! m_Board.getTroopOnCoord ( move.m_To ) ) // if is a non capture move
            continue;
        m_Board.MakeMove (move, true);
        eval = -QuiescenceSearch ( -beta, -alpha);
        m_Board.UnMakeMove ( move, true );

        if ( eval >= beta )
            return beta;
        if ( eval > alpha )
            alpha = eval;
    }
    return alpha;
}
