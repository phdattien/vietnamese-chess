//
// Created by tiendat on 09.05.22.
//

#include "CRook.h"

std::set<CCoord> CRook::getPossibleMoves ( const std::unique_ptr<CTroop> currBoard ) const {
    std::set<CCoord> coords;
    for ( int i = 0; i < 8; i++ ) {
        coords.emplace ( i, m_Coord.m_Row );
        coords.emplace ( m_Coord.m_Colum, i );
    }
    return coords;
}
