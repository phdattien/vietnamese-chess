#pragma once
#include "troops/CTroop.h"
#include <vector>
#include <memory>

const size_t ROW_SIZE = 9;
const size_t COL_SIZE = 10;

// board.isLegalMove ( m_board[3][8],  dest - CCoord ( "41" )


class CBoard {
public:
    // takes all troops in vector and fill the board
    CBoard ( std::vector<std::shared_ptr<CTroop>> & troops );
    CBoard () = default;


    bool isLegalMove ( const std::shared_ptr<CTroop> & troopOnPos, const CCoord & dest ) const;
    // find if two generals face each other return false
    bool isGeneralsFace   ();
    void print () const;


private:
//    std::shared_ptr<CTroop> m_Board[COL_SIZE][ROW_SIZE];

    std::shared_ptr<CTroop> m_Board[COL_SIZE][ROW_SIZE];
    const std::shared_ptr<CTroop> & findKing ( ) const;
};

