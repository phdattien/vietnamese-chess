//
// Created by tiendat on 24.05.22.
//
#pragma once
#include <string>
#include <vector>
#include "CBoard.h"
#include "CPositionInf.h"
#include <optional>

/**
 * A helper Class to work with Fen
 */
class CFen {
public:
    CFen() = default;
    /**
     * Static method to parse and control a fen string
     * @param fen specialized string representing troops on board
     * @return null_opt if fen is wrong, CPosition otherwise -> all infromation for Board to be able to be initialized
     */
    static std::optional<CPositionInf> loadTroops ( const std::string &fen );
    /**
     * Method to get a Fen string from our current position
     * @param currBoard
     * @return a fen string format
     */
    static std::string getFen ( const CBoard & currBoard );

private:
    static std::shared_ptr<CTroop> getTroopByType ( char name, SIDE side, const CCoord & coord );
};


