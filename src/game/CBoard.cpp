//
// Created by tiendat on 09.05.22.
//

#include "CBoard.h"
#include <cstdio>
#include <iostream>
#include <algorithm>
#include "utility/CFen.h"
#include <exception>
#include "utility/CPositionInf.h"



CBoard::CBoard ( const std::string &  fen  ) {
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


bool CBoard::isLegalMove ( const std::shared_ptr<CTroop> &troopOnPos, const CCoord &dest ) const {
    // if destination is in set of a troops all possible moves thatn true
    return troopOnPos->getPossibleMoves ( m_Board ).count (dest);
}

//void CBoard::printInside () const {
//    // --------------- printing header  -----------------------
//    char c = 'A';
//    for ( size_t i = 0; i < ROW_SIZE; i++ ) {
//        printf ( "%5c", c );
//        c++;
//    }
//    // --------------- printing header  -----------------------
//
//    printf("\n\n");
//    // ------------------ board -----------------------------
//    int num = 10;
//    char sep = '|';
//    const char * dash = "----";
//    const char * space = " ";
//    for ( size_t i = 0; i < COL_SIZE; i++ ) {
//        // printInside left side
//        printf ( "%2d", num--);
//        printf ( "%2s", space);
//
//        // printing board
//        for ( size_t j = 0; j < ROW_SIZE; j++ ) {
//            if ( m_Board[i][j] ) {
//               std::cout << "\u001b[" <<
//                printf ( " \"\\u001b[\" << START_COL << \";1mS\\u001b[0m\"    %c", m_Board[i][j]->getName() );
//                "\u001b[" << START_COL << ";1mS\u001b[0m"
//
//            }
//            else
//                printf ( "+" );
//            if ( j != ROW_SIZE - 1 )
//                printf ( "%s", dash );
//        }
//
//        printf("\n");
//        // printing bar
//        if ( i != COL_SIZE - 1 )
//            for ( size_t j = 0; j < ROW_SIZE; j++ ) {
//                printf ( "%5c", sep );
//        }
//        printf("\n");
//    }
//
//    // --------------- printing footer  -----------------------
//    c = 'A';
//    for ( size_t i = 0; i < ROW_SIZE; i++ ) {
//        printf ( "%5c", c );
//        c++;
//    }
//    // --------------- printing footer  -----------------------
//    printf("\n");
//}
//

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

std::shared_ptr<CTroop> &CBoard::getTroopOnCoord ( const CCoord &from ) {
    return m_Board[from.m_Colum][from.m_Row];
}

std::shared_ptr<CTroop> CBoard::getTroopOnCoord ( const CCoord &from ) const {
    return m_Board[from.m_Colum][from.m_Row];
}

//void CBoard::Move ( const CCoord &from, const CCoord &to )  {
//    auto & troopOnPos =  m_Board[from.m_Colum][from.m_Row];
//    troopOnPos->setCoord (to); // set new coordinates
//    m_Board[to.m_Colum][to.m_Row] = move ( troopOnPos );
//
//}

std::vector<std::shared_ptr<CTroop>> &CBoard::getTroopsOnPlay ()  {
    return RedToMove ? m_RedTroops : m_BlackTroops;
}

std::vector<std::shared_ptr<CTroop>> &CBoard::getTroopsOnOpositePlay () {
    return RedToMove ? m_BlackTroops : m_RedTroops;
}

void CBoard::addMoves ( const CCoord & start, const std::set<CCoord>& cords, std::vector<Move>& moves ) {
    for ( const auto & coord : cords ) {
        moves.emplace_back(start, coord);
    }
}

void CBoard::printAttackedMoves () {
    std::vector<Move> moves = generatePseudoLegalMoves();
    for ( const auto [from, to] : moves ) {
        printf ( "from: %d %d to: %d %d\n", from.m_Colum, from.m_Row, to.m_Colum, to.m_Row );
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
    RedToMove = !RedToMove; // after making movements switch sides
    std::vector<std::shared_ptr<CTroop>> &troops = getTroopsOnPlay();
//    std::vector<std::shared_ptr<CTroop>> troops = m_BlackTroops;
    CCoord from = movement.m_From;
    CCoord to = movement.m_To;

    auto & troopOnPos = getTroopOnCoord (from);
    m_PrevCapturedTroop = getTroopOnCoord (to); // can be null
    auto it = std::find(troops.begin(), troops.end(), m_PrevCapturedTroop);

    if ( it != troops.end() ) {
        troops.erase ( it );
    }

    troopOnPos->setCoord (to); // set new coordinates

    // move troop to desired destination
    m_Board[to.m_Colum][to.m_Row] = move ( troopOnPos );
}

// can only used after MakeMove
void CBoard::UnMakeMove ( const Move &movement ) {
    std::vector<std::shared_ptr<CTroop>> troops = getTroopsOnPlay();
    RedToMove = !RedToMove; // after making movements switch sides
    CCoord from = movement.m_From;
    CCoord to = movement.m_To;
    auto & troopOnPos = getTroopOnCoord (to);
//    m_PrevCapturedTroop = getTroopOnCoord (to); // can be null

    troopOnPos->setCoord (from); // set where he came from
    // move troop to desired destination
    m_Board[from.m_Colum][from.m_Row] = move ( troopOnPos );
    m_Board[to.m_Colum][to.m_Row] = m_PrevCapturedTroop;
    troops.push_back (m_PrevCapturedTroop);
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

bool CBoard::isGeneralAttacked ()  {
    std::vector<Move> moves = generatePseudoLegalMovesByColour ( getTroopsOnOpositePlay() );
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




