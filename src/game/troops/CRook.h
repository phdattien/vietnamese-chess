#pragma once
#include "CTroop.h"

class CRook : public CTroop {

public:
    CRook ( std::string name, SIDE side, CCoord coord ) : CTroop ( move(name), side, coord ) {};
    std::set<CCoord> getPossibleMoves ( const std::unique_ptr<CTroop> currBoard ) const override;
};


