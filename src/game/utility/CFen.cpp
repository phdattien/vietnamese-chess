//
// Created by tiendat on 24.05.22.
//

#include "CFen.h"
#include <sstream>
#include <memory>
#include "../troops/CAdvisor.h"
#include "../troops/CCannon.h"
#include "../troops/CChariot.h"
#include "../troops/CElephant.h"
#include "../troops/CGeneral.h"
#include "../troops/CHorse.h"
#include "../troops/CSoldier.h"

std::optional<CPositionInf> CFen::loadTroops ( const std::string &fen ) {
    //const std::string startBoard = "rheagaehr/9/1c5c1/s1s1s1s1s/9/9/S1S1S1S1S/1C5C1/9/RHEAGAEHR r";

    CPositionInf inf;
    std::stringstream ss ( fen );
    std::string positions, colour;

    ss >> positions >> colour;

    int col = 0;
    int row = 0;

    CCoord coord{};
    SIDE side;

    for ( auto c : positions ) {
        if ( c == '/') {
            col++;
            row = 0;
        }
        else if  ( isalpha(c) )  {
            side = isupper (c) ? SIDE::BLACK : SIDE::RED;
            coord = CCoord( col, row );
            std::shared_ptr<CTroop> troop = getTroopByType ( c, side, coord );
            if ( ! troop )
                return {};
            inf.troopsOnBoard.push_back (troop);
            row++;
        }
        else if ( isdigit(c) ) {
            row += ( c - '0');
        }
        else
            return {};
    }

    if ( colour != "r" && colour != "b")
        return {};

    inf.isRedOnPlay = ( "r" == colour );
    return inf;
}

std::shared_ptr<CTroop> CFen::getTroopByType ( char name, SIDE side, const CCoord & coord ) {
    switch ( toupper (name) ) {
        case 'A':
            return std::make_shared<CAdvisor>(side, coord);
        case 'C':
            return std::make_shared<CCannon>(side, coord);
        case 'R':
            return std::make_shared<CChariot>(side, coord);
        case 'E':
            return std::make_shared<CElephant>(side, coord);
        case 'G':
            return std::make_shared<CGeneral>(side, coord);
        case 'H':
            return std::make_shared<CHorse>(side, coord);
        case 'S':
            return std::make_shared<CSoldier>(side, coord);
        default:
            return nullptr;
    }

}

std::string CFen::getFen ( const CBoard &currBoard ) {
    return std::string ();
}
