#pragma once
#include "CTroop.h"
#include <vector>
#include <memory>
#include "Move.h"
#include <stack>

const size_t COL_SIZE = 10;
const size_t ROW_SIZE = 9;

/**
 * Class CBoard is main structure for this engine
 */
class CBoard {
public:
    using TroopsArr = std::vector<std::shared_ptr<CTroop>>;
    // takes all troops in vector and fill the board
    /**
     * Constructor init all private members, from fen
     * @param fen - special string to represent troops on board
     * @throw Exception if fen is wrong
     */
    CBoard ( const std::string & fen );

    void ChangeSide ();

    /**
     * Method if a current position is in Check
     * @return true if in Check false otherwise
     */
    bool isInCheck ();

    /**
     * Getter
     * @return array of red Troops
     */
    const TroopsArr & getRedTroops () const;

    /**
     * Getter
     * @return array of black Troops
     */
    const TroopsArr & getBlackTroops () const;

    /**
     * Method to get a troop from a position on Board
     * @param from place in Board
     * @return pointer to a Troop
     */
    std::shared_ptr<CTroop> & getTroopOnCoord ( const CCoord & from );

    /**
     * Method to get a troop from a position on Board
     * @param from place in Board
     * @return const Troop
     */
    std::shared_ptr<CTroop> getTroopOnCoord ( const CCoord & from ) const;

    /**
     * Method to detect which side is on the move
     * @return if true - red is on play false - black
     */
    bool isRedToMove () const;


    /**
     * Method print to console all available positions
     */
    void printAttackedMap ();

    /**
     * Method Move to move a piece. Remember which troop has he taken
     * movement must be correct
     * @param movement structure containing from an to
     */
    void MakeMove ( const Move & movement );

    /**
     * Method to unmake a move, returns to previous position
     * movement must be correct
     * @param movement structure containing from an to
     */
    void UnMakeMove ( const Move & movement );

    /**
     * Generate all possible Moves from a playing side
     * @return
     */
    const std::vector<Move> & generateMoves ();

    const CCoord & getRedKingCoord () const;

    const CCoord & getBlackKingCoord () const;

    /**
     * Simple Method to detect draw, T
     * TODO: better draw recognition
     * @return true if current position is a draw, false otherwise
     */
    bool isDraw();

    /**
     * friend class to be able to print a board to console
     */
    friend class UI;

private:
    /** @var 2D array of pointers, representing board and troops */
    std::vector<std::vector<std::shared_ptr<CTroop>>> m_Board;
    /* array of troops - faster Moves generation*/
    TroopsArr m_BlackTroops;
    TroopsArr m_RedTroops;
    std::shared_ptr<CTroop> m_RedGeneral;
    std::shared_ptr<CTroop> m_BlackGeneral;

    /** history of captured moves, to be able to UnMove and search */
    std::stack<std::shared_ptr<CTroop>> m_HistoryCapturedTroops;

    std::vector<Move> possibleMoves;
    /**  @var to recognize who's on the move */
    bool RedToMove = true;

    std::vector<Move> generatePseudoLegalMovesByColour ( const TroopsArr & troops );
    std::vector<std::shared_ptr<CTroop>> & getTroopsOnOppositePlay ();
    bool canCross ( const std::vector<char>& troopNames );
    const CCoord & getGeneralOnPlayCoord () const;
    const CCoord & getGeneralOnOppositePlayCoord () const;
    void addMoves ( const CCoord & start, const std::set<CCoord>& cords, std::vector<Move>& moves );
    /** generate all moves, without take account of making own king in danger */
    std::vector<Move> generatePseudoLegalMoves ();
    TroopsArr & getTroopsOnPlay ();
    /** method to recognize if two generals are facing each other, return true if do */
    bool isGeneralsFacing   ();
};

