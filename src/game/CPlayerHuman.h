//
// Created by tiendat on 25.05.22.
//
#pragma once
#include "CPlayer.h"
#include <string>
#include <vector>


class CPlayerHuman : public CPlayer {
public:
    CPlayerHuman () = default;
    bool TakeAction ( CBoard &board, GAME_STATE &gameState ) override;

private:
    bool chooseMove ( CBoard &board ) const;
    void safeGame ( const CBoard &board ) const;
    bool isValidCoord ( const std::string& from, const std::string& to ) const;
    bool validateCommand ( const std::string & command );
    void drawSuggest ( GAME_STATE &drawState);
    void drawDecide ( GAME_STATE &drawState );
    std::vector<Move> m_PossibleMoves;
    bool isEmpty ( CBoard & board );
    std::string  m_Command;
};
