//
// Created by tiendat on 13.05.22.
//
#pragma once

#include <vector>
#include "CTroop.h"


class CPawn : public CTroop {
public:
    CPawn ( SIDE side, const CCoord &coord );

    std::set<CCoord> getPossibleMoves ( const std::shared_ptr<CTroop> currBoard[10][9] ) const override;

    char getName () const override;

private:
    char m_Name = 'P';
    static const std::vector<int> POS_COL;
    static const std::vector<int> POS_ROW;
    bool isValidCoord ( const CCoord &newCoord, const std::shared_ptr<CTroop> (*currBoard)[9] ) const;
};

