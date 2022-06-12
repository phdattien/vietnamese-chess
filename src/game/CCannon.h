//
// Created by tiendat on 20.05.22.
//
#pragma once
#include "CTroop.h"
#include "CCoord.h"


class CCannon : public CTroop {
public:
    CCannon ( SIDE side, const CCoord &coord );

    char getName () const override;

    std::set<CCoord> getPossibleMoves ( const Board &currBoard) const override;


private:
    char m_Name = CANNON;
    void getSlidingCoords ( int start, char still, int direction, int end, const Board (&currBoard), std::set<CCoord> & cords ) const;
};


