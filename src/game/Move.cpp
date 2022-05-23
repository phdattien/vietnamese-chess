//
// Created by tiendat on 21.05.22.
//

#include "Move.h"

Move::Move ( const CCoord &mFrom, const CCoord &mTo ) : m_From ( mFrom ), m_To ( mTo ) {}

std::ostream &operator<< ( std::ostream &os, const Move &move ) {
    os << "From: " << move.m_From.m_Colum << " " << move.m_From.m_Row << " " << "To: " << move.m_To.m_Colum << " " << move.m_To.m_Row;
    return os;
}

