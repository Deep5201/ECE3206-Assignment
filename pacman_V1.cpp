#include <iostream>
#include <fstream>
#include <string>
#include "Game.h"

/*
IMPORTANT: External Class file (Game.cpp) must be compiled together for the game to work.
The following build command should be used:

g++ pacman_V1.cpp Game.cpp -o pacman_V1.exe

If "Game.cpp" is not included during compilation there will be multiple Linker errors
as it will not be able to locate any of the Classes or their members.
*/

using namespace Game;
using namespace std;

int main() {
	CGame game1;
	Maze m1; // init and allocate memory
	m1.readMaze(); 
	m1.showMazeProperty();
	
	m1.drawMaze();
	Creature p(1, 3, 1); // starting position of pacman in maze at(1,3) where type=1 is pacman
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
		// check if move is  valid in the maze
		game1.checkMove(move, m1, p); // if it is valid, update the pacman position and update maze
		m1.showMazeProperty();
	}
	
	
	m1.deleteMaze();
	system("pause");
	return 1;
}

