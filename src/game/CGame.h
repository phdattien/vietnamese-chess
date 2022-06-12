//
// Created by tiendat on 14.05.22.
//

#pragma once
#include "CBoard.h"
#include "CPlayer.h"
#include "Draw.h"


class CGame {
public:
    using Player = std::shared_ptr<CPlayer>;
    /**
     * Constructor of a new Game, taking Board position and two types o players, players can be anything
     * @param board position
     * @param playerOne types of player
     * @param playerTwo
     */
    CGame  ( CBoard board, Player playerOne, Player playerTwo );
    /**
     * Main gameLoop
     */
    void Play ();

private:
    CBoard m_GameBoard;
    Player m_RedPlayer;
    Player m_BlackPlayer;
    Player m_PlayerOnTurn;
    GAME_STATE m_STATE = GAME_STATE::NEUTRAL;
    void changePlayer ();
    void printResult () const;
};

