#include "CCoord.h"
#include <tuple>
#include <iostream>
#include <regex>


CCoord::CCoord ( const std::string & coord ) {
    if (  ! std::regex_match (coord, std::regex("[a-iA-I]([1-9]|10)") ))
        throw std::invalid_argument("Bad coord string");

    m_Colum = parseColum (coord);
    m_Row = parseRow (coord);
}

bool CCoord::isInsideBoard () const {
    if ( m_Colum < 0 || m_Colum >= COL) {
        return false;
    }

    if ( m_Row < 0 || m_Row >= ROW)
        return false;
    return true;
}

bool CCoord::operator< ( const CCoord & rhs ) const {
    return  std::tie ( m_Colum, m_Row ) < std::tie ( rhs.m_Colum, rhs.m_Row );
}

bool CCoord::operator== ( const CCoord &rhs ) const {
    return ( m_Row == rhs.m_Row && m_Colum == rhs.m_Colum );
}

std::ostream &operator<< ( std::ostream &os, const CCoord &coord ) {
    os << char( coord.m_Row + 'A' ) << 10 - coord.m_Colum;
    return os;
}

int CCoord::parseColum ( const std::string& coord ) {
    if ( coord.size() == 3)
        return 0;
    else
        return 10 - ( coord[1] - '0' );
}

int CCoord::parseRow ( const std::string& coord ) {
    return _toupper(coord[0]) - 'A';

}
