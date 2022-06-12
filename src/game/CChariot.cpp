//
// Created by tiendat on 13.05.22.
//

#include "CChariot.h"


bool CChariot::isValidCoord ( const CCoord &newCoord, const Board (&currBoard)) const {
    // if newCoord is outside of board or there is a troop but, on the same side or it is outside of the palace
    auto & troopOnPos = currBoard[newCoord.m_Colum][newCoord.m_Row];
    if ( troopOnPos && troopOnPos->getSide() == m_Side )
        return false;
    return true;
}

void CChariot::getSlidingCoords ( int start, char still, int direction, int end,
                                  const Board (&currBoard),
                                  std::set<CCoord> & cords ) const {
    if ( start == end )
        return;

    int finish = abs (start - end );
    while ( finish ) {
        --finish;
        start += direction;
        CCoord newCoord = still == 'r' ? CCoord( m_Coord.m_Colum, start ) : CCoord ( start, m_Coord.m_Row );
        if ( ! isValidCoord ( newCoord, currBoard ) )
            break;

        auto & troopOnPos = currBoard[newCoord.m_Colum][newCoord.m_Row];
        // if is a capture troop add and break
        if ( troopOnPos && troopOnPos->getSide() != m_Side ) {
            cords.insert (newCoord);
            break;
        }
        cords.insert (newCoord);
    }
}



std::set<CCoord> CChariot::getPossibleMoves ( const Board &currBoard ) const {
    std::set<CCoord> s_coord;
    // add coords right directions, 9 - is width of board
    getSlidingCoords ( m_Coord.m_Row, 'r', 1, ROW_SIZE - 1, currBoard, s_coord ) ; // right cords
    getSlidingCoords ( m_Coord.m_Row, 'r', -1, 0, currBoard, s_coord ); // left cords
    getSlidingCoords ( m_Coord.m_Colum, 'c', 1, COL_SIZE - 1, currBoard, s_coord ); // up cords

    getSlidingCoords ( m_Coord.m_Colum, 'c', -1, 0, currBoard, s_coord ); // down cords
    return s_coord;
}

char CChariot::getName () const {
    return m_Name;
}

CChariot::CChariot ( SIDE side, const CCoord &coord ) : CTroop ( side, coord ) {}




