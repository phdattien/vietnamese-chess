//
// Created by tiendat on 14.05.22.
//

#pragma once
#include "CBoard.h"
#include <tuple>
#include "players/CPlayer.h"

enum class PLAYER_TYPE {
    HUMAN,
    AI
};

enum class GAME_STATE {
    PLAYING,
    DRAW,
    CHECKMATE,
};

class CGameHandler {
public:
    using Player = std::shared_ptr<CPlayer>;
    CGameHandler  ( CBoard board, PLAYER_TYPE playerOne, PLAYER_TYPE playerTwo );
    // main chess loop
    void PrintGameState() const;
    void makeNextTurn( const std::string & movement);
    void AlternateTurn ();
    bool IsGameOver();
    void doCommand ();
    void printHelpMenu () const;
    bool safeGame ( std::string command );
    bool parseMovement ( const std::string & movement, CCoord & first, CCoord & second ) const;
    bool validatePlayerMovement ( const CCoord & from, const CCoord & to );
    void Play ();
    void PrintResult () const;

private:
    Player m_RedPlayer;
    Player m_BlackPlayer;
    Player m_PlayerOnTurn;

    void changePlayer ();

    void CreatePlayer ( Player & player, PLAYER_TYPE type );
    GAME_STATE gameState = GAME_STATE::PLAYING;
    CBoard m_GameBoard;
};

