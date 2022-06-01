//
// Created by tiendat on 25.05.22.
//
#pragma once
#include "CPlayer.h"

class CPlayerHuman : public CPlayer {
public:
    CPlayerHuman () = default;
    std::optional<Move> TakeAction ( CBoard &board ) override;

private:
    bool chooseMove ( CBoard &board, Move &move ) const;
    void safeGame ( const CBoard &board ) const;
    bool isValidCoord ( const std::string& from, const std::string& to ) const;
    bool validateCommand ( const std::string & command );
};
