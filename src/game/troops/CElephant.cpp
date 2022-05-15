//
// Created by tiendat on 13.05.22.
//


#include "CElephant.h"
#include <vector>

const std::vector<int> pos_coll { 2,  2, -2, -2};
const std::vector<int> pos_row  { 2, -2,  2, -2};

const std::set<CCoord> ELEPHANT_MOVEMENTS_RED
        {
                CCoord("I3"),
                CCoord("E3"),
                CCoord("A3"),
                CCoord("G1"),
                CCoord("C1"),
                CCoord("C5"),
                CCoord("G5")
        };

std::set<CCoord> ELEPHANT_MOVEMENTS_BLACK
        {
                CCoord("I8"),
                CCoord("E8"),
                CCoord("A8"),
                CCoord("G10"),
                CCoord("C10"),
                CCoord("C6"),
                CCoord("G6")
        };

CElephant::CElephant ( const std::string &name, SIDE side, const CCoord &coord ) : CTroop ( name, side, coord ) {}

bool CElephant::isInsideElephantMovements ( const CCoord &newCoord ) const {
    return m_Side == SIDE::RED ? ELEPHANT_MOVEMENTS_RED.count (newCoord) : ELEPHANT_MOVEMENTS_BLACK.count (newCoord);
}

bool CElephant::inWay ( const CCoord &newCoord, const std::shared_ptr<CTroop> (*currBoard)[9] ) const {
    // test if between new Coords and  currCoord is standing something if does remove the new cord from set
    int testCol = ( m_Coord.m_Colum + newCoord.m_Colum ) / 2;
    int testRow = ( m_Coord.m_Row + newCoord.m_Row ) / 2;

    if (  currBoard[testCol][testRow ] ) // there is someting in between
        return true;

    return false;
}

std::set<CCoord> CElephant::getPossibleMoves ( const std::shared_ptr<CTroop> currBoard[10][9] ) const {
    std::set<CCoord> s_coord;
    //  advisor can't cross river
    // generate all possible moves for Elephant
    for ( size_t i = 0; i < pos_coll.size(); i++ ) {
        int newPosI = m_Coord.m_Colum + pos_coll[i];
        int newPosJ = m_Coord.m_Row + pos_row[i];

        CCoord newCoord ( newPosI, newPosJ );
        auto & troopOnPos = currBoard[newCoord.m_Colum][newCoord.m_Row];

        // if newCoord is outside of board or there is a troop but, on the same side or it is outside of the palace
        if (     ! newCoord.isInsideBoard ()
                 ||  ( troopOnPos && troopOnPos->getSide() == m_Side )
                 ||  !  isInsideElephantMovements( newCoord )
                 ||   inWay ( newCoord, currBoard ) )
        {
            continue;
        }

        s_coord.insert (newCoord );
    }
    return s_coord;
}

