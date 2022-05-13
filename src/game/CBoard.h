#pragma once
#include "src/game/troops/CTroop.h"
#include <vector>
#include <memory>




class CBoard {
public:
    // takes all troops in vector and fill the board
    explicit CBoard ( std::vector<std::unique_ptr<CTroop>> & troops );
    CBoard () = default;
    bool validateMove () const;
    void print () const;

private:
    std::unique_ptr<CTroop> m_Board[10][9];
};

