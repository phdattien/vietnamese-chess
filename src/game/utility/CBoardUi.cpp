//
// Created by tiendat on 25.05.22.
//

#include "CBoardUi.h"
#include "iostream"
#include "sstream"
const std::string CBoardUi::ESCAPE = "\u001b[";
const std::string CBoardUi::RESET = "\u001b[0m";
const std::string CBoardUi::BRIGHT = ";1m";
#define WHITE 37
#define RED_BACKGROUND 41
#define BLACK_BACKGROUND 40
#define BLACK 30

void CBoardUi::printHead () {
    int width = 6;
    char c = 'A';
    printf ( "%*c", width, c );
    c++;
    for ( size_t i = 1; i < ROW_SIZE; i++ ) {
        printf ( "%*c", width + 1, c );
        c++;
    }
}

void CBoardUi::printSep () {
    std::stringstream ss;
    ss << ESCAPE << BLACK << BRIGHT << '|' << RESET;

    for ( size_t j = 0; j < ROW_SIZE - 1; j++ ) {
        if ( j == 0 )
            printf ( "%5s%s","", ss.str().c_str() );
        printf ( "%6s%s","", ss.str().c_str() );
    }
}



void CBoardUi::printBoard ( const CBoard &currBoard ) {
    // --------------- printing header  -----------------------
    auto & Board = currBoard.m_Board;
    printHead();
    // --------------- printing header  -----------------------

    printf("\n\n");
    // ------------------ board -----------------------------
    int num = 10;
    const char * space = " ";
    for ( size_t i = 0; i < COL_SIZE; i++ ) {
        // printInside left side
        printf ( "%2d", num--);
        printf ( "%2s", space);

        // printing board
        for ( size_t j = 0; j < ROW_SIZE; j++ ) {
            if ( Board[i][j] ) {
                std::cout << ESCAPE << ( Board[i][j]->getSide() == SIDE::RED ? RED_BACKGROUND : BLACK_BACKGROUND )
                          << BRIGHT  <<  ESCAPE  << WHITE << BRIGHT << " "  << Board[i][j]->getName() << " " << RESET;
            }
            else
                std::cout << " " << ESCAPE << BLACK << BRIGHT << "+" << RESET << " ";
            if ( j != ROW_SIZE - 1 )
                std::cout << ESCAPE << BLACK << BRIGHT << "----" << RESET;
        }
        printf("\n");
        // printing bar
        if ( i != COL_SIZE - 1 ) {
            printSep();
            printf("\n");
            printSep();
        }

        printf("\n");
    }

    // --------------- printing footer  -----------------------
    printHead();
    // --------------- printing footer  -----------------------
    printf("\n");
}




