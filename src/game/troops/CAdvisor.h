#pragma once
#include "CTroop.h"


class CAdvisor : public CTroop {
public:
    CAdvisor ( SIDE side, const CCoord &coord );

    std::set<CCoord> getPossibleMoves ( const std::shared_ptr<CTroop> currBoard[10][9] ) const override;

    char getName () const override;

private:
    char m_Name = 'A';
    bool isInsideAdvisorMovements ( const CCoord& newCoord ) const;
};


