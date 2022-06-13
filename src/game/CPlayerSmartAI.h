//
// Created by tiendat on 01.06.22.
//
#include "CPlayer.h"
#include "CSearch.h"

/**
 * Smart Player AI choose based on a Search using minmax algorithm
 * When deciding a draw, search for a not disarable outcome
 */
class CPlayerSmartAI : public CPlayer {
public:
    CPlayerSmartAI ( int depth ): m_Depth ( depth ) {};
    bool TakeAction ( CBoard &board, GAME_STATE &gameState ) override;
private:
    int m_Depth;
};

