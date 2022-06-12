//
// Created by tiendat on 30.05.22.
//
#pragma once
#include "CBoard.h"


class Perft {
public:
    explicit Perft ( CBoard board );
    int movesTest ( int depth );
private:
    CBoard m_Board;


};


