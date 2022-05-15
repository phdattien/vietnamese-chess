#pragma once
#include "CTroop.h"

class CElephant : public CTroop {
public:
    CElephant ( const std::string &name, SIDE side, const CCoord &coord );
    std::set<CCoord> getPossibleMoves ( const std::shared_ptr<CTroop> currBoard[10][9] ) const override;

private:
    bool isInsideElephantMovements( const CCoord& newCoord ) const;
    bool inWay ( const CCoord& newCoord, const std::shared_ptr<CTroop> (*currBoard)[9] ) const;
};


