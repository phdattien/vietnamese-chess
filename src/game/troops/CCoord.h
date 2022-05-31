#pragma once
#include <string>

struct CCoord {
public:
    CCoord ( size_t c, size_t r ) : m_Colum ( c), m_Row( r) {};
    CCoord () = default;
    /* coord is a sttring with human readible string */
    explicit CCoord ( const std::string & coord );
    bool isInsideBoard() const;
    bool operator < ( const CCoord & rhs ) const;
    bool operator == ( const CCoord & rhs ) const;
    friend std::ostream & operator << ( std::ostream & os, const CCoord & coord );
    int m_Colum;
    int m_Row;
private:
    int parseColum ( const std::string& cord );
    int parseRow ( const std::string& cord );
};

