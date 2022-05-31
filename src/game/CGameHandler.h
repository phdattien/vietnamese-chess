//
// Created by tiendat on 14.05.22.
//

#pragma once
#include "CBoard.h"
#include "players/CPlayer.h"

enum class PLAYER_TYPE {
    HUMAN,
    AI
};

class CGameHandler {
public:
    using Player = std::shared_ptr<CPlayer>;
    CGameHandler  ( CBoard board, PLAYER_TYPE playerOne, PLAYER_TYPE playerTwo );
    void Play ();

private:
    Player m_RedPlayer;
    Player m_BlackPlayer;
    Player m_PlayerOnTurn;
    CBoard m_GameBoard;
    void changePlayer ();
    void createPlayer ( Player & player, PLAYER_TYPE type );
    void printResult () const;
};

