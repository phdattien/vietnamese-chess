//
// Created by tiendat on 09.05.22.
//

#include "CBoard.h"
#include <cstdio>
#include <iostream>



CBoard::CBoard (  std::vector<std::shared_ptr<CTroop>> &troops ) {
    for ( auto & troop : troops ) {
        if ( troop->getSide() == SIDE::RED ) {
            if ( troop->getName() == GENERAL )
                m_RedGeneral = troop;
            else
                m_RedTroops.push_back (troop);
        }
        else {
            if ( troop->getName() == GENERAL )
                m_BlackGeneral = troop;
            else
                m_BlackTroops.push_back (troop);
        }

        m_Board[troop->getCoord().m_Colum][troop->getCoord().m_Row] = move ( troop ) ;
    }
}

bool CBoard::isLegalMove ( const std::shared_ptr<CTroop> &troopOnPos, const CCoord &dest ) const {
    // if destination is in set of a troops all possible moves thatn true
    return troopOnPos->getPossibleMoves ( m_Board ).count (dest);
}

void CBoard::print () const {
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
        // print left side
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

const std::shared_ptr<CTroop> &CBoard::findKing () const {
    int kingCol = 0;
    int kingRow = 0;
    for (auto & i : m_Board) {
        for (auto & j : i) {
            if ( j->getName() == "K") { // find da black general
                return j;
            }
        }
    }
    return m_Board[kingRow][kingCol];
}

bool CBoard::isGeneralsFace ( ) {
    auto & King = findKing();
    size_t i = King->getCoord().m_Colum + 1;
    for ( ; i < COL_SIZE; i++ ) {
        auto & newCord =  m_Board[i][King->getCoord().m_Row];
        if (  newCord && newCord->getName() != "K" )
            return false;
    }
    return true;
}

std::shared_ptr<CTroop> &CBoard::getTroopOnCoord ( const CCoord &from ) {
    return m_Board[from.m_Colum][from.m_Row];
}

std::shared_ptr<CTroop> CBoard::getTroopOnCoord ( const CCoord &from ) const {
    return m_Board[from.m_Colum][from.m_Row];
}

void CBoard::Move ( const CCoord &from, const CCoord &to )  {
    auto & troopOnPos =  m_Board[from.m_Colum][from.m_Row];
    troopOnPos->setCoord (to); // set new coordinates
    m_Board[to.m_Colum][to.m_Row] = move ( troopOnPos );

}

