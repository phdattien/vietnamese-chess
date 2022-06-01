//
// Created by tiendat on 01.06.22.
//

#include "Evaluation.h"
#include <map>


std::map<char, int> Evaluation::SCORE {
        { GENERAL, GENERAL_VALUE},
        { ADVISOR, ADVISOR_VALUE},
        { CANNON, CANNON_VALUE},
        { CHARIOT, CHARIOT_VALUE},
        { HORSE, HORSE_VALUE},
        { PAWN, PAWN_VALUE},
        { ELEPHANT, ELEPHANT_VALUE}
};


// very simple/ score is evaluated for the plyer on the move - if positive -> good
double Evaluation::Evaluate ( const CBoard &board ) const {
    int redMaterialScore = countMaterial ( board.getRedTroops() );
    int blackMaterialScore = countMaterial ( board.getBlackTroops() );

    int eval = redMaterialScore - blackMaterialScore;
    int sideToMove = board.isRedToMove() ? 1 : -1;
    return eval * sideToMove;
}

int Evaluation::countMaterial ( const Evaluation::TroopsArr &troops ) const {
    int material = 0;
    for ( const auto & troop : troops ) {
        material += SCORE[troop->getName()];
    }
    return  material;
}
