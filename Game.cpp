#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Game.h"

using namespace Game;
using namespace std;

Creature::Creature():points(0) {}

Creature::Creature(int a_row, int a_col, int a_type):points(0), row(a_row), col(a_col), type(a_type) {}

int Creature::getType() const {
    //converts the types of creatures to make them suitable for the Maze class
    switch (type) {
        case 1:
            return 3;
        case 2:
            return 4;
        default:
            return type;
    }
}

void Creature::getPosition(int& a_row, int& a_col) {
        a_row = row;
        a_col = col;
}

void Creature::showCreaturePosition() {
    string c_name = type == 1 ? "Pacman" : "Monster";
    cout << c_name << " at position (" << row << ", " << col <<")" << endl;
}

void Creature::setPosition(int a_row, int a_col) {
    row = a_row;
    col = a_col;
}

void Creature::addPoints(int a_point) {
    points += a_point;
}

void Creature::showCurrentPoints() {
    cout << "Your collected points = " << points << endl;
}


Monster::Monster(int row, int col) : Creature(row, col, 2) { // Monster objects are initialised as type 2 Creatures by default
    // initialise random number generator 
    srand(time(0));
}

void Monster::getMove(int& next_row, int& next_col) {
    int prev_row = row, prev_col = col;
    // move monster in a random direction
    int move = rand() % 4;
    switch(move) {
        case 0:
            prev_row += 1;
            break;
        case 1:
            prev_col += 1;
            break;
        case 2:
            prev_row -= 1;
            break;
        case 3:
            prev_col -= 1;
            break;
        default:
            prev_row += 0;
            prev_col += 0;
    }
    next_row = prev_row;
    next_col = prev_col;
}


Maze::Maze():numRow(0), numCol(0), prevLoc(2) {} // prevLoc = 2 because game spawns monster at a position that has food

void Maze::showMazeProperty() {
    cout << "Num rows = " << numRow << endl;
    cout << "Num columns = " << numCol << endl << endl;
    for (int i{}; i<numRow; i++) {
        for (int j{}; j<numCol; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Maze::readMaze() {
    char ch;
    int i{}, j{};
    string line;
    ifstream mazeFile("maze.txt");

    if (mazeFile.is_open()) {
        while(getline(mazeFile, line)) {
            numRow++;
        }
        mazeFile.close();
    }
    numCol = line.length();

    mat = new int*[numRow];
    for (int k{}; k<numRow; k++) {
        mat[k] = new int[numCol];
    }

    mazeFile.open("maze.txt");
    if (mazeFile.is_open()) {
        while (mazeFile.get(ch)) {
            if (ch == '\n') {
                j = 0;
                i++;
            } else {
                mat[i][j] = ch - '0';
                j++;
            }
        }
        mazeFile.close();
    }
}

void Maze::drawMaze() {
    cout << endl;
    for (int i{}; i<numRow; i++) {
        for (int j{}; j<numCol; j++) {
            switch (mat[i][j]) {
            case 0:
                cout << " ";
                break;
            case 1:
                cout << "|";
                break;
            case 2:
                cout << "*";
                break;
            case 3:
                cout << "P";
                break;
            case 4:
                cout << "M";
            default:
                cout << "";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void Maze::deleteMaze() {
    delete[] mat;
}

void Maze::updateMaze(Creature& p, int row_, int col_) {
    int type = p.getType();
    int prevRow, prevCol;
    p.getPosition(prevRow, prevCol);
    if (type == 4) {
        // this basically restores the position type of whatever position the monster moves into
        // it is done to ensure the monster doesn't eat the food too
        mat[prevRow][prevCol] = prevLoc;
        prevLoc = mat[row_][col_];
    } else {
        mat[prevRow][prevCol] = 0;
    }
    mat[row_][col_] = type;
}

void Maze::placeCreatureInMaze(Creature& p) {
    int c_row, c_col;
    p.getPosition(c_row, c_col);
    mat[c_row][c_col] = p.getType();
}

bool Maze::isValidMove(int nrow, int ncol) {
    if ((nrow >= 0 && nrow < numRow) && (ncol >= 0 && ncol < numCol)) {
        return mat[nrow][ncol] == 1 ? false : true;
    }
    return false;
}

int Maze::getReward(int r, int c) {
    return mat[r][c] == 2 ? 1 : 0;
}

int Maze::countFood() {
    int foodCount = 0;
    for (int i{}; i<numRow; i++) {
        for (int j{}; j<numCol; j++) {
            if (mat[i][j] == 2) foodCount++;
        }
    }
    return foodCount;
}


CGame::CGame() : gameOver(0) {}

void CGame::moveMonster(Maze& maze, Monster& monster) {
    int next_row, next_col;
    do {
        // keep getting a new move until a valid move is found
        monster.getMove(next_row, next_col);
    } while (!maze.isValidMove(next_row, next_col));
    maze.updateMaze(monster, next_row, next_col);
    monster.setPosition(next_row, next_col);
}

void CGame::checkGameOver(Maze& maze, Creature& creature, Monster& monster) {
    int p_row, p_col, m_row, m_col;
    creature.getPosition(p_row, p_col);
    monster.getPosition(m_row, m_col);
    if (m_row == p_row && m_col == p_col) gameOver = -1;
    if (maze.countFood() == 0) gameOver = 1;
}

void CGame::checkMove(char move, Maze& a_maze , Creature& a_creature, Monster& monster) {
    int p_row, p_col;
    a_creature.getPosition(p_row, p_col);
    switch (move) {
        case 'w':
            p_row -= 1;
            break;
        case 'a':
            p_col -= 1;
            break;
        case 's':
            p_row += 1;
            break;
        case 'd':
            p_col += 1;
            break;
        case 'q':
            break;
        default:
            cout << "Invalid input." << endl << endl;
    }
    if (a_maze.isValidMove(p_row, p_col)) {
        a_creature.addPoints(a_maze.getReward(p_row, p_col));
        a_maze.updateMaze(a_creature, p_row, p_col);
        a_creature.setPosition(p_row, p_col);
        checkGameOver(a_maze, a_creature, monster); // check if pacman moves into monster's position
        moveMonster(a_maze, monster);
        checkGameOver(a_maze, a_creature, monster); // check if monster moves into pacman's position
    } else {
        cout << "Invalid move." << endl << endl;
    }
}