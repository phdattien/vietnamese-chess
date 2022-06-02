//
// Created by tiendat on 24.05.22.
//
#pragma once
#include <vector>
#include "CTroop.h"
#include <memory>

class CPositionInf {
public:
    std::vector<std::shared_ptr<CTroop>> troopsOnBoard;
    bool isRedOnPlay;
};


