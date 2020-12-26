#ifndef GAME_H
#define GAME_H

// TODO: Upload to GitHub


class Creature {
    int row;
    int col;
    int type;
    int points=0;

    public:
        Creature() {}
        Creature(int a_row, int a_col, int a_type) {
            row = a_row; // position of creature object (Pacman) in maze
            col = a_col;
            type = a_type; // 1 indicate pacman
        }
        void getPosition(int& a_row, int& a_col); // get pacman position in maze and store in a_row, a_col
        void showCreaturePosition();
        void setPosition(int a_row, int a_col);
        void updateCreaturePosition(int nrow, int ncol); // update based on new pos
        void addPoints(int a_point);
        void showCurrentPoints(); // show collected reward points
};

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


class Maze {
    int numRow;
    int numCol;
    int** mat; // 2D matrix that stores the maze
    
    public:
        Maze() {}
        void showMazeProperty(); // for the maze 2D matrix
        void readMaze(); // read maze from text file and populate mat
        void drawMaze();
        void deleteMaze();
        void updateMaze(Creature p, int row_, int col_); // update maze based on location of pacman object p and its previous location
        bool isValidMove(int nrow, int ncol); // Check if the move to new location (nrow,ncol) is valid
        void placeCreatureInMaze(Creature p); // Position pacman object p into the maze
        int getReward(Maze a_maze, int r, int c); // return points as reward if move into food mat[i][j]=2 at location (r,c)
};

void Maze::showMazeProperty() {}

void Maze::readMaze() {}

void Maze::drawMaze() {}

void Maze::deleteMaze() {}

void Maze::updateMaze(Creature p, int row_, int col_) {}

void Maze::placeCreatureInMaze(Creature p) {}

bool Maze::isValidMove(int nrow, int ncol) {}

int Maze::getReward(Maze a_maze, int r, int c) {}


class CGame {
    public:
        void checkMove(char move, Maze& a_maze , Creature& a_creature); // check if the move by creature is valid or not
};

#endif