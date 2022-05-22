#pragma once
#include "troops/CTroop.h"
#include <vector>
#include <memory>
#include "Move.h"

const size_t ROW_SIZE = 9;
const size_t COL_SIZE = 10;

// board.isLegalMove ( m_board[3][8],  dest - CCoord ( "41" )


class CBoard {
public:
    // takes all troops in vector and fill the board
    CBoard ( std::vector<std::shared_ptr<CTroop>> & troops );
    CBoard () = default;

    bool isLegalMove ( const std::shared_ptr<CTroop> & troopOnPos, const CCoord & dest ) const;
    // return true if two generals are facing each other
    bool isGeneralsFacing   ();

    std::shared_ptr<CTroop> & getTroopOnCoord ( const CCoord & from );

    std::shared_ptr<CTroop> getTroopOnCoord ( const CCoord & from ) const;

    std::vector<std::shared_ptr<CTroop>> & getTroopsOnPlay ();

    // void Move ( const CCoord &from, const CCoord & to);

    void printBoard () const;

    //getAllpseudoLegalMoves
    std::vector<Move> generatePseudoLegalMoves ();

    void printAttackedMoves ();

    void printAttackedMap ();

    void addMoves ( const CCoord & start, const std::set<CCoord>& cords, std::vector<Move>& moves );

    void MakeMove ( const Move & movement );

    const CCoord & getGeneralOnPlayCoord () const;

    const CCoord & getGeneralOnOppositePlayCoord () const;

    void UnMakeMove ( const Move & movement );


    const std::vector<Move> & generateMoves ();

private:
    std::string GENERAL = "G";
    std::shared_ptr<CTroop> m_Board[COL_SIZE][ROW_SIZE];
    std::vector<std::shared_ptr<CTroop>> m_BlackTroops;
    std::vector<std::shared_ptr<CTroop>> m_RedTroops;
    std::shared_ptr<CTroop> m_RedGeneral;
    std::shared_ptr<CTroop> m_BlackGeneral;
    std::shared_ptr<CTroop> m_PrevCapturedTroop;
    std::vector<Move> possibleMoves;
    // who is moving right now
    bool RedToMove = true;
};

