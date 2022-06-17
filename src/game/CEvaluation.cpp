//
// Created by tiendat on 01.06.22.
//

#include "CEvaluation.h"
#include <map>

std::map<char, int> CEvaluation::SCORE {
        { GENERAL, GENERAL_VALUE},
        { ADVISOR, ADVISOR_VALUE},
        { CANNON, CANNON_VALUE},
        { CHARIOT, CHARIOT_VALUE},
        { HORSE, HORSE_VALUE},
        { PAWN, PAWN_VALUE},
        { ELEPHANT, ELEPHANT_VALUE}
};


// very simple/ score is evaluated for the plyer on the move - if positive -> good
int CEvaluation::Evaluate ( const CBoard &board ) const {
    int redEval = 0;
    int blackEval = 0;
    redEval += countMaterial ( board.getRedTroops() ); //
    blackEval += countMaterial ( board.getBlackTroops() );

    // the closer are troops near  enemy kings the better, -> count by manhattan distance
    redEval += countDistance ( board.getRedTroops(), board.getRedKingCoord() );
    blackEval += countDistance ( board.getBlackTroops(), board.getBlackKingCoord() );

    // counting distance, stroop troops and pawn as close to enemy king

    int eval = redEval - blackEval;
    int sideToMove = board.isRedToMove() ? 1 : -1;
    return eval * sideToMove;
//    return eval;
}

int CEvaluation::countMaterial ( const CEvaluation::TroopsArr &troops ) const {
    int material = 0;
    for ( const auto & troop : troops ) {
        material += SCORE[troop->getName()];
    }
    return  material;
}

int CEvaluation::countDistance ( const CEvaluation::TroopsArr &troops, const CCoord &enemyGeneralCoord ) const {
    int count = 0;
    for ( const auto & troop : troops ) {
        if ( troop->getName() == PAWN || troop->getName() == HORSE ) {
            int distance = ( abs (troop->getCoord().m_Row - enemyGeneralCoord.m_Row ) + abs ( troop->getCoord().m_Colum - enemyGeneralCoord.m_Colum) ) * 10;
            count += ( 400 - distance );

        }
//        if ( SCORE[troop->getName()] < 500 || troop->getName() == GENERAL)
//            continue;
//        count += ( abs (troop->getCoord().m_Row - enemyGeneralCoord.m_Row ) + abs ( troop->getCoord().m_Colum - enemyGeneralCoord.m_Colum) ) * 60;
    }
    return count;
}
