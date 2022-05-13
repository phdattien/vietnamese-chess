//
// Created by tiendat on 13.05.22.
//
#pragma once

#include <vector>
#include "CTroop.h"


class CSoldier : public CTroop {
public:
    CSoldier ( const std::string &name, SIDE side, const CCoord &coord );

private:
public:
    std::set<CCoord> getPossibleMoves ( const std::unique_ptr<CTroop> (*currBoard)[8] ) const override;
    static const std::vector<int> POS_COL;
    static const std::vector<int> POS_ROW;
};

