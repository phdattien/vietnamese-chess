#include "CCoord.h"
#include <tuple>
#include <iostream>


CCoord::CCoord ( const std::string & coord ) {
    m_Colum = 8 - ( coord[1] - '0' );
    m_Row = _toupper(coord[0]) - 'A';
}

bool CCoord::ValidateCoord () const {
    if ( m_Colum < 0 || m_Colum > 8)
        return false;

    if ( m_Row < 0 || m_Row > 8)
        return false;
    return true;
}

bool CCoord::operator< ( const CCoord & rhs ) const {
    return  std::tie ( m_Colum, m_Row ) < std::tie ( rhs.m_Row, rhs.m_Row );
}
