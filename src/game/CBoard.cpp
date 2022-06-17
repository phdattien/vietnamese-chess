//
// Created by tiendat on 09.05.22.
//

#include "CBoard.h"
#include <cstdio>
#include <iostream>
#include <algorithm>
#include "CFen.h"
#include "CPositionInf.h"
#include <exception>
#include "Constants.h"

CBoard::CBoard ( const std::string &  fen  ) : m_Board ( COL_SIZE, std::vector<std::shared_ptr<CTroop>> ( ROW_SIZE,nullptr) ){
    auto inf = CFen::loadTroops (fen); // static method to parse fen string
    if ( ! inf ) {
        throw std::invalid_argument ("Bad Fen");
    }

    // loop for initialazing private atributes
    for ( auto & troop : inf->troopsOnBoard ) {
        if ( troop->getSide() == SIDE::RED ) {
            if ( troop->getName() == GENERAL )
                m_RedGeneral = troop;
            m_RedTroops.push_back (troop);
        }
        else {
            if ( troop->getName() == GENERAL )
                m_BlackGeneral = troop;
            m_BlackTroops.push_back (troop);
        }
        m_Board[troop->getCoord().m_Colum][troop->getCoord().m_Row] = move ( troop ) ;
    }
    RedToMove = inf->isRedOnPlay;
}

bool CBoard::isGeneralsFacing ( ) {
    if ( m_BlackGeneral->getCoord().m_Row != m_RedGeneral->getCoord().m_Row)
        return false;

    for ( int i = m_BlackGeneral->getCoord().m_Colum + 1; i < m_RedGeneral->getCoord().m_Colum; i++ ) {
        auto & troopOnPos =  m_Board[i][m_RedGeneral->getCoord().m_Row];
        if (  troopOnPos ) {
            return false;
        }
    }
    return true;
}

std::shared_ptr<CTroop> &CBoard::getTroopOnCoord ( const CCoord &from )  {
    return m_Board[from.m_Colum][from.m_Row];
}

std::shared_ptr<CTroop> CBoard::getTroopOnCoord ( const CCoord &from ) const {
    return m_Board[from.m_Colum][from.m_Row];
}

std::vector<std::shared_ptr<CTroop>> &CBoard::getTroopsOnPlay ()  {
    return RedToMove ? m_RedTroops : m_BlackTroops;
}

std::vector<std::shared_ptr<CTroop>> &CBoard::getTroopsOnOppositePlay () {
    return RedToMove ? m_BlackTroops : m_RedTroops;
}

void CBoard::addMoves ( const CCoord & start, const std::set<CCoord>& cords, std::vector<Move>& moves ) {
    for ( const auto & coord : cords ) {
        moves.emplace_back(start, coord);
    }
}


void CBoard::printAttackedMap () {
    std::vector<Move> moves = generateMoves();
    std::vector<CCoord> cords;

    cords.reserve(moves.size());
    for ( const auto move : moves ) {
        cords.push_back (move.m_To);
    }

    for ( size_t i = 0; i < COL_SIZE; i++ ) {
        for ( size_t j = 0; j < ROW_SIZE; j++ ) {
            printf (" ");
            if ( std::find(cords.begin(), cords.end(), CCoord(i, j)) != cords.end() )
                printf ( "X");
            else
                printf ( ".");
        }
        printf ( "\n");
    }
}

void CBoard::MakeMove ( const Move &movement, bool searching ) {
    CCoord from = movement.m_From;
    CCoord to = movement.m_To;

    auto capturedTroop = getTroopOnCoord (to);
    m_HistoryCapturedTroops.push (capturedTroop);
    std::vector<std::shared_ptr<CTroop>> &troops = getTroopsOnOppositePlay();
    auto it = std::find(troops.begin(), troops.end(), capturedTroop);

    if ( it != troops.end() ) {
        troops.erase ( it );
    }

    auto & troopOnPos = getTroopOnCoord (from);
    troopOnPos->setCoord (to); // set new coordinates

    // m_Move troop to desired destination
    m_Board[to.m_Colum][to.m_Row] = move ( troopOnPos );
    std::string fen = CFen::getFen (*this);
    currentFen = fen; // update our position;
    if ( ! searching )
        m_RepetitionHistory.emplace_front( fen ); // add this position to top, later to find repettions
    ChangeSide();
}

