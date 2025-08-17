#include "gol/Grid.hpp"
#include <iostream>
#include <thread>
// #include <chrono>
#include <string>
#include <cstring>
using namespace std;

static void printGrid(const gol::Grid& g) {
    for (int y=0; y<g.height(); ++y) {
        for (int x=0; x<g.width(); ++x) {
            cout << (g.getCell(x,y) ? "O " : ". ");
        }
        cout << '\n';
    }
}

int main(int argc, char* argv[]) {
    int gridWidth, gridHeight;
    bool wrapEdges;
    cout<<"start"<<endl;
    for(int i=1;i<argc;i++){
        // Need to add parser (handle cases like 0,1,TRUE,FALSE etc,etc)
        cout<<argv[i]<<endl;
        if(strcmp(argv[i], "--width") == 0)
            gridWidth=atoi(argv[++i]);
        else if (strcmp(argv[i], "--height") == 0)
            gridHeight=atoi(argv[++i]);
        else if (strcmp(argv[i], "--wrap") == 0)
            wrapEdges=strcmp(argv[++i], "false");//incorrect logic (fails for true)
        else{
            cout<<"Unknown Argument: "<<argv[i++]<<endl;
        }
    }

    // cout<<gridWidth<<endl;
    // cout<<gridHeight<<endl;
    // cout<<wrapEdges<<endl;
    gol::Grid grid(gridWidth, gridHeight, wrapEdges);

    // Seed
    grid.setCell(12,12,true);
    grid.setCell(13,12,true);
    grid.setCell(14,13,true);
    grid.setCell(13,13,true);
    grid.setCell(13,11,true);

    for (int gen=0; gen<=150; ++gen) {
        std::cout << "Gen " << gen << "\n";
        printGrid(grid);
        grid.step(); // B3/S23
        std::this_thread::sleep_for(450ms);
    }
    return 0;
}
