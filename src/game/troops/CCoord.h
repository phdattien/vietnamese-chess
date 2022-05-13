#pragma once
#include <string>

struct CCoord {
    CCoord ( int c, int r ) : m_Colum (c), m_Row(r) {};
    /* coord is a sttring with human readible string */
    explicit CCoord ( const std::string & coord );
    bool isInsideBoard() const;
    bool operator < ( const CCoord & rhs ) const;
    bool operator == ( const CCoord & rhs ) const;

    int m_Colum;
    int m_Row;
};

