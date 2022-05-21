//
// Created by tiendat on 14.05.22.
//

#include "CChess.h"
#include <iostream>
#include <cstdio>
#include <sstream>
#include <regex>

CChess::CChess ( CBoard board ) : m_GameBoard ( std::move (board ) ), m_PlayerTurn ( SIDE::RED ) {}

void CChess::PrintGameState () const {
//    printf ( "%s TURN\n", m_PlayerTurn == SIDE::RED ? "RED" : "WHITE" ); // header
    m_GameBoard.print (); // printing game state
    printf ( "press: (h)elp | (s)save <file> | (q)uit | (m)move <xy> <zw>\n");
}

void CChess::doCommand () {
    std::string command;
    while ( std::getline ( std::cin, command ) ) {
        printf ( "%s TURN's\n", m_PlayerTurn == SIDE::RED ? "RED" : "WHITE" ); // header
        switch ( tolower (command[0])) {
            case 'q': // quit
                std::cout << "Good bye have a nice day";
                throw std::invalid_argument ( "Me quit" );
            case 'h': // help
                printHelpMenu ();
                break;
            case 'm': // move
                makeNextTurn ( command ); // move a1 3p
                break;
            case 's': // save
                safeGame ( command );
                std::cin.get();
                PrintGameState();
                break;
            case 'p': // print gameboard again
                PrintGameState ();
                break;
            default:
                printf ( "Wrong command, try again please\n" );
                break;
        }
    }
}

bool CChess::validatePlayerMovement ( const CCoord &from, const CCoord &to ) {
    if ( ! from.isInsideBoard() || ! to.isInsideBoard() ) {
        printf ( "Coordinates not inside board!\n");
        return false;
    }

    // check if movement is done by right player
    auto & currPiece = m_GameBoard.getTroopOnCoord (from);

    //check if at from position is a troop and the troop is player's side
    if ( ! currPiece || currPiece->getSide() != m_PlayerTurn ) {
        printf ( "Troop is not yours!\n");
        return false;
    }

    if ( ! m_GameBoard.isLegalMove (currPiece, to ) ) {
        printf ( "Not a Legal move!\n");
        return false;
    }
    return true;
}

void CChess::makeNextTurn ( const std::string &movement ) {
    CCoord from{};
    CCoord to{};

    // all theses check probably should be some command class handler
    if ( ! parseMovement ( movement, from, to ) ) {
        printf ( "Bad move format!\n");
        return;
    }

    if ( ! validatePlayerMovement ( from, to ) )
        return;

    // make the move
    // get a troop on to position
    auto toTroop =  m_GameBoard.getTroopOnCoord (to);
    m_GameBoard.Move ( from, to );
    if ( m_GameBoard.isGeneralsFace() )




}


void CChess::printHelpMenu () const {
    printf ( "=========== GAME HELP MENU ========================\n");
    printf ( "(s)save <file>\n");
    printf ( "save game state to <file> if file not included will be saved to default file chess.txt\n");
    printf ( "(m)ove <rc> <rc>\n");
    printf ( "move Troop from current position to destination: r - row (A-I), c - colum (1-10) \n");
    printf ( "(q)uit\n");
    printf ( "quit chess game and go back to user menu\n");
    printf ( "=========== HELP MENU ========================\n");
}

bool CChess::parseMovement ( const std::string &movement, CCoord & first, CCoord & second ) const {
    std::string s;
    std::string fir;
    std::string sec;

    std::istringstream iss (movement);
    if (   ! ( iss >> s >> fir >> sec )
        || ! std::regex_match (fir, std::regex("[a-iA-i][1-9]") )
        || ! std::regex_match (sec, std::regex("[a-iA-i][1-9]") ) )
        return false;

    first = CCoord(first);
    first = CCoord(second);
    return true;
}




