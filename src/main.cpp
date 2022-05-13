//
// Created by tiendat on 09.05.22.
//
#include "game/troops/CCoord.h"
#include "game/troops/CBoard.h"
#include "game/troops/CTroop.h"
#include "game/troops/CGeneral.h"
#include "game/troops/CRook.h"
#include <iostream>
#include <memory>




int main () {
    
    std::vector<std::unique_ptr<CTroop>> pieces;
    /* pieces . push_back ( std::make_unique<CGeneral>("K1", SIDE::BLACK, CCoord(0,0) ) ); */
    /* pieces . push_back ( std::make_unique<CGeneral>("K2", SIDE::BLACK, CCoord(0,1) ) ); */
    /* pieces . push_back ( std::make_unique<CGeneral>("K3", SIDE::BLACK, CCoord(0,2) ) ); */
    /* pieces . push_back ( std::make_unique<CGeneral>("K4", SIDE::BLACK, CCoord(0,4) ) ); */
    /* pieces . push_back ( std::make_unique<CGeneral>("K5", SIDE::BLACK, CCoord(0,5) ) ); */

    pieces . push_back ( std::make_unique<CGeneral>( "R1", SIDE::WHITE, CCoord( "A2") ) );
    pieces . push_back ( std::make_unique<CRook>("R2", SIDE::WHITE, CCoord("B2") ) );
    pieces . push_back ( std::make_unique<CRook>("R3", SIDE::WHITE, CCoord("C2") ) );
    pieces . push_back ( std::make_unique<CRook>("R4", SIDE::WHITE, CCoord("D2") ) );


    CBoard b (pieces);
    b.print();
}

