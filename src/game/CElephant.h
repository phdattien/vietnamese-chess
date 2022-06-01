#pragma once
#include "CTroop.h"

class CElephant : public CTroop {
public:
    CElephant ( SIDE side, const CCoord &coord );

    std::set<CCoord> getPossibleMoves ( const Board &currBoard ) const override;
    char getName () const override;


private:
    char m_Name = ELEPHANT;
    bool isInsideElephantMovements( const CCoord& newCoord ) const;
    bool inWay ( const CCoord& newCoord, const Board (&currBoard)) const;
    static const std::vector<int> POS_COL;
    static const std::vector<int> POS_ROW;
    static const std::set<CCoord> ELEPHANT_MOVEMENTS_RED;
    static const std::set<CCoord> ELEPHANT_MOVEMENTS_BLACK;
};


