#include "gol/Grid.hpp"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

static void printGrid(const gol::Grid& g) {
    for (int y=0; y<g.height(); ++y) {
        for (int x=0; x<g.width(); ++x) {
            std::cout << (g.getCell(x,y) ? "O " : ". ");
        }
        std::cout << '\n';
    }
}

int main() {
    gol::Grid grid(12, 12, true);

    // Seed
    grid.setCell(5,5,true);
    grid.setCell(6,5,true);
    grid.setCell(7,6,true);
    grid.setCell(6,6,true);
    grid.setCell(6,4,true);

    std::cout << "Gen " << 0 << "\n";
    printGrid(grid);
    for (int gen=1; gen<=15; ++gen) {
        std::cout << "Gen " << gen << "\n";
        printGrid(grid);
        grid.step(); // B3/S23
        std::this_thread::sleep_for(600ms);
        // std::cout << "\x1B[2J\x1B[H"; // clear screen (ANSI)
    }
    return 0;
}
