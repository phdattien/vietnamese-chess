//
// Created by tiendat on 30.05.22.
//
#pragma once
#include "CBoard.h"


class Perft {
public:
    explicit Perft ( CBoard board );
    void movesTest ( int depth, int &sum );
private:
    CBoard m_Board;


};


