#pragma once
#include <string>

/**
 * Structure CCoord
 */

const int COL = 10;
const int ROW = 9;

struct CCoord {
public:
    /**
     * Constructor of Coord
     * @param c colum
     * @param r row
     */
    CCoord ( size_t c, size_t r ) : m_Colum ( c), m_Row( r) {};
    CCoord () = default;
    /**
     * Constructor takes string and par to array colum and row
     * @param coord string of chess coordinates
     */
    explicit CCoord ( const std::string & coord );
    /**
     * Method to detect if Coordinate is in board
     * @return
     */
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

