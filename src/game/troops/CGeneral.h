//
// Created by tiendat on 09.05.22.
//
#pragma once
#include "CTroop.h"
#include <vector>

class CGeneral : public CTroop {
public:
    CGeneral ( std::string name, SIDE side, CCoord coord ) : CTroop ( move( name), side, coord ) {};

    std::set<CCoord> getPossibleMoves ( const std::shared_ptr<CTroop> currBoard[10][9] ) const override;

private:
    bool isInsideGeneralMovements ( const CCoord& newCoord ) const;
    static const std::vector<int> pos_coll;
    static const std::vector<int> pos_row;
};
