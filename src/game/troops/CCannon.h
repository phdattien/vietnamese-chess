//
// Created by tiendat on 20.05.22.
//
#pragma once
#include "CTroop.h"


class CCannon : CTroop {
public:
private:
public:
    CCannon ( SIDE side, const CCoord &coord );

private:
    std::set<CCoord> getPossibleMoves ( const std::shared_ptr<CTroop> (*currBoard)[9] ) const override;
    const std::string &getName () const override;

private:
    std::string m_Name = "C";
    void getSlidingCoords ( int start, char still, int direction, int end, const std::shared_ptr<CTroop> (*currBoard)[9], std::set<CCoord> & cords ) const;
};


