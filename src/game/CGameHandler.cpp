//
// Created by tiendat on 14.05.22.
//

#include "CGameHandler.h"
#include <iostream>
#include <cstdio>
#include <chrono>
#include <thread>
#include "players/CPlayerHuman.h"
#include "players/CPlayerAI.h"
#include "utility/UI.h"

using namespace std::chrono_literals;
#define SLEEP_TIME 50ms

CGameHandler::CGameHandler ( CBoard board, PLAYER_TYPE playerOne, PLAYER_TYPE playerTwo ): m_GameBoard (std::move(board)) {
    createPlayer ( m_RedPlayer, playerOne );
    createPlayer ( m_BlackPlayer, playerTwo );

    m_PlayerOnTurn = m_GameBoard.isRedToMove() ? m_RedPlayer : m_BlackPlayer;
}


void CGameHandler::createPlayer ( CGameHandler::Player & player, PLAYER_TYPE type ) {
    if ( type == PLAYER_TYPE::HUMAN ) {
        player = std::make_shared<CPlayerHuman> ();
    } else {
        player = std::make_shared<CPlayerAI> ();
    }
}

void CGameHandler::Play () {
    while ( true ) {
        //getState  -- playerOnTrun ( under attack > checked, takeAction
        UI::printBoard ( m_GameBoard);
        if ( m_GameBoard.isDraw() ) {
            printf ( "DRAW\n");
            return;
        }

        if ( m_GameBoard.isInCheck () )
            printf ( "Checked!\n");

        auto move = m_PlayerOnTurn->TakeAction ( m_GameBoard ); // takeAction -->  v
        if ( ! move ) {
            printResult ();
            break;
        }
        std::cout << move.value() << std::endl;
        m_GameBoard.MakeMove (move.value() );
        changePlayer ();
        std::this_thread::sleep_for(SLEEP_TIME);
    }
}

void CGameHandler::printResult () const {
    printf ( "You LOST %s\n", m_GameBoard.isRedToMove() ? "RED" : "BLACK");

}

void CGameHandler::changePlayer () {
    m_PlayerOnTurn = m_GameBoard.isRedToMove() ? m_RedPlayer : m_BlackPlayer;
}
