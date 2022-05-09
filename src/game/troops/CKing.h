//
// Created by tiendat on 09.05.22.
//
#pragma once
#include "CTroop.h"

class CKing : public CTroop {
public:
    CKing ( std::string name, SIDE side, CCoord coord ) : CTroop ( move(name), side, coord ) {};

    std::set<CCoord> getPossibleMoves ( ) const override;

private:
};

