//
// Created by tiendat on 09.05.22.
//

#include "CBoard.h"
#include <cstdio>

CBoard::CBoard (  std::vector<std::unique_ptr<CTroop>> &troops ) {
    for ( auto & troop : troops ) {
        m_Board[troop->getCoord().m_Colum][troop->getCoord().m_Row] = move ( troop ) ;
    }
}

bool CBoard::validateMove () const {
    return false;
}

void CBoard::print () const {
    char c = 'A';
//    printf ( " " );
    for ( size_t i = 0; i < 8; i++ ) {
        printf ( "%6c", c );
        c++;
    }

    char h = 'h';
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
            printf ( "%5c ", h ); // TODO printing pieces
        }
        printf ( "\n");
    }

    printf ( "  ");
    for ( size_t j = 0; j < 8; j++ ) {
        printf ( "%s", s );
    }
}
