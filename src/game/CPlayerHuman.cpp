//
// Created by tiendat on 25.05.22.
//

#include <regex>
#include <fstream>
#include <algorithm>
#include "CPlayerHuman.h"
#include "iostream"
#include "UI.h"
#include "CFen.h"
#include "CQuitException.h"
#include "Move.h"

bool CPlayerHuman::TakeAction ( CBoard &board, DRAW_STATE &drawState ) {
    if ( isEmpty ( board ) )
        return false;
    if ( drawState == DRAW_STATE::SUGGEST ) {
        drawDecide ( drawState );
        board.ChangeSide();
        return true;
    }
    while (true) {
        printf ( ">>> ");
        std::cin >> m_Command;
        if ( ! validateCommand ( m_Command) )
            continue;
            switch ( tolower ( m_Command [0]) ) {
                case 'd': // draw
                    drawSuggest (drawState);
                    board.ChangeSide();
                    return true;
                case 'q': // quit
                    std::cout << "Good bye have a nice day";
                    throw CQuitException();
                case 'h': // help
                    UI::printHelpMenu();
                    break;
                case 'm': // m_Move
                    if ( ! chooseMove ( board ) ) {
                        printf ( "Invalid Move\n");
                        break;
                    }
                    return true;
                case 's': // save
                    safeGame ( board );
                    break;
                case 'p': // save
                    UI::printBoard( board);
                    break;
                default:
                    printf ( "Wrong m_Command, try again\n" );
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

bool CPlayerHuman::chooseMove ( CBoard &board ) const {
    std::string from;
    std::string to;

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
    if ( std::find(m_PossibleMoves.begin(), m_PossibleMoves.end(), nextMove) == m_PossibleMoves.end() ) {
        return false;
    }

    board.MakeMove (nextMove);
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


bool CPlayerHuman::isEmpty ( CBoard &board ) {
    m_PossibleMoves = board.generateMoves();
    return m_PossibleMoves.empty();
}

void CPlayerHuman::drawDecide ( DRAW_STATE &drawState ) {
    while ( true ) {
        std::cout << "Do you wanna draw? (y)/(n)\n";
        std::cin >> m_Command;
        if ( std::cin.eof() )
            throw std::ios::failure ("");
        if ( m_Command != "y" && m_Command != "n" ) {
            std::cout << "Wrong!\n";
            continue;
        }
        drawState = m_Command == "y" ? DRAW_STATE::ACCEPT : DRAW_STATE::NEUTRAL;
        return;
    }
}

void CPlayerHuman::drawSuggest ( DRAW_STATE & drawState) {
    drawState = DRAW_STATE::SUGGEST;
}
