//
// Created by tiendat on 30.05.22.
//

#include "Perft.h"
#include <vector>

Perft::Perft ( CBoard board ) : m_Board ( std::move (board) ) {}

void Perft::movesTest ( int depth, int & sum ) {
    if ( depth == 0 ) {
        sum += 1;
        return;
    }

    std::vector<Move> moves = m_Board.generateMoves();
    for ( auto & move : moves ) {
        m_Board.MakeMove (move);
        movesTest ( depth - 1, sum);
        m_Board.UnMakeMove (move);
    }
}

