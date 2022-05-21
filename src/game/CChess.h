//
// Created by tiendat on 14.05.22.
//

#pragma once
#include "CBoard.h"
#include <tuple>

class CChess {
public:
    CChess ( CBoard board);
    // main chess loop
    virtual void Play() = 0;
    void PrintGameState() const;
    void makeNextTurn( const std::string & movement);
    void AlternateTurn ();
    bool IsGameOver();
    void doCommand ();
    void printHelpMenu () const;
    bool safeGame ( std::string command );
    bool parseMovement ( const std::string & movement, CCoord & first, CCoord & second ) const;
    bool validatePlayerMovement ( const CCoord & from, const CCoord & to );

protected:

    CBoard m_GameBoard;
    SIDE m_PlayerTurn;
};

