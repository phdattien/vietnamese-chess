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

    std::shared_ptr<CTroop> & getTroopOnCoord ( const CCoord & from );

    std::shared_ptr<CTroop> getTroopOnCoord ( const CCoord & from ) const;

    std::vector<std::shared_ptr<CTroop>> & getTroopsOnPlay ();

    // void Move ( const CCoord &from, const CCoord & to);

//    void printInside () const;

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

    bool isRedToMove () const;

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
};

