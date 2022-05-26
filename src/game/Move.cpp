//
// Created by tiendat on 21.05.22.
//

#include "Move.h"

Move::Move ( const CCoord &mFrom, const CCoord &mTo ) : m_From ( mFrom ), m_To ( mTo ) {}

std::ostream &operator<< ( std::ostream &os, const Move &move ) {
    os << "From: " << move.m_From << " " << "To: " << move.m_To;
    return os;
}

bool Move::operator== ( const Move &rhs ) {
   return m_From == rhs.m_From && m_To == rhs.m_To;
}

