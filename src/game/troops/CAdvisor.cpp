//
// Created by tiendat on 10.05.22.
//

#include "CAdvisor.h"
#include <vector>
#include <iostream>


std::vector<int> pos_coll { 1,  1, -1, -1 };
std::vector<int> pos_row  { 1, -1,  1, -1 };

const std::set<CCoord> AdvisorCoord
{
    CCoord("D1"),
    CCoord("D3"),
    CCoord("F1"),
    CCoord("F3"),
    CCoord("E2")
};


bool CAdvisor::isInsideAdvisorMovements ( const CCoord &newCoord ) const {
    std::set<CCoord> movements;

    // general on red side all his movements from E2 otherwise from E9
    CCoord start = m_Side == SIDE::RED ? CCoord("E2") : CCoord("E9");

    for ( size_t i = 0; i < 4; i++ ) {
        int newPosI = start.m_Colum + pos_coll[i];
        int newPosJ = start.m_Row + pos_row[i];

        // newCoord is in the one of the possible general moves (8) - all movements in palace
        if ( newCoord == CCoord ( newPosI, newPosJ ) )
            return true;
    }
    return false;
}


std::set<CCoord> CAdvisor::getPossibleMoves ( const std::shared_ptr<CTroop> currBoard[10][9] ) const {

    std::set<CCoord> s_coord;
    //  advisor can only move inside his "palace"
    // generate all possible moves for Advisor
    for ( size_t i = 0; i < 4; i++ ) {
        int newPosI = m_Coord.m_Colum + pos_coll[i];
        int newPosJ = m_Coord.m_Row + pos_row[i];


        CCoord newCoord ( newPosI, newPosJ );

        if ( ! newCoord.isInsideBoard() )
            continue;


        auto & troopOnPos = currBoard[newCoord.m_Colum][newCoord.m_Row];


        // if newCoord is outside of board or there is a troop but, on the same side or it is outside of the palace

        if ( ( troopOnPos && troopOnPos->getSide() == m_Side )
                ||  !  isInsideAdvisorMovements( newCoord ) )
        {
            continue;
        }
//
        s_coord.insert (newCoord );
    }
//    std::cout << "Size: " << s_coord.size() << std::endl;
    return s_coord;
}

const std::string &CAdvisor::getName () const {
    return m_Name;
}

CAdvisor::CAdvisor ( SIDE side, const CCoord &coord ) : CTroop ( side, coord ) {}