void CBoard::UnMakeMove ( const Move &movement, bool searching ) {
    if ( m_RepetitionHistory.size() > 0 && ! searching )
        m_RepetitionHistory.pop_front(); // pop, was in search so it doesn't matter
    std::vector<std::shared_ptr<CTroop>> &troops = getTroopsOnPlay();
    ChangeSide();
    CCoord from = movement.m_From;
    CCoord to = movement.m_To;
    auto & troopOnPos = getTroopOnCoord (to);

    troopOnPos->setCoord (from); // set where he came from
    // m_Move troop to desired destination
    m_Board[from.m_Colum][from.m_Row] = move ( troopOnPos );
    auto prevCapturedTroop = m_HistoryCapturedTroops.top();
    m_HistoryCapturedTroops.pop(); //

//    m_Board[to.m_Colum][to.m_Row] = m_PrevCapturedTroop;
    m_Board[to.m_Colum][to.m_Row] = prevCapturedTroop;

    if (  prevCapturedTroop )
        troops.push_back ( prevCapturedTroop);
}

// generate all PseudoLegalMoves and then filter out dangerMoves
const std::vector<Move> &CBoard::generateMoves () {
    possibleMoves.clear();
    std::vector<Move> pseudoLegalMoves = generatePseudoLegalMoves();

    for ( auto & possibleMov : pseudoLegalMoves ) {
        MakeMove (possibleMov);
        std::vector<Move> opponentMoves = generatePseudoLegalMoves();


        CCoord generalCoord = getGeneralOnOppositePlayCoord();
        auto res = std::find_if(opponentMoves.begin(), opponentMoves.end(), [&generalCoord]  (const Move & a ) {
            return a.m_To == generalCoord;
        });

        // if there is any m_Move that will make out King in danger
        if ( res == opponentMoves.end() &&  ! isGeneralsFacing() ) {
            possibleMoves.push_back (possibleMov);
        }
        UnMakeMove (possibleMov);
    }

    return possibleMoves;
}

const CCoord &CBoard::getGeneralOnPlayCoord () const {
    return RedToMove ? m_RedGeneral->getCoord() : m_BlackGeneral->getCoord();
}

const CCoord &CBoard::getGeneralOnOppositePlayCoord () const {
    return RedToMove ? m_BlackGeneral->getCoord() : m_RedGeneral->getCoord();
}

bool CBoard::isRedToMove () const {
    return RedToMove;
}

bool CBoard::isInCheck ()  {
    std::vector<Move> moves = generatePseudoLegalMovesByColour ( getTroopsOnOppositePlay() );
    CCoord generalCoord = getGeneralOnPlayCoord();

    auto res = std::find_if( moves.begin(), moves.end(), [&generalCoord]  (const Move & a ) {
        return a.m_To == generalCoord;
    });

    if ( res == moves.end()) { // meaning our King is not under attacked
        return false;
    }
    return true;
}

std::vector<Move> CBoard::generatePseudoLegalMovesByColour ( const TroopsArr & troops ) {
    std::vector<Move> moves;
    for ( const auto & troop : troops ) {
        addMoves ( troop->getCoord(), troop->getPossibleMoves (m_Board), moves );
    }
    return moves;
}

std::vector<Move> CBoard::generatePseudoLegalMoves () {
    return generatePseudoLegalMovesByColour ( getTroopsOnPlay() );
}

// draw  is detected if are enough troops to be able to make a check
bool CBoard::isDraw () {
    if ( m_RedTroops.size() <= 2 && m_BlackTroops.size() <= 2)
        return true;
    std::vector<char> redTroops;
    std::vector<char> blackTroops;

    for ( const auto& x : m_RedTroops ) {
        redTroops.push_back (x->getName());
    }

    for ( const auto& x : m_BlackTroops ) {
        blackTroops.push_back (x->getName());
    }

    if ( ! canCross (blackTroops) && !canCross (redTroops))
        return true;

    return false;
}

bool CBoard::canCross ( const std::vector<char>& troopNames ) {
    std::vector<char> low { 'S', 'R', 'H'};
    for ( auto c : low ) {
        if ( std::find(troopNames.begin(), troopNames.end(), c) != troopNames.end() )
            return true;
    }
    return false;
}

void CBoard::ChangeSide () {
    RedToMove = !RedToMove; // after making movements switch sides
}

const CBoard::TroopsArr &CBoard::getRedTroops () const {
    return m_RedTroops;
}

const CBoard::TroopsArr &CBoard::getBlackTroops () const {
    return m_BlackTroops;
}

const CCoord &CBoard::getRedKingCoord () const {
    return m_RedGeneral->getCoord();
}

const CCoord &CBoard::getBlackKingCoord () const {
    return m_BlackGeneral->getCoord();
}

bool CBoard::isRepetition () const {
    auto it = std::find(m_RepetitionHistory.begin(), m_RepetitionHistory.end(), currentFen);
    return it != m_RepetitionHistory.end(); // if not in the end meaning already exists -> is repetition;

}

