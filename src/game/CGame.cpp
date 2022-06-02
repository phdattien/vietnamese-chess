//
// Created by tiendat on 14.05.22.
//

#include "CGame.h"
#include <cstdio>
#include <chrono>
#include <thread>
#include <utility>
#include "UI.h"

using namespace std::chrono_literals;
#define SLEEP_TIME 30ms

CGame::CGame ( CBoard board, Player playerOne, Player playerTwo )
        : m_GameBoard (std::move(board)),
          m_RedPlayer (std::move(playerOne)),
          m_BlackPlayer(std::move(playerTwo))
{
    m_PlayerOnTurn = m_GameBoard.isRedToMove() ? m_RedPlayer : m_BlackPlayer;
}

void CGame::Play () {
    while ( true ) {
        UI::printBoard ( m_GameBoard);
        if ( m_GameBoard.isDraw() || m_STATE == GAME_STATE::ACCEPT ) {
            printf ( "DRAW\n");
            return;
        }

        if ( m_GameBoard.isInCheck () )
            printf ( "Checked!\n");

        if ( ! m_PlayerOnTurn->TakeAction ( m_GameBoard, m_STATE ) || m_STATE == GAME_STATE::GIVEUP ) {
            printResult ();
            break;
        }
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
