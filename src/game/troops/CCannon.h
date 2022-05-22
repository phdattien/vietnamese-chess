//
// Created by tiendat on 20.05.22.
//
#pragma once
#include "CTroop.h"
#include "CCoord.h"


class CCannon : public CTroop {
public:
    CCannon ( SIDE side, const CCoord &coord );

    const std::string &getName () const override;

private:
    std::string m_Name = "C";
    std::set<CCoord> getPossibleMoves ( const std::shared_ptr<CTroop> (*currBoard)[9] ) const override;
    void getSlidingCoords ( int start, char still, int direction, int end, const std::shared_ptr<CTroop> (*currBoard)[9], std::set<CCoord> & cords ) const;
};


