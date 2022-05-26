//
// Created by tiendat on 25.05.22.
//

#include <regex>
#include <fstream>
#include "CPlayerHuman.h"
#include "iostream"
#include "exception"
#include "../utility/CBoardUi.h"
#include "../utility/CFen.h"
#include "../CQuitException.h"

std::optional<Move> CPlayerHuman::TakeAction ( CBoard &board ) {
    std::string  command;
    while (true) {
        printf ( ">>> ");
        std::cin >> command;
        switch ( tolower (command [0]) ) {
            case 'q': // quit
                std::cout << "Good bye have a nice day";
                throw CQuitException();
            case 'h': // help
                CBoardUi::printHelpMenu();
                break;
            case 'm': // move
                return chooseMove( board ); // move a1 3p
            case 's': // save
                safeGame ( board );
                break;
            case 'p': // save
                CBoardUi::printBoard(board);
                break;
            default:
                printf ( "Wrong command, try again\n" );
        }
    }
}

void CPlayerHuman::safeGame ( const CBoard & board ) const {
    std::string file;
    printf ( "file name: ");
    std::cin >> file;
    std::ofstream ofs ( file, std::ios::out );
    if ( !ofs ) {
        printf ( "Cannot make a file\n");
        return;
    }

    std::string fen = CFen::getFen (board);
    ofs << fen;
    ofs.close();
}

std::optional<Move> CPlayerHuman::chooseMove ( CBoard & board ) const {
    std::string from;
    std::string to;
    std::vector<Move> possibleMoves = board.generateMoves();

    if ( possibleMoves.empty() )
        return {};

    while ( true ) {
        printf ( "From: ");
        std::cin >> from;
        printf ( "to: ");
        std::cin >> to;
        if ( ! isValidCoord ( from, to ) ) {
            printf ("Invalid Coord\n");
            continue;
        }
        Move nextMove ((CCoord(from)),CCoord(to));
        if ( std::find(possibleMoves.begin(), possibleMoves.end(), nextMove) != possibleMoves.end() )
            return nextMove;
        printf ( "Invalid Move\n");
    }
}

bool CPlayerHuman::isValidCoord ( const std::string& from, const std::string& to ) {
    if (  std::regex_match (from, std::regex("[a-iA-I]([1-9]|10)") )
       &&  std::regex_match (to, std::regex("[a-iA-I]([1-9]|10)") ) )
        return true;
    return false;
}




