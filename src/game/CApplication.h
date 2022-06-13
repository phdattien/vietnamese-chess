//
// Created by tiendat on 26.05.22.
//

#pragma once
#include "CGame.h"
#include "PLAYER_TYPE.h"

// default starting position
const std::string START_POS = "rchghcr/p1ppp1p/7/7/P1PPP1P/RCHGHCR r";


class CApplication {
public:
    using Player = std::shared_ptr<CPlayer>;
    /**
     * Application main Loop, userMenu
     */
    void Run ();
private:
    Player m_Player1;
    Player m_Player2;
    std::string m_BoardPosition = START_POS;
    bool quit = false;
    void makeAction();
    bool newGame ();
    void createPlayer ( Player & player, char type );
    void loadGame ();
    void setDefaultBoard();
    bool choosePlayerPrompt ( Player & player );
};

