//
// Created by tiendat on 01.06.22.
//
#pragma once
#include "CBoard.h"
#include "Move.h"
#include "CEvaluation.h"

class CSearch {
public:
    CSearch ( CBoard board ) : m_Board ( std::move ( board ) ){};
    void StartSearch ( );
    int GetBestEval () const;
    int Search ( int depth, int alpha, int beta );
    Move GetBestMove () const;

private:
    void OrderMoves ( std::vector<Move> & moves );
    CBoard m_Board;
    CEvaluation m_Evaluation;
    Move m_BestMove;
    int m_BestEval;
    static const int DEPTH = 3;
};
