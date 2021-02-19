#include <iostream>
#include <fstream>
#include <string>
#include "Game.h"

/*
IMPORTANT: External Class file (Game.cpp) must be compiled together for the game to work.
The following build command should be used:

g++ pacman_V2.cpp Game.cpp -o pacman_V2.exe

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
	Monster m(4, 5); // starting position of monster in maze at(4,5)
	m1.placeCreatureInMaze(p);
	m1.placeCreatureInMaze(m);
	m1.drawMaze();

	char move='y';
	while (move != 'q') {
		m1.drawMaze();
		m1.showMazeProperty();
		p.showCurrentPoints();
		p.showCreaturePosition();
		m.showCreaturePosition();
		// if game is over, exit loop
		if (game1.gameOver != 0) {
			cout << endl << "Game Over!" << endl;
			if (game1.gameOver == 1) cout << "You managed to eat all the food." << endl << endl;
			else if (game1.gameOver == -1) cout << "You were eaten by the monster." << endl << endl;
			break;
		}
		cout << endl << "enter move >> ";
		cin >> move;
		// check if move is  valid in the maze
		game1.checkMove(move, m1, p, m); // if it is valid, update the pacman position and update maze
	}
	
	
	m1.deleteMaze();
	system("pause");
	return 1;
}
