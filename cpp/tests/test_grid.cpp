#include "gol/Grid.hpp"
#include <cassert>
#include <iostream>

static void test_block() {
    gol::Grid g(6,6,true);
    // 2x2 block at (2,2)
    g.setCell(2,2,true); g.setCell(3,2,true);
    g.setCell(2,3,true); g.setCell(3,3,true);
    // One step should be identical
    g.step();
    assert(g.getCell(2,2)); assert(g.getCell(3,2));
    assert(g.getCell(2,3)); assert(g.getCell(3,3));
}

static void test_blinker() {
    gol::Grid g(7,7,true);
    g.setCell(3,2,true); g.setCell(3,3,true); g.setCell(3,4,true);
    g.step();
    // Should rotate to horizontal at y=3
    assert(g.getCell(2,3)); assert(g.getCell(3,3)); assert(g.getCell(4,3));
    // Step again returns to vertical
    g.step();
    assert(g.getCell(3,2)); assert(g.getCell(3,3)); assert(g.getCell(3,4));
}

int main() {
    test_block();
    test_blinker();
    std::cout<<"All good!";
    return 0;
}
