//
// Created by tiendat on 26.05.22.
//

#include <iostream>
#include "CApplication.h"
#include "UI.h"
#include "fstream"
#include "CGame.h"
#include "CBoard.h"
#include "CQuitException.h"
#include "CPlayerHuman.h"
#include "CPlayerRandomAI.h"
#include "CPlayerSmartAI.h"

void CApplication::Run () {
    for ( ;; ) {
        UI::printUserMenu();
        try {
            makeAction();
            if ( quit )
                break;
            // new Board
            CBoard b ( m_BoardPosition );
            CGame game ( b, player1, player2 );
            game.Play();
            setDefaultBoard();
        } catch ( std::invalid_argument & e ) {
            std::cout << e.what() << std::endl;
        } catch ( CQuitException & e ) {
            std::cout << e.what() << std::endl;
        } catch  ( std::ios::failure & e ) {
            return;
        }
    }
}

void CApplication::makeAction () {
    while ( true ) {
        std::string  command;
        printf ( ">>> ");
        std::cin >> command;
        if ( std::cin.eof() )
            throw std::ios::failure ("");
        // control of input
        if ( command.size() > 2 ) {
            printf ("Wrong m_Command, try again\n");
            continue;
        }
        switch ( tolower (command [0]) ) {
            case '1':
                newGame ( PLAYER_TYPE::HUMAN, PLAYER_TYPE::HUMAN);
                return;
            case '2':
                newGame ( PLAYER_TYPE::HUMAN, PLAYER_TYPE::SMART_AI);
                return;
            case '3':
                newGame ( PLAYER_TYPE::RANDOM_AI, PLAYER_TYPE::SMART_AI);
                return;
            case 'l':
                loadGame();
                break;
            case 'q':
                std::cout << "Good bye have a nice day";
                quit = true;
                return;
            default:
                printf ( "Wrong m_Command, try again\n" );
        }
    }
}

// creating a newGame with types of players
void CApplication::newGame ( PLAYER_TYPE p1, PLAYER_TYPE p2 ) {
    createPlayer (player1, p1);
    createPlayer (player2, p2);
}

void CApplication::createPlayer ( CApplication::Player & player, PLAYER_TYPE type ) {
    if ( type == PLAYER_TYPE::HUMAN )
        player = std::make_shared<CPlayerHuman> ();

    if ( type == PLAYER_TYPE::RANDOM_AI )
        player = std::make_shared<CPlayerRandomAI>();

    if ( type == PLAYER_TYPE::SMART_AI )
        player = std::make_shared<CPlayerSmartAI>();
}

void CApplication::loadGame () {
    std::string ifName;
    printf ( "fileName: ");
    std::cin >> ifName;
    if ( std::cin.eof() )
        throw std::ios::failure ("");

    std::ifstream ifs (ifName);
    if ( ! ifs ) {
        printf ("Bad File\n");
        return;
    }
    std::getline ( ifs, m_BoardPosition );
    std::cout << m_BoardPosition << std::endl;
    printf ("Choose game 1 - 3\n");
}

void CApplication::setDefaultBoard () {
    m_BoardPosition = START_POS;
}
