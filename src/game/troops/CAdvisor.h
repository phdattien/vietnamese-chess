#pragma once
#include "CTroop.h"


class CAdvisor : public CTroop {
public:
    CAdvisor ( const std::string &name, SIDE side, const CCoord &coord );

    std::set<CCoord> getPossibleMoves ( const std::unique_ptr<CTroop> (*currBoard)[8] ) const override;

private:
    bool isInsideAdvisorMovements ( const CCoord& newCoord ) const;
};


