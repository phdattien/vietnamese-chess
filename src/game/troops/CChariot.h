//
// Created by tiendat on 13.05.22.
//
#pragma once
#include "CTroop.h"
#include <vector>



class CChariot : public CTroop {
public:
    CChariot ( const std::string &name, SIDE side, const CCoord &coord );

private:
public:
    std::set<CCoord> getPossibleMoves ( const std::unique_ptr<CTroop> currBoard[10][9] ) const override;
    // control if on a newCoord on a currBoard state is a ally troop
    bool isValidCoord ( const CCoord& newCoord, const std::unique_ptr<CTroop> (*currBoard)[9]) const;
    void getSideCoords ( int start, char still, int direction, int end, const std::unique_ptr<CTroop> (*currBoard)[9],  std::set<CCoord> & cords ) const;
};

