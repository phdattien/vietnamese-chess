//
// Created by tiendat on 13.05.22.
//
#pragma once
#include "CTroop.h"
#include <vector>



class CChariot : public CTroop {
public:

    CChariot ( SIDE side, const CCoord &coord );

    const std::string &getName () const override;

private:
    std::string m_Name = "R";

    std::set<CCoord> getPossibleMoves ( const std::shared_ptr<CTroop> currBoard[10][9] ) const override;
    // control if on a newCoord on a currBoard state is a ally troop
    bool isValidCoord ( const CCoord& newCoord, const std::shared_ptr<CTroop> (*currBoard)[9]) const;
    void getSlidingCoords ( int start, char still, int direction, int end, const std::shared_ptr<CTroop> (*currBoard)[9], std::set<CCoord> & cords ) const;
};

