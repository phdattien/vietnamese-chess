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
#include "troopsNames.h"

CBoard::CBoard ( const std::string &  fen  ) : m_Board ( COL_SIZE, std::vector<std::shared_ptr<CTroop>> ( ROW_SIZE,nullptr) ){
    auto inf = CFen::loadTroops (fen);
    if ( ! inf ) {
        throw std::invalid_argument ("Bad Fen");
    }

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

void CBoard::printAttackedMoves () {
    std::vector<Move> moves = generateMoves();
    for ( const auto move : moves ) {
        std::cout << move << std::endl;
    }
}

void CBoard::printAttackedMap () {
//    std::vector<Move> moves = generatePseudoLegalMoves();
    std::vector<Move> moves = generateMoves();
    std::vector<CCoord> cords;

    cords.reserve(moves.size());
    for ( const auto [from, to] : moves ) {
        cords.push_back (to);
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

void CBoard::MakeMove ( const Move &movement ) {
//    std::vector<std::shared_ptr<CTroop>> troops = m_BlackTroops;
    CCoord from = movement.m_From;
    CCoord to = movement.m_To;

    auto capturedTroop = getTroopOnCoord (to);
    m_HistoryCapturedTroops.push (capturedTroop);
//    m_PrevCapturedTroop = getTroopOnCoord (to); // can be null
    std::vector<std::shared_ptr<CTroop>> &troops = getTroopsOnOppositePlay();
    auto it = std::find(troops.begin(), troops.end(), capturedTroop);

    if ( it != troops.end() ) {
        troops.erase ( it );
    }

    auto & troopOnPos = getTroopOnCoord (from);
    troopOnPos->setCoord (to); // set new coordinates

    // m_Move troop to desired destination
    m_Board[to.m_Colum][to.m_Row] = move ( troopOnPos );
//    RedToMove = !RedToMove; // after making movements switch sides
    ChangeSide();
}

// can only used after MakeMove
void CBoard::UnMakeMove ( const Move &movement ) {
    std::vector<std::shared_ptr<CTroop>> &troops = getTroopsOnPlay();
//    RedToMove = !RedToMove; // after making movements switch sides
    ChangeSide();
    CCoord from = movement.m_From;
    CCoord to = movement.m_To;
    auto & troopOnPos = getTroopOnCoord (to);
//    m_PrevCapturedTroop = getTroopOnCoord (to); // can be null

    troopOnPos->setCoord (from); // set where he came from
    // m_Move troop to desired destination
    m_Board[from.m_Colum][from.m_Row] = move ( troopOnPos );
    auto prevCapturedTroop = m_HistoryCapturedTroops.top();
    m_HistoryCapturedTroops.pop();

//    m_Board[to.m_Colum][to.m_Row] = m_PrevCapturedTroop;
    m_Board[to.m_Colum][to.m_Row] = prevCapturedTroop;

    if (  prevCapturedTroop )
        troops.push_back ( prevCapturedTroop);
}

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

std::vector<Move> CBoard::generatePseudoLegalMovesByColour ( const std::vector<std::shared_ptr<CTroop>>& troops ) {
    std::vector<Move> moves;
    for ( const auto & troop : troops ) {
        addMoves ( troop->getCoord(), troop->getPossibleMoves (m_Board), moves );
    }
    return moves;
}

std::vector<Move> CBoard::generatePseudoLegalMoves () {
    return generatePseudoLegalMovesByColour ( getTroopsOnPlay() );
}

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
