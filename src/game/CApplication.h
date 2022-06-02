//
// Created by tiendat on 26.05.22.
//

#pragma once
#include "CGame.h"
#include "PLAYER_TYPE.h"

// default starting position
const std::string START_POS = "rheagaehr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RHEAGAEHR r";

class CApplication {
public:
    using Player = std::shared_ptr<CPlayer>;
    /**
     * Application main Loop, userMenu
     */
    void Run ();
private:
    Player player1;
    Player player2;
    std::string m_BoardPosition = START_POS;
    bool quit = false;
    void makeAction();
    void newGame ( PLAYER_TYPE p1, PLAYER_TYPE p2 );
    void createPlayer ( Player & player, PLAYER_TYPE type );
    void loadGame ();
    void setDefaultBoard();
};

