//
// Created by tiendat on 09.05.22.
//

#include "CBoard.h"
#include <cstdio>
#include <iostream>
#include <algorithm>



CBoard::CBoard (  std::vector<std::shared_ptr<CTroop>> &troops ) {
    for ( auto & troop : troops ) {
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
}

bool CBoard::isLegalMove ( const std::shared_ptr<CTroop> &troopOnPos, const CCoord &dest ) const {
    // if destination is in set of a troops all possible moves thatn true
    return troopOnPos->getPossibleMoves ( m_Board ).count (dest);
}

void CBoard::printBoard () const {
    // --------------- printing header  -----------------------
    char c = 'A';
    for ( size_t i = 0; i < ROW_SIZE; i++ ) {
        printf ( "%5c", c );
        c++;
    }
    // --------------- printing header  -----------------------

    printf("\n\n");
    // ------------------ board -----------------------------
    int num = 10;
    char sep = '|';
    const char * dash = "----";
    const char * space = " ";
    for ( size_t i = 0; i < COL_SIZE; i++ ) {
        // printBoard left side
        printf ( "%2d", num--);
        printf ( "%2s", space);

        // printing board
        for ( size_t j = 0; j < ROW_SIZE; j++ ) {
            if ( m_Board[i][j] )
                printf ( "%s", m_Board[i][j]->getName().c_str() );
            else
                printf ( "+" );
            if ( j != ROW_SIZE - 1 )
                printf ( "%s", dash );
        }

        printf("\n");
        // printing bar
        if ( i != COL_SIZE - 1 )
            for ( size_t j = 0; j < ROW_SIZE; j++ ) {
                printf ( "%5c", sep );
        }
        printf("\n");
    }

    // --------------- printing footer  -----------------------
    c = 'A';
    for ( size_t i = 0; i < ROW_SIZE; i++ ) {
        printf ( "%5c", c );
        c++;
    }
    // --------------- printing footer  -----------------------
    printf("\n");
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

std::vector<Move> CBoard::generatePseudoLegalMoves () {
    std::vector<Move> moves;
    std::vector<std::shared_ptr<CTroop>> troops = getTroopsOnPlay();
    for ( const auto & troop : troops ) {
        addMoves ( troop->getCoord(), troop->getPossibleMoves (m_Board), moves );
    }
    return moves;
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

        std::cout << "General COord: " << generalCoord.m_Colum << " " << generalCoord.m_Row << std::endl;

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




