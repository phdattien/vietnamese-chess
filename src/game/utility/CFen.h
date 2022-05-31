//
// Created by tiendat on 24.05.22.
//
#pragma once
#include <string>
#include <vector>
#include "../CBoard.h"
#include "CPositionInf.h"
#include <optional>

class CFen {
public:
    CFen() = default;
    static std::optional<CPositionInf> loadTroops ( const std::string &fen );
    static std::string getFen ( const CBoard & currBoard );

private:
    static std::shared_ptr<CTroop> getTroopByType ( char name, SIDE side, const CCoord & coord );
};


