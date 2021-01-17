#include <iostream>
#include <fstream>
#include <string>
#include "Game.h"

using namespace Game;
using namespace std;

Creature::Creature():points(0) {}

Creature::Creature(int a_row, int a_col, int a_type):points(0), row(a_row), col(a_col), type(a_type) {}

int Creature::getType() const {
    switch (type) {
        case 1:
            return 3;
        default:
            return type;
    };
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

void Creature::addPoints(int a_point) {
    points += a_point;
}

void Creature::showCurrentPoints() {
    cout << "Your collected points = " << points << endl;
}


Maze::Maze():numRow(0), numCol(0) {}

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

void Maze::updateMaze(Creature p, int row_, int col_) {
    int prevRow, prevCol;
    p.getPosition(prevRow, prevCol);
    mat[prevRow][prevCol] = 0;
    mat[row_][col_] = p.getType();
}

void Maze::placeCreatureInMaze(Creature p) {
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


void CGame::checkMove(char move, Maze& a_maze , Creature& a_creature) {
    int m_row, m_col;
    a_creature.getPosition(m_row, m_col);
    switch (move) {
        case 'w':
            m_row -= 1;
            break;
        case 'a':
            m_col -= 1;
            break;
        case 's':
            m_row += 1;
            break;
        case 'd':
            m_col += 1;
            break;
        case 'q':
            break;
        default:
            cout << "Invalid input." << endl << endl;
    }
    if (a_maze.isValidMove(m_row, m_col)) {
        a_creature.addPoints(a_maze.getReward(m_row, m_col));
        a_maze.updateMaze(a_creature, m_row, m_col);
        a_creature.setPosition(m_row, m_col);
    } else {
        cout << "Invalid move." << endl << endl;
    }
}