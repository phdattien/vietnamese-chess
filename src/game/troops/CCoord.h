#pragma once
#include <string>

struct CCoord {
    CCoord ( int c, int r ) : m_Colum (x), m_Row(y) {};
    /* coord is a sttring with human readible string */
    explicit CCoord ( const std::string & coord );
    bool isInsideBoard() const;
    bool operator < ( const CCoord & rhs ) const;
    bool operator == ( const CCoord & rhs ) const;

    int m_Colum;
    int m_Row;
};

