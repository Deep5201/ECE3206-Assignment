#include <iostream>
#include <fstream>
#include <string>
#include "Game.h"

using namespace Game;
using namespace std;

Creature::Creature() {}

Creature::Creature(int a_row, int a_col, int a_type) {
    row = a_row; // position of creature object (Pacman) in maze
    col = a_col;
    type = a_type; // 1 indicate pacman
}

void Creature::getPosition(int& a_row, int& a_col) {
        a_row = row;
        a_col = col;
}

void Creature::showCreaturePosition() {
    cout << "Pacman at position (" << row << ", " << col <<")" << endl;
}

void Creature::setPosition(int a_row, int a_col) {
    row = a_row;
    col = a_col;
}

void Creature::updateCreaturePosition(int nrow, int ncol) {
    row = nrow;
    col = ncol;
}

void Creature::addPoints(int a_point) {
    points += a_point;
}

void Creature::showCurrentPoints() {
    cout << "Your collected points = " << points << endl;
}


Maze::Maze() {}

void Maze::showMazeProperty() {}

void Maze::readMaze() {
    string l;
    ifstream mazeFile("maze.txt");
    if (mazeFile.is_open()) {
        while (getline(mazeFile, l)) {
            cout << l << endl;
        }
        mazeFile.close();
    }
}

void Maze::drawMaze() {}

void Maze::deleteMaze() {}

void Maze::updateMaze(Creature p, int row_, int col_) {}

void Maze::placeCreatureInMaze(Creature p) {}

bool Maze::isValidMove(int nrow, int ncol) {}

int Maze::getReward(Maze a_maze, int r, int c) {}


void CGame::checkMove(char move, Maze& a_maze , Creature& a_creature) {}