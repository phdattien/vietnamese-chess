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
#include "../troops/CPawn.h"

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
            side = isupper (c) ? SIDE::RED: SIDE::BLACK;
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
        case 'P':
            return std::make_shared<CPawn>( side, coord);
        default:
            return nullptr;
    }

}

std::string CFen::getFen ( const CBoard &currBoard ) {
    std::string fen;
    for ( size_t i = 0; i < COL_SIZE; i++ ) {
        int empty = 0;
        for ( size_t j = 0; j < ROW_SIZE; j++ ) {
            const auto & troop = currBoard.getTroopOnCoord ( CCoord (i, j ) );
            if ( ! troop )  {
                empty++;
            }
            else {
                if ( empty != 0 )
                    fen.push_back ( ( empty + '0') );
                char c = troop->getSide() == SIDE::RED ? toupper (troop->getName()) : tolower (troop->getName());
                fen.push_back (c);
                empty = 0;
            }
        }
        if ( empty != 0 ) // in case whole row is empty
            fen.push_back ( ( empty + '0') );
        fen.push_back ('/');
    }

    // add colour on play

    char sideOnPlay = currBoard.isRedToMove() ? 'r' : 'b';
    fen.push_back (' ');
    fen.push_back (sideOnPlay);
    return fen;
}