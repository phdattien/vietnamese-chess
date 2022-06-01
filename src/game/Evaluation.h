//
// Created by tiendat on 01.06.22.
//
#pragma once
#include "CBoard.h"
#include <map>
#include "Constants.h"


class Evaluation {
public:
    using TroopsArr = std::vector<std::shared_ptr<CTroop>>;
    Evaluation () = default;
    double Evaluate ( const  CBoard & board ) const;
private:
    int countMaterial ( const TroopsArr & troops ) const;
    static std::map<char, int> SCORE;
};
