//
// Created by tiendat on 09.05.22.
//

#include <vector>
#include "CKing.h"

std::set<CCoord> CKing::getPossibleMoves () const {
    std::vector<int> pos_coll { 1, -1, 0,  0, 1, 1, -1, -1 };
    std::vector<int> pos_row  { 0,  0, 1, -1, 1, -1, 1, -1 };
    std::set<CCoord> s_coord;

    for ( size_t i = 0; i < 7; i++ ) {
        int newPosI = m_Coord.m_Colum + pos_coll[i];
        int newPosJ = m_Coord.m_Row + pos_row[i];

        CCoord newCoord ( newPosI, newPosJ );
        if ( newCoord.ValidateCoord() )
            s_coord.insert (newCoord );
    }
    return s_coord;
}
