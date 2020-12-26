#include <iostream>
#include <fstream>
#include <string>
#include "Game.h"

using namespace std;

int main() {
    CGame game1;
    Maze m1; // init and allocate memory
    m1.readMaze();
    m1.showMazeProperty();
    m1.drawMaze();
    Creature p(1, 3, 1); // starting position of pacman (1) in maze
    m1.placeCreatureInMaze(p);
    m1.drawMaze();
    bool status;
    char move='y';
    while (move != 'q') {
        m1.drawMaze();
        m1.showMazeProperty();
        p.showCurrentPoints();
        p.showCreaturePosition();
        cout << endl << "enter move >> ";
        cin >> move;
        // check if move is valid in the maze
        game1.checkMove(move, m1, p);
        m1.showMazeProperty();
    }
    m1.deleteMaze();
    system("pause");
    return 0;
}