//
// Created by tiendat on 26.05.22.
//

#include <iostream>
#include "CAplication.h"
#include "utility/CBoardUi.h"
#include "fstream"
#include "CGameHandler.h"
#include "CBoard.h"
#include "CQuitException.h"

void CApplication::Run () {
    for ( ;; ) {
        CBoardUi::printUserMenu();
        makeAction();
        if ( quit )
            break;
        try {
            CBoard b ( initGame );
            CGameHandler game ( b, player1, player2 );
            game.Play();
            setDefaultBoard();
        } catch ( std::invalid_argument & e ) {
            std::cout << e.what() << std::endl;
        } catch ( CQuitException & e ) {
            std::cout << e.what() << std::endl;
        }
    }
}

CApplication::STATE CApplication::getGameState () const {
    return m_GameState;
}

void CApplication::makeAction () {
    while ( true ) {
        std::string  command;
        printf ( ">>> ");
        std::cin >> command;
        if ( command.size() > 2 ) {
            printf ("Wrong command, try again\n");
            continue;
        }
        switch ( tolower (command [0]) ) {
            case '1':
                newGame ( PLAYER_TYPE::HUMAN, PLAYER_TYPE::HUMAN);
                return;
            case '2':
                newGame ( PLAYER_TYPE::HUMAN, PLAYER_TYPE::AI);
                return;
            case '3':
                newGame ( PLAYER_TYPE::AI, PLAYER_TYPE::AI);
                return;
            case 'l':
                loadGame();
                break;
            case 'q':
                std::cout << "Good bye have a nice day";
                quit = true;
                return;
            default:
                printf ( "Wrong command, try again\n" );
        }
    }
}

void CApplication::newGame ( PLAYER_TYPE p1, PLAYER_TYPE p2 ) {
    player1 = p1;
    player2 = p2;
}

void CApplication::loadGame () {
    std::string ifName;
    printf ( "fileName: ");
    std::cin >> ifName;
    std::ifstream ifs (ifName);
    if ( ! ifs ) {
        printf ("Bad File\n");
        return;
    }

    std::getline ( ifs, initGame );
    std::cout << initGame << std::endl;
    printf ("Choose game 1 - 3\n");
}

void CApplication::setDefaultBoard () {
    initGame = "rheagaehr/9/1c5c1/s1s1s1s1s/9/9/S1S1S1S1S/1C5C1/9/RHEAGAEHR r";
}
