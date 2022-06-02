//
// Created by tiendat on 01.06.22.
//
#pragma once
#include "CBoard.h"
#include <map>
#include "Constants.h"

/**
 *  Class for evaluating current board position, simple heuristic for Search
 */
class CEvaluation {
public:
    using TroopsArr = std::vector<std::shared_ptr<CTroop>>;
    CEvaluation () = default;
    /**
     * Method to evaluate current position,
     * @param board current position
     * @return a position score, evaluate is symetric, meaning positive is good ( easier minmax )
     */
    int Evaluate ( const  CBoard & board ) const;
private:
    /**
     * Method counting a evaluation score by agregating their troops power
     * @param troops all troops of one side
     * @return
     */
    int countMaterial ( const TroopsArr & troops ) const;
    /**
     * Method count evaluation position by counting distance to enemy King
     * @param troops all troops of one side
     * @param enemyGeneralCoord coordinate of other side
     * @return
     */
    int countDistance ( const TroopsArr & troops, const CCoord & enemyGeneralCoord ) const;
    /**
     * Score for every type of troop
     */
    static std::map<char, int> SCORE;
};
