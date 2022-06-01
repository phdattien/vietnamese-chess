//
// Created by tiendat on 14.05.22.
//

#pragma once
#include "CBoard.h"
#include "CPlayer.h"
#include "Draw.h"

enum class PLAYER_TYPE {
    HUMAN,
    AI
};

class CGame {
public:
    using Player = std::shared_ptr<CPlayer>;
    CGame  ( CBoard board, PLAYER_TYPE playerOne, PLAYER_TYPE playerTwo );
    DRAW_STATE GetDrawState () const;
    void SetDrawState ( DRAW_STATE newState );
    void Play ();

private:
    Player m_RedPlayer;
    Player m_BlackPlayer;
    Player m_PlayerOnTurn;
    CBoard m_GameBoard;
    DRAW_STATE m_Draw = DRAW_STATE::NEUTRAL;
    void changePlayer ();
    void createPlayer ( Player & player, PLAYER_TYPE type );
    void printResult () const;
};

