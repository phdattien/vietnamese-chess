#include "src/game/CBoard.h"
#include "Perft.h"
#include <string>
#include <iostream>

const std::string map1 = "rheagaehr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RHEAGAEHR r";
const std::string map2 = "r1ea1a3/4gh3/2h1e4/pHp1p1p1p/4c4/6P2/P1P2R2P/1CcC5/9/2EAGAE2 r";
const std::string map3 = "1ceag4/9/h2a5/2p1p3p/5cp2/2h2H3/6PCP/3AE4/2C6/3A1G1H1 r";

void testBoard ( const std::string & map, int depth ) {
    CBoard b ( map );
    Perft perf (b);
    std::cout << map << std::endl;
    for ( size_t i = 1; i <= depth; i++ ) {
        std::cout <<  "depth: " << i << " number of movement:  " << perf.movesTest (i) << std::endl;
    }
}
int main () {
    testBoard (map1, 3);
    testBoard (map2, 3);
    testBoard (map3, 3);
}
