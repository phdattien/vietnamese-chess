//
// Created by tiendat on 13.05.22.
//
#pragma once
#include "CTroop.h"


class CHorse : public CTroop {
public:
    CHorse ( const std::string &name, SIDE side, const CCoord &coord );

private:

public:
    std::set<CCoord> getPossibleMoves ( const std::shared_ptr<CTroop> currBoard[10][9] ) const override;
    bool inWay ( const CCoord& newCoord, const std::shared_ptr<CTroop> (*currBoard)[9] ) const;
};


