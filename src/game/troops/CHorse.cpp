//
// Created by tiendat on 13.05.22.
//

#include "CHorse.h"
#include <vector>
#include <iostream>


const std::vector<int> POS_COLL {  2, 2, -2, -2, -1, 1, -1,  1 };
const std::vector<int> POS_ROW  { -1, 1, -1,  1,  2, 2, -2, -2};


bool CHorse::inWay ( const CCoord &newCoord, const std::shared_ptr<CTroop> (*currBoard)[9] ) const {
    // test if between new Coords and  currCoord is standing something if does remove the new cord from set
    int testCol =  m_Coord.m_Colum > newCoord.m_Colum ? 1 : -1;
    int testRow =  m_Coord.m_Row > newCoord.m_Row ? 1 : -1;

    if (  currBoard[testCol + newCoord.m_Colum][testRow + newCoord.m_Row] ) // there is someting in between
        return true;

    return false;
}

std::set<CCoord> CHorse::getPossibleMoves ( const std::shared_ptr<CTroop> currBoard[10][9] ) const {
    std::set<CCoord> s_coord;
    for ( size_t i = 0; i < POS_COLL.size(); i++ ) {
        int newPosI = m_Coord.m_Colum + POS_COLL[i];
        int newPosJ = m_Coord.m_Row + POS_ROW[i];

        CCoord newCoord ( newPosI, newPosJ );
        auto & troopOnPos = currBoard[newCoord.m_Colum][newCoord.m_Row];

        // if newCoord is outside of board or there is a troop but, on the same side or it is outside of the palace
        if (     ! newCoord.isInsideBoard ()
                 ||  ( troopOnPos && troopOnPos->getSide() == m_Side )
                 ||   inWay ( newCoord, currBoard ) )
        {
            continue;
        }

        s_coord.insert (newCoord );
    }
    return s_coord;
}

char CHorse::getName () const {
    return m_Name;
}

CHorse::CHorse ( SIDE side, const CCoord &coord ) : CTroop ( side, coord ) {}
