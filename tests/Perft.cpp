//
// Created by tiendat on 30.05.22.
//

#include "Perft.h"
#include <vector>
#include <iostream>

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

//u64 Perft(int depth)
//{
//    MOVE move_list[256];
//    int n_moves, i;
//    u64 nodes = 0;
//
//    if (depth == 0)
//        return 1ULL;
//
//    n_moves = GenerateMoves(move_list);
//    for (i = 0; i < n_moves; i++) {
//        MakeMove(move_list[i]);
//        if (!IsIncheck())
//            nodes += Perft(depth - 1);
//        UndoMove(move_list[i]);
//    }
//    return nodes;
//}
//
