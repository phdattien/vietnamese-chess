//
// Created by tiendat on 25.05.22.
//
#pragma once
#include "CPlayer.h"

class CPlayerHuman : public CPlayer {
public:
    CPlayerHuman () = default;
    std::optional<Move> TakeAction ( CBoard &board ) override;

    static bool isValidCoord ( const std::string& from, const std::string& to ) ;
private:
    Move chosenMove;
    std::optional<Move> chooseMove ( CBoard &board ) const;
    void safeGame ( const CBoard &board ) const;

};
