//
// Created by tiendat on 09.05.22.
//

#include <vector>
#include "CGeneral.h"

const std::vector<int> CGeneral::pos_coll { 1, -1, 0,  0, 1,  1, -1, -1 };
const std::vector<int> CGeneral::pos_row  { 0,  0, 1, -1, 1, -1,  1, -1};

// could be better if all the new cords are initiliaze at the start
bool CGeneral::isInsideGeneralMovements ( const CCoord &newCoord ) const {
    std::set<CCoord> movements;

    // general on red side all his movements from E2 otherwise from E9
    CCoord start = m_Side == SIDE::RED ? CCoord("E2") : CCoord("E9");

    for ( size_t i = 0; i < 8; i++ ) {
        int newPosI = start.m_Colum + pos_coll[i];
        int newPosJ = start.m_Row + pos_row[i];

        // newCoord is in the one of the possible general moves (8) - all movements in palace
        if ( newCoord == CCoord ( newPosI, newPosJ ) )
            return true;
    }
    return false;
}


std::set<CCoord> CGeneral::getPossibleMoves ( const std::shared_ptr<CTroop> currBoard[10][9] ) const {
    std::set<CCoord> s_coord;

    // general can only move inside his "palace"
    // generate all possible moves for CGeneral
    for ( size_t i = 0; i < 4; i++ ) {
        int newPosI = m_Coord.m_Colum + pos_coll[i];
        int newPosJ = m_Coord.m_Row + pos_row[i];

        CCoord newCoord ( newPosI, newPosJ );
        auto & troopOnPos = currBoard[newCoord.m_Colum][newCoord.m_Row];

        // if newCoord is outside of board or there is a troop but, on the same side or it is outside of the palace
        if (     ! newCoord.isInsideBoard ()
             ||  ( troopOnPos && troopOnPos->getSide() == m_Side ) // troop on new pos already exist a troop but he is on same side
             ||  !  isInsideGeneralMovements ( newCoord ) )
        {
            continue;
        }
        s_coord.insert (newCoord );
    }
    return s_coord;
}
