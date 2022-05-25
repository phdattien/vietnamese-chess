//
// Created by tiendat on 24.05.22.
//
#pragma once
#include <string>
#include <vector>
#include "../troops/CTroop.h"
#include "../CBoard.h"
#include "CPositionInf.h"
#include <optional>


const std::string startBoard = "rheagaehr/9/1c5c1/s1s1s1s1s/9/9/S1S1S1S1S/1C5C1/9/RHEAGAEHR r";

class CFen {
public:
    CFen() = default;
    static std::optional<CPositionInf> loadTroops ( const std::string &fen = startBoard );
    static std::string getFen ( const CBoard & currBoard );

private:
    static std::shared_ptr<CTroop> getTroopByType ( char name, SIDE side, const CCoord & coord );

};

struct PositionInformation {
    std::vector<CTroop> troops;
    bool redOnPlay;
};

