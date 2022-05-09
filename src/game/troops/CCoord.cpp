#include "CCoord.h"

CCoord::CCoord ( const std::string & coord ) {
    if ( coord[1] != '1')
        m_Colum = 8 % ( coord[1] - '0' );
    else
        m_Colum = 7;
    m_Row = _toupper(coord[0]) - 'A';
}

bool CCoord::ValidateCoord () const {
    if ( m_Colum < 0 || m_Colum > 8)
        return false;

    if ( m_Row < 0 || m_Row > 8)
        return false;
    return true;
}
