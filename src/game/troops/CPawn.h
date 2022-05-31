//
// Created by tiendat on 13.05.22.
//
#pragma once

#include <vector>
#include "CTroop.h"

class CPawn : public CTroop {
public:
    CPawn ( SIDE side, const CCoord &coord );

    std::set<CCoord> getPossibleMoves ( const Board & currBoard ) const override;


    char getName () const override;

private:
    char m_Name = PAWN;
    static const std::vector<int> POS_COL;
    static const std::vector<int> POS_ROW;
    bool isValidCoord ( const CCoord &newCoord, const Board & currBoard  ) const;
};
