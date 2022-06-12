//
// Created by tiendat on 01.06.22.
//
#pragma once
#include "CBoard.h"
#include "Move.h"
#include "CEvaluation.h"

/**
 * Class for searching current position and finding a best Move
 * inspired a copied from:
 * https://www.youtube.com/watch?v=U4ogK0MIzqk&t=773s
 * https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
 * https://www.chessprogramming.org/Move_Ordering
 */
class CSearch {
public:
    CSearch ( CBoard board ) : m_Board ( std::move ( board ) ){};
    /**
     * search
     */
    void StartSearch ( );
    /*
     * Method to get bestMove, can be used only after StartSearch
     */
    Move GetBestMove () const;
    /*
     * Method to get bestMove, can be used only after StartSearch
     */
    int GetBestEval () const;

private:
    /**
     * Method to find a best Move, using minimax and alpha-beta prunning for optimalization
     * @param depth depth to search
     * @param alpha helps optimize search
     * @param beta
     * @return
     */
    int Search ( int depth, int alpha, int beta );
    void OrderMoves ( std::vector<Move> & moves );
    CBoard m_Board;
    CEvaluation m_Evaluation;
    /**
     * Best move after Search
     */
    Move m_BestMove;
    int m_BestEval;
    static const int DEPTH = 3;
};
