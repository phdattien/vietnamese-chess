#include "CCoord.h"
#include <tuple>
#include <iostream>


CCoord::CCoord ( const std::string & coord ) {
    if ( coord.size() == 3)
        m_Colum = 0;
    else
        m_Colum = 10 - ( coord[1] - '0' );
    m_Row = _toupper(coord[0]) - 'A';
}

bool CCoord::isInsideBoard () const {
    if ( m_Colum < 0 || m_Colum >= 10) {
        return false;
    }

    if ( m_Row < 0 || m_Row >= 9)
        return false;
    return true;
}

bool CCoord::operator< ( const CCoord & rhs ) const {
    return  std::tie ( m_Colum, m_Row ) < std::tie ( rhs.m_Colum, rhs.m_Row );
}

bool CCoord::operator== ( const CCoord &rhs ) const {
    return ( m_Row == rhs.m_Row && m_Colum == rhs.m_Colum );
}
