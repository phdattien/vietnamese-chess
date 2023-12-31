//
// Created by tiendat on 20.05.22.
//

#include "CCannon.h"
#include <iostream>

CCannon::CCannon ( SIDE side, const CCoord &coord ) : CTroop ( side, coord ) {}


char CCannon::getName () const {
    return m_Name;
}

void CCannon::getSlidingCoords ( int start, char still, int direction, int end, const Board (&currBoard),
                                 std::set<CCoord> &cords ) const {
    if ( start == end )
        return;

    bool skip = false;
    int finish = abs (start - end );
    while ( finish ) {
        --finish;
        start += direction;
        CCoord newCoord = still == 'r' ? CCoord( m_Coord.m_Colum, start ) : CCoord ( start, m_Coord.m_Row );

        auto & troopOnPos = currBoard[newCoord.m_Colum][newCoord.m_Row];
        // any troop on this position
        if ( troopOnPos && !skip ) {
            skip = true;
            continue;
        }


        if ( troopOnPos && skip ) { // adding a jump take movement
            if ( troopOnPos->getSide() != m_Side )
                cords.insert (newCoord);
            break;
        }

        if ( ! skip )
            cords.insert (newCoord);
    }

}

std::set<CCoord> CCannon::getPossibleMoves ( const Board (&currBoard)) const {
    std::set<CCoord> s_coord;
    // add coords right directions, 9 - is width of board
    getSlidingCoords ( m_Coord.m_Row, 'r', 1, ROW_SIZE - 1, currBoard, s_coord ) ; // right cords
    getSlidingCoords ( m_Coord.m_Row, 'r', -1, 0, currBoard, s_coord ); // left cords
    getSlidingCoords ( m_Coord.m_Colum, 'c', 1, COL_SIZE - 1, currBoard, s_coord ); // up cords
    getSlidingCoords ( m_Coord.m_Colum, 'c', -1, 0, currBoard, s_coord ); // down cords

    return s_coord;

}

