//
// Created by tiendat on 13.05.22.
//

#include "CPawn.h"

const std::vector<int> CPawn::POS_COL  { 0, 0 };
const std::vector<int> CPawn::POS_ROW  { 1, -1 };

bool CPawn::isValidCoord ( const CCoord &newCoord, const Board & currBoard ) const {
    // if newCoord is outside of board or there is a troop but, on the same side or it is outside of the palace
    auto & troopOnPos = currBoard[newCoord.m_Colum][newCoord.m_Row];
    if (     ! newCoord.isInsideBoard ()
             ||  ( troopOnPos && troopOnPos->getSide() == m_Side ) )
    {
        return false;
    }
    return true;
}


std::set<CCoord> CPawn::getPossibleMoves ( const CTroop::Board &currBoard ) const  {
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

char CPawn::getName () const {
    return m_Name;
}

CPawn::CPawn ( SIDE side, const CCoord &coord ) : CTroop ( side, coord ) {}

