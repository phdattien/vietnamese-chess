//
// Created by tiendat on 09.05.22.
//

#include "src/game/CBoard.h"
#include <cstdio>

CBoard::CBoard (  std::vector<std::unique_ptr<CTroop>> &troops ) {
    for ( auto & troop : troops ) {
        m_Board[troop->getCoord().m_Colum][troop->getCoord().m_Row] = move ( troop ) ;
    }
}

bool CBoard::isLegalMove ( const std::unique_ptr<CTroop> &troopOnPos, const CCoord &dest ) const {
    // if destination is in set of a troops all possible moves thatn true
    return troopOnPos->getPossibleMoves ( m_Board ).count (dest);
}

void CBoard::print () const {
    char c = 'A';
//    printf ( " " );
    for ( size_t i = 0; i < 8; i++ ) {
        printf ( "%6c", c );
        c++;
    }

    char h = ' ';
    const char *s = "+-----";
    int num = 8;

    printf("\n");

    for ( size_t i = 0; i < 8; i++ ) {
        printf ( "  ");
        for ( size_t j = 0; j < 8; j++ ) {
            printf ( "%s", s );
        }
        printf ( "+\n");

        printf ( "%d", num );
        num--;
        for ( size_t j = 0; j < 8; j++ ) {
            if( m_Board[i][j] )
                printf ( "%5s ", m_Board[i][j]->getName().c_str() ); // TODO printing pieces
            else {
                printf ( "%5c ", h );
            }
        }
        printf ( "\n");
    }

    printf ( "  ");
    for ( size_t j = 0; j < 8; j++ ) {
        printf ( "%s", s );
    }
}


const std::unique_ptr<CTroop> &CBoard::findKing () const {
    int kingCol;
    int kingRow;
    for (auto & i : m_Board) {
        for (auto & j : i) {
            if ( j->getName() == "K") { // find da black general
                return j;
            }
        }
    }
    return nullptr;
}

bool CBoard::isGeneralsFace ( ) {
    auto & King = findKing();
    int i = King->getCoord().m_Colum + 1;
    for ( ; i < COL_SIZE; i++ ) {
        auto & newCord =  m_Board[i][King->getCoord().m_Row];
        if (  newCord && newCord->getName() != "K" )
            return false;
    }
    return true;
}
