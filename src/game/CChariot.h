//
// Created by tiendat on 13.05.22.
//
#pragma once
#include "CTroop.h"
#include <vector>



class CChariot : public CTroop {
public:

    CChariot ( SIDE side, const CCoord &coord );

    char getName () const override;


private:
    char m_Name = CHARIOT;


    std::set<CCoord> getPossibleMoves ( const Board &currBoard ) const override;
    // control if on a newCoord on a currBoard state is a ally troop
    bool isValidCoord ( const CCoord& newCoord, const Board (&currBoard)) const;
    void getSlidingCoords ( int start, char still, int direction, int end, const Board (&currBoard), std::set<CCoord> & cords ) const;
};

