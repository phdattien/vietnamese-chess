//
// Created by tiendat on 09.05.22.
// inspired by this video
// https://www.youtube.com/watch?v=Asz5yHz8KiA

//#include "game/troops/CCoord.h"
//#include "game/troops/CTroop.h"
//#include "game/troops/CAdvisor.h"
//#include "game/troops/CGeneral.h"
//#include "game/troops/CElephant.h"
//#include "game/troops/CHorse.h"
//#include "game/troops/CChariot.h"
//#include "game/troops/CSoldier.h"
//#include "game/troops/CCannon.h"
//#include "game/CBoard.h"
//#include "game/players/CPlayer.h"
//#include "game/players/CPlayerAI.h"
//#include <memory>
//#include <vector>
//#include "game/players/CPlayerHuman.h"
//#include <iostream>
//#include "game/utility/CPositionInf.h"
//#include "game/CGameHandler.h"
//#include "game/utility/CBoardUi.h"
//#include "game/utility/CFen.h"

#include "game/CAplication.h"
#include "game/CBoard.h"

int main () {
//    std::vector<std::shared_ptr<CTroop>> pieces;
//    pieces . push_back ( std::make_shared<CAdvisor>(SIDE::RED, CCoord("E2") ) );
//    pieces . push_back ( std::make_shared<CGeneral>(SIDE::RED, CCoord("E1") ) );
//    pieces . push_back ( std::make_shared<CAdvisor>(SIDE::RED, CCoord("F1")nd ) );
//    pieces . push_back ( std::make_shared<CElephant>(SIDE::RED, CCoord("G1") ) );
//    pieces . push_back ( std::make_shared<CHorse>(SIDE::RED, CCoord("H1") ) );
//    pieces . push_back ( std::make_shared<CChariot>(SIDE::RED, CCoord("I1") ) );
//    pieces . push_back ( std::make_shared<CSoldier>(SIDE::RED, CCoord("A4") ) );
//    pieces . push_back ( std::make_shared<CSoldier>(SIDE::RED, CCoord("C4") ) );
//    pieces . push_back ( std::make_shared<CSoldier>(SIDE::RED, CCoord("C4") ) );
//    pieces . push_back ( std::make_shared<CCannon>(SIDE::RED, CCoord("E5") ) );

//    pieces . push_back ( std::make_shared<CChariot>(SIDE::BLACK, CCoord("E7") ) );
//    pieces . push_back ( std::make_shared<CElephant>(SIDE::BLACK, CCoord("F5") ) );
//    pieces . push_back ( std::make_shared<CGeneral>(SIDE::BLACK, CCoord("D10") ) );
//    pieces . push_back ( std::make_shared<CCannon>(SIDE::BLACK, CCoord("F7") ) );

//    CBoard b (pieces);

//    std::shared_ptr<CPlayer> ai = std::make_shared<CPlayerAI> ();
//    for ( size_t i = 0; i < 10; i++ ) {
//        b.printInside ();
//        b.printAttackedMap();
//        Move move = ai->TakeAction ( b );
//        b.MakeMove (move);
//        std::cout << move << std::endl;
//    }
//    CBoard b("rheagaehr/9/1c5c1/s1s1s1s1s/9/9/S1S1S1S1S/1C5C1/9/RHEAGAEHR b");
//    CGameHandler game ( b, PLAYER_TYPE::AI, PLAYER_TYPE::AI );
//    game.Play();
    CApplication app;
    app.Run();

    return 0;


}