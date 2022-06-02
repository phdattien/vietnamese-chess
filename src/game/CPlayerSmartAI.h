//
// Created by tiendat on 01.06.22.
//
#include "CPlayer.h"
#include "CSearch.h"

class CPlayerSmartAI : public CPlayer {
public:
    CPlayerSmartAI () = default;
    bool TakeAction ( CBoard &board, GAME_STATE &gameState ) override;
private:
    static const int SEARCH_DEPTH = 3;
};

