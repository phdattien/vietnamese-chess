//
// Created by tiendat on 09.05.22.
//
#pragma once
#include "CTroop.h"
#include <vector>

class CGeneral : public CTroop {
public:
    CGeneral ( SIDE side, const CCoord &coord );

    std::set<CCoord> getPossibleMoves ( const Board &currBoard ) const override;
    char getName () const override;

private:
    char  m_Name = GENERAL;
    bool isInsideGeneralMovements ( const CCoord& newCoord ) const;
    static const std::vector<int> POS_COL;
    static const std::vector<int> POS_ROW;
};
