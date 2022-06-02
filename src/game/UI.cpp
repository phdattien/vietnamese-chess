//
// Created by tiendat on 25.05.22.
//

#include "UI.h"
#include "iostream"
#include "sstream"
const std::string UI::ESCAPE = "\u001b[";
const std::string UI::RESET = "\u001b[0m";
const std::string UI::BRIGHT = ";1m";
#define WHITE 37
#define RED_BACKGROUND 41
#define BLACK_BACKGROUND 40
#define BLACK 30

void UI::printHead () {
    int width = 6;
    char c = 'A';
    printf ( "%*c", width, c );
    c++;
    for ( size_t i = 1; i < ROW_SIZE; i++ ) {
        printf ( "%*c", width + 1, c );
        c++;
    }
}

void UI::printSep () {
    std::stringstream ss;
    ss << ESCAPE << BLACK << BRIGHT << '|' << RESET;

    for ( size_t j = 0; j < ROW_SIZE - 1; j++ ) {
        if ( j == 0 )
            printf ( "%5s%s","", ss.str().c_str() );
        printf ( "%6s%s","", ss.str().c_str() );
    }
}



void UI::printBoard ( const CBoard &currBoard ) {
    std::cout << "\x1b[1J" << "\x1b[H"; //-> clear screan
    printf ( "%s TURN\n", currBoard.isRedToMove()  ? "RED" : "BLACK" ); // header
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
    printf ( "press: (h)elp | (s)save <file> | (q)uit | (m)m_Move | (p)rint | (d)raw | (q)uit\n");
}

void UI::printHelpMenu () {
    printf ( "=========== GAME HELP MENU ========================\n");
    printf ( "(s)save\n");
    printf ( "save game state to file\n");
    printf ( "(m)ove \n");
    printf ( "m_Move Troop from current position to destination:  \n");
    printf ( "(q)uit\n");
    printf ( "quit chess game and go back to user menu\n");
    printf ( "(p)rint\n");
    printf ( "print a current board again\n");
    printf ( "(d)draw\n");
    printf ( "suggest a draw for the other player\n");
    printf ( "(g)give up\n");
    printf ( "GIVING UP, ending the game\n");
    printf ( "=========== HELP MENU ========================\n");
}

void UI::printUserMenu () {
    printf ("============== VIETNAMESE CHESS =====================\n");
    printf ( "(1)PVP\n");
    printf ( "(2)PVCo\n");
    printf ( "(3)CoVSmarterCo\n");
    printf ( "(l)load game\n");
    printf ( "(q)uit\n");
    printf ("============== VIETNAMESE CHESS =====================\n");
}




