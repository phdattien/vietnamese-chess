//
// Created by tiendat on 09.05.22.
//
#pragma once
#include "CTroop.h"

class CGeneral : public CTroop {
public:
    CGeneral ( std::string name, SIDE side, CCoord coord ) : CTroop ( move( name), side, coord ) {};

    std::set<CCoord> getPossibleMoves ( const std::unique_ptr<CTroop> currBoard[8][8] ) const override;

private:
    bool isInsideGeneralMovements ( const CCoord& newCoord ) const;
};
