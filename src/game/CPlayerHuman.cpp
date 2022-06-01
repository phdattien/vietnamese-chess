//
// Created by tiendat on 25.05.22.
//

#include <regex>
#include <fstream>
#include "CPlayerHuman.h"
#include "iostream"
#include "src/game/utility/UI.h"
#include "src/game/utility/CFen.h"
#include "CQuitException.h"

std::optional<Move> CPlayerHuman::TakeAction ( CBoard &board ) {
    std::string  command;
    Move move{};
    while (true) {
        printf ( ">>> ");
        std::cin >> command;
        if ( ! validateCommand (command) )
            continue;
            switch ( tolower (command [0]) ) {
                case 'q': // quit
                    std::cout << "Good bye have a nice day";
                    throw CQuitException();
                case 'h': // help
                    UI::printHelpMenu();
                    break;
                case 'm': // move
                    if ( chooseMove ( board, move ) )
                        return move;
                    printf ( "Invalid Move\n");
                    break;
                case 's': // save
                    safeGame ( board );
                    break;
                case 'p': // save
                    UI::printBoard( board);
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
    if ( std::cin.eof() )
        throw std::ios::failure ("");
    std::ofstream ofs ( file, std::ios::out );
    if ( !ofs ) {
        printf ( "Cannot make a file\n");
        return;
    }

    std::string fen = CFen::getFen (board);
    ofs << fen;
    ofs.close();
}

bool CPlayerHuman::chooseMove ( CBoard &board, Move &move ) const {
    std::string from;
    std::string to;
    std::vector<Move> possibleMoves = board.generateMoves();

    if ( possibleMoves.empty() ) {
        move = {};
        return true;
    }

    printf ( "From: ");
    std::cin >> from;
    if ( std::cin.eof() )
        throw std::ios::failure ("");
    printf ( "to: ");
    std::cin >> to;

    if ( std::cin.eof() )
        throw std::ios::failure ("");

    if ( ! isValidCoord ( from, to ) ) {
        return false;
    }
    Move nextMove ((CCoord(from)),CCoord(to));
    if ( std::find(possibleMoves.begin(), possibleMoves.end(), nextMove) == possibleMoves.end() ) {
        return false;
    }

    move = nextMove;
    return true;
}

bool CPlayerHuman::isValidCoord ( const std::string& from, const std::string& to ) const {
    if (  std::regex_match (from, std::regex("[a-iA-I]([1-9]|10)") )
       &&  std::regex_match (to, std::regex("[a-iA-I]([1-9]|10)") ) )
        return true;
    return false;
}

bool CPlayerHuman::validateCommand ( const std::string& command ) {
    if ( command.size() > 1)
        return false;
    if ( std::cin.eof() )
        throw std::ios::failure ("");
    return true;
}
