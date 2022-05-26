//
// Created by tiendat on 13.05.22.
//

#include "CSoldier.h"

const std::vector<int> CSoldier::POS_COL  {  0, 0 };
const std::vector<int> CSoldier::POS_ROW  {  1, -1 };




bool CSoldier::isValidCoord ( const CCoord &newCoord, const std::shared_ptr<CTroop> (*currBoard)[9] ) const {
    // if newCoord is outside of board or there is a troop but, on the same side or it is outside of the palace
    auto & troopOnPos = currBoard[newCoord.m_Colum][newCoord.m_Row];
    if (     ! newCoord.isInsideBoard ()
             ||  ( troopOnPos && troopOnPos->getSide() == m_Side ) )
    {
        return false;
    }
    return true;
}


std::set<CCoord> CSoldier::getPossibleMoves ( const std::shared_ptr<CTroop> currBoard[10][9] ) const {
    std::set<CCoord> s_coords;

    int direction = m_Side == SIDE::RED ? -1 : 1;

    CCoord newCoord ( m_Coord.m_Colum + direction, m_Coord.m_Row );
    // if newCoord is outside of board or there is a troop but, on the same side or it is outside of the palace
    if ( isValidCoord ( newCoord, currBoard ) )
        s_coords.insert (newCoord);

    if ( ( m_Side == SIDE::RED && ( m_Coord.m_Colum <= 4) )
           || ( m_Side == SIDE::BLACK && ( m_Coord.m_Colum >= 5 ) ) ) {

        for ( size_t i = 0; i < POS_COL.size(); i++ ) {
            int newPosI = m_Coord.m_Colum + POS_COL[i];
            int newPosJ = m_Coord.m_Row + POS_ROW[i];

            newCoord = CCoord( newPosI, newPosJ );

            // if newCoord is outside of board or there is a troop but, on the same side or it is outside of the palace
            if ( !isValidCoord ( newCoord, currBoard ) )
                continue;
            s_coords.insert ( newCoord );
        }
    }

    return s_coords;
}

char CSoldier::getName () const {
    return m_Name;
}

CSoldier::CSoldier ( SIDE side, const CCoord &coord ) : CTroop ( side, coord ) {}
