#pragma once
#include "CTroop.h"


class CAdvisor : public CTroop {
public:
    CAdvisor ( SIDE side, const CCoord &coord );

    std::set<CCoord> getPossibleMoves ( const Board &currBoard ) const override;

    char getName () const override;

    int getValue () const override;

private:
    char m_Name = ADVISOR;
    bool isInsideAdvisorMovements ( const CCoord& newCoord ) const;
    static const std::vector<int> POS_COL;
    static const std::vector<int> POS_ROW;
};


