//
// Created by tiendat on 09.05.22.
// inspired by this video
// https://www.youtube.com/watch?v=Asz5yHz8KiA
#include "game/CApplication.h"
#include "game/CBoard.h"
#include "game/UI.h"
#include "game/Perft.h"
#include "iostream"


const std::string map1 = "rchghcr/p1ppp1p/7/7/P1PPP1P/RCHGHCR r";
//const std::string map1 = "3g3/7/7/7/7/2G4 r";

void testBoard ( const std::string & map, size_t depth ) {
    CBoard b ( map );
    Perft perf (b);
    std::cout << map << std::endl;
    for ( size_t i = 1; i <= depth; i++ ) {
        std::cout <<  "depth: " << i << " number of movement:  " <<std::endl;
        int sum = 0;
        perf.movesTest (i, sum);
        std::cout << sum << std::endl;
    }
}

int main () {
//    CBoard b ("1chgh1r/1pppp1p/4c2/7/3G2r/7 r");
//    UI::printBoard (b);
//    b.printAttackedMap();



//    CBoard b ( map1 );
//    testBoard (map1, 5);
//    testBoard (map2, 3);
//    testBoard (map3, 3);
    CApplication app;
    app.Run();
}