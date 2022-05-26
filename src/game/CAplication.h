//
// Created by tiendat on 26.05.22.
//

#pragma once
#include "CGameHandler.h"


class CApplication {
public:
    void Run ();
private:
    enum class STATE {
        GAME,
        MENU
    };
    STATE m_GameState = STATE::MENU;
    STATE getGameState () const;
    PLAYER_TYPE player1;
    PLAYER_TYPE player2;
    std::string initGame = "rheagaehr/9/1c5c1/s1s1s1s1s/9/9/S1S1S1S1S/1C5C1/9/RHEAGAEHR r";
    bool quit = false;
    void makeAction();
    void newGame ( PLAYER_TYPE p1, PLAYER_TYPE p2 );
    void loadGame ();
    void setDefaultBoard();

};


