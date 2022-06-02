//
// Created by tiendat on 13.05.22.
//
#pragma once
#include "CTroop.h"


class CHorse : public CTroop {
public:
    CHorse ( SIDE side, const CCoord &coord );
    std::set<CCoord> getPossibleMoves ( const Board & currBoard ) const override;
    char getName () const override;

private:
    char m_Name = HORSE;
    static const std::vector<int> POS_COL;
    static const std::vector<int> POS_ROW;
    bool inWay ( const CCoord& newCoord, const Board & currBoard  ) const;

};


