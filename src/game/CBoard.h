#pragma once
#include "troops/CTroop.h"
#include <vector>
#include <memory>
#include "Move.h"
//#include "utility/CBoardUi.h"

const size_t ROW_SIZE = 9;
const size_t COL_SIZE = 10;


class CBoard {
public:
    // takes all troops in vector and fill the board
    CBoard ( const std::string & fen = "rheagaehr/9/1c5c1/s1s1s1s1s/9/9/S1S1S1S1S/1C5C1/9/RHEAGAEHR r" );


    bool isLegalMove ( const std::shared_ptr<CTroop> & troopOnPos, const CCoord & dest ) const;
    // return true if two generals are facing each other
    bool isGeneralsFacing   ();

    bool isInCheck ();

    std::shared_ptr<CTroop> & getTroopOnCoord ( const CCoord & from );

    std::shared_ptr<CTroop> getTroopOnCoord ( const CCoord & from ) const;

    std::vector<std::shared_ptr<CTroop>> & getTroopsOnPlay ();

    bool isRedToMove () const;

    std::vector<Move> generatePseudoLegalMoves ();

    void printAttackedMoves ();

    void printAttackedMap ();

    void addMoves ( const CCoord & start, const std::set<CCoord>& cords, std::vector<Move>& moves );

    void MakeMove ( const Move & movement );


    void UnMakeMove ( const Move & movement );

    const std::vector<Move> & generateMoves ();

    bool isDraw();

    friend class CBoardUi;



private:
    char GENERAL = 'G';
    std::shared_ptr<CTroop> m_Board[COL_SIZE][ROW_SIZE];
    std::vector<std::shared_ptr<CTroop>> m_BlackTroops;
    std::vector<std::shared_ptr<CTroop>> m_RedTroops;
    std::shared_ptr<CTroop> m_RedGeneral;
    std::shared_ptr<CTroop> m_BlackGeneral;
    std::shared_ptr<CTroop> m_PrevCapturedTroop;
    std::vector<Move> possibleMoves;
    // who is moving right now
    bool RedToMove = true;


    std::vector<Move> generatePseudoLegalMovesByColour ( const std::vector<std::shared_ptr<CTroop>>& troops );

    std::vector<std::shared_ptr<CTroop>> & getTroopsOnOpositePlay ();
    bool canCross ( const std::vector<char>& troopNames );

    const CCoord & getGeneralOnPlayCoord () const;

    const CCoord & getGeneralOnOppositePlayCoord () const;
};

