//
// Created by tiendat on 26.05.22.
//

#include <cctype>
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
        try {
            makeAction();
            if ( quit )
                break;
            // new Board
            CBoard b ( m_BoardPosition );
            CGame game ( b, m_Player1, m_Player2 );
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
        UI::printUserMenu();
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
            case 'n':
                if ( ! newGame () ) 
                    break;
                return;
            case 'l':
                loadGame();
                return;
            case 'q':
                std::cout << "Good bye have a nice day";
                quit = true;
                return;
            default:
                printf ( "Wrong m_Command, try again\n" );
        }
    }
}

bool CApplication::choosePlayerPrompt ( CApplication::Player & player ) {
    char command;
    printf ( "player: " );
    std::cin >> command;
    if ( std::cin.eof() )
        throw std::ios::failure ("");
    if ( command != 'n' && command != 'r' && command != 's' )  {
        printf ( "Wrong m_Command, try again\n" );
        return false;
    }

    createPlayer ( player, tolower ( command ) );
    return true;
}

// creating a newGame with types of players
bool CApplication::newGame () {
        UI::printChoosePlayer();
    if ( ! choosePlayerPrompt ( m_Player1 ) ) {
        return false;
    }
    if ( ! choosePlayerPrompt ( m_Player2 ) ) {
        return false;
    }
    /* createPlayer (player2, p2); */
    return true;
}

void CApplication::createPlayer ( CApplication::Player & player, char type ) {
    if ( type == 'n' )
        player = std::make_shared<CPlayerHuman> ();

    if ( type == 'r' )
        player = std::make_shared<CPlayerRandomAI>();

    if ( type == 's' ) {
        int n;
        printf ( "how smart? input number: ");
        std::cin >> n;
        player = std::make_shared<CPlayerSmartAI>(n);
    }
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
