//
// Created by tiendat on 13.05.22.
//

#include "CChariot.h"

CChariot::CChariot ( const std::string &name, SIDE side, const CCoord &coord ) : CTroop ( name, side, coord ) {}

bool CChariot::isValidCoord ( const CCoord &newCoord, const std::unique_ptr<CTroop> (*currBoard)[8] ) const {
    // if newCoord is outside of board or there is a troop but, on the same side or it is outside of the palace
    auto & troopOnPos = currBoard[newCoord.m_Colum][newCoord.m_Row];
    if ( troopOnPos && troopOnPos->getSide() == m_Side )
        return false;
    return true;
}


void CChariot::getSideCoords ( int start, char still, int direction, int end,
                                          const std::unique_ptr<CTroop> (*currBoard)[8],
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
        cords.insert (newCoord);
    }
}



std::set<CCoord> CChariot::getPossibleMoves ( const std::unique_ptr<CTroop> (*currBoard)[8] ) const {
    std::set<CCoord> s_coord;
    // add coords right directions, 9 - is width of board
    getSideCoords ( m_Coord.m_Row, 'r', 1, 8, currBoard, s_coord ) ; // right cords
    getSideCoords ( m_Coord.m_Row, 'r', -1, 0, currBoard, s_coord ); // left cords
    getSideCoords ( m_Coord.m_Colum, 'c', 1, 9, currBoard, s_coord ); // up cords
    getSideCoords ( m_Coord.m_Colum, 'c', -1, 0, currBoard, s_coord ); // down cords
    return s_coord;
}


