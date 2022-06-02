//
// Created by tiendat on 30.05.22.
//

#include "Perft.h"
#include <vector>

Perft::Perft ( CBoard board ) : m_Board ( std::move (board) ) {}

int Perft::movesTest ( int depth ) {
    if ( depth == 0 )
        return 1;

    int nodes = 0;
    std::vector<Move> moves = m_Board.generateMoves();
    for ( auto & move : moves ) {
        m_Board.MakeMove (move);
        nodes += movesTest ( depth - 1);
        m_Board.UnMakeMove (move);
    }
    return nodes;
}

