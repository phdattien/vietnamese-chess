//
// Created by tiendat on 14.05.22.
//

#include "CGame.h"
#include <iostream>
#include <cstdio>
#include <chrono>
#include <thread>
#include "CPlayerHuman.h"
#include "CPlayerAI.h"
#include "UI.h"

using namespace std::chrono_literals;
#define SLEEP_TIME 30ms

CGame::CGame ( CBoard board, PLAYER_TYPE playerOne, PLAYER_TYPE playerTwo ): m_GameBoard (std::move(board)) {
    createPlayer ( m_RedPlayer, playerOne );
    createPlayer ( m_BlackPlayer, playerTwo );

    m_PlayerOnTurn = m_GameBoard.isRedToMove() ? m_RedPlayer : m_BlackPlayer;
}


void CGame::createPlayer ( CGame::Player & player, PLAYER_TYPE type ) {
    if ( type == PLAYER_TYPE::HUMAN ) {
        player = std::make_shared<CPlayerHuman> ();
    } else {
        player = std::make_shared<CPlayerAI> ();
    }
}

void CGame::Play () {
    while ( true ) {
        //getState  -- playerOnTrun ( under attack > checked, takeAction
        UI::printBoard ( m_GameBoard);
        if ( m_GameBoard.isDraw() || m_Draw == DRAW_STATE::ACCEPT ) {
            printf ( "DRAW\n");
            return;
        }

        if ( m_GameBoard.isInCheck () )
            printf ( "Checked!\n");

        if ( ! m_PlayerOnTurn->TakeAction ( m_GameBoard, m_Draw ) ) {
            printResult ();
            break;
        }
//        std::cout << m_Move.value() << std::endl;
//        m_GameBoard.MakeMove (m_Move.value() );
        changePlayer ();
        std::this_thread::sleep_for(SLEEP_TIME);
    }
}

void CGame::printResult () const {
    printf ( "You LOST %s\n", m_GameBoard.isRedToMove() ? "RED" : "BLACK");

}

void CGame::changePlayer () {
    m_PlayerOnTurn = m_GameBoard.isRedToMove() ? m_RedPlayer : m_BlackPlayer;
}

DRAW_STATE CGame::GetDrawState () const {
    return m_Draw;
}

void CGame::SetDrawState ( DRAW_STATE newState ) {
    m_Draw = newState;
}
