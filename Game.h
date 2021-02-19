#ifndef GAME_H
#define GAME_H

namespace Game {
    class Creature {
        int type;
        int points;

        protected:
            int row;
            int col;

        public:
            Creature();
            Creature(int a_row, int a_col, int a_type);
            int getType() const; 
            void getPosition(int& a_row, int& a_col); // get pacman position in maze and store in a_row, a_col
            void showCreaturePosition();
            void setPosition(int a_row, int a_col);
            void addPoints(int a_point);
            void showCurrentPoints(); // show collected reward points
    };

    class Monster : public Creature {
        public:
            Monster(int row, int col);
            void getMove(int& next_row, int& next_col);
    };

    class Maze {
        int numRow;
        int numCol;
        int prevLoc; // stores the type of position the monster moves into (empty space or food)
        int** mat; // 2D matrix that stores the maze
        
        public:
            Maze();
            void showMazeProperty(); // for the maze 2D matrix
            void readMaze(); // read maze from text file and populate mat
            void drawMaze();
            void deleteMaze();
            void updateMaze(Creature& p, int row_, int col_); // update maze based on location of pacman object p and its previous location
            bool isValidMove(int nrow, int ncol); // Check if the move to new location (nrow,ncol) is valid
            void placeCreatureInMaze(Creature& p); // Position pacman object p into the maze
            int getReward(int r, int c); // return points as reward if move into food mat[i][j]=2 at location (r,c)
            int countFood(); // Check if there is any more food left in the maze
    };

    class CGame {
        public:
            int gameOver;
            CGame();
            void moveMonster(Maze& maze, Monster& monster); 
            void checkGameOver(Maze& maze, Creature& creature, Monster& monster); // check if player monster has eaten player
            void checkMove(char move, Maze& a_maze , Creature& a_creature, Monster& monster); // check if the move by creature is valid or not
    };
}

#endif