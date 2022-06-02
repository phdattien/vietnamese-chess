//
// Created by tiendat on 14.05.22.
//

#pragma once
#include "CBoard.h"
#include "CPlayer.h"
#include "Draw.h"

enum class PLAYER_TYPE {
    HUMAN,
    RANDOM_AI,
    SMART_AI
};

class CGame {
public:
    using Player = std::shared_ptr<CPlayer>;
    CGame  ( CBoard board, PLAYER_TYPE playerOne, PLAYER_TYPE playerTwo );
    GAME_STATE GetDrawState () const;
    void SetDrawState ( GAME_STATE newState );
    void Play ();

private:
    Player m_RedPlayer;
    Player m_BlackPlayer;
    Player m_PlayerOnTurn;
    CBoard m_GameBoard;
    GAME_STATE m_STATE = GAME_STATE::NEUTRAL;
    void changePlayer ();
    void createPlayer ( Player & player, PLAYER_TYPE type );
    void printResult () const;
};

