//
// Created by tiendat on 26.05.22.
//

#pragma once
#include "CGameHandler.h"

const std::string START_POS = "rheagaehr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RHEAGAEHR r";


class CApplication {
public:
    void Run ();
private:
    PLAYER_TYPE player1;
    PLAYER_TYPE player2;
    std::string m_BoardPosition = START_POS;
    bool quit = false;
    void makeAction();
    void newGame ( PLAYER_TYPE p1, PLAYER_TYPE p2 );
    void loadGame ();
    void setDefaultBoard();
};


