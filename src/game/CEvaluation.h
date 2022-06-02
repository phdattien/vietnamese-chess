//
// Created by tiendat on 01.06.22.
//
#pragma once
#include "CBoard.h"
#include <map>
#include "Constants.h"


class CEvaluation {
public:
    using TroopsArr = std::vector<std::shared_ptr<CTroop>>;
    CEvaluation () = default;
    int Evaluate ( const  CBoard & board ) const;
private:
    int countMaterial ( const TroopsArr & troops ) const;
    int countDistance ( const TroopsArr & troops, const CCoord & enemyKingCoord ) const;
    static std::map<char, int> SCORE;
};
