#pragma once
#include "troops/CTroop.h"
#include <vector>
#include <memory>
#include "Move.h"
#include <stack>
//#include "utility/UI.h"

const size_t COL_SIZE = 10;
const size_t ROW_SIZE = 9;

class CBoard {
public:
    // takes all troops in vector and fill the board
    CBoard ( const std::string & fen );

    bool isInCheck ();

    std::shared_ptr<CTroop> & getTroopOnCoord ( const CCoord & from );

    std::shared_ptr<CTroop> getTroopOnCoord ( const CCoord & from ) const;

    bool isRedToMove () const;

    void printAttackedMoves ();

    void printAttackedMap ();

    void MakeMove ( const Move & movement );

    void UnMakeMove ( const Move & movement );

    const std::vector<Move> & generateMoves ();

    bool isDraw();

    friend class UI;

private:
//    std::shared_ptr<CTroop> m_Board[COL_SIZE][ROW_SIZE];
    std::vector<std::vector<std::shared_ptr<CTroop>>> m_Board;
    std::vector<std::shared_ptr<CTroop>> m_BlackTroops;
    std::vector<std::shared_ptr<CTroop>> m_RedTroops;
    std::shared_ptr<CTroop> m_RedGeneral;
    std::shared_ptr<CTroop> m_BlackGeneral;

    std::stack<std::shared_ptr<CTroop>> m_HistoryCapturedTroops;

    std::vector<Move> possibleMoves;
    // who is moving right now
    bool RedToMove = true;

    std::vector<Move> generatePseudoLegalMovesByColour ( const std::vector<std::shared_ptr<CTroop>>& troops );
    std::vector<std::shared_ptr<CTroop>> & getTroopsOnOppositePlay ();
    bool canCross ( const std::vector<char>& troopNames );
    const CCoord & getGeneralOnPlayCoord () const;
    const CCoord & getGeneralOnOppositePlayCoord () const;
    void addMoves ( const CCoord & start, const std::set<CCoord>& cords, std::vector<Move>& moves );
    std::vector<Move> generatePseudoLegalMoves ();
    std::vector<std::shared_ptr<CTroop>> & getTroopsOnPlay ();
    bool isGeneralsFacing   ();
};

