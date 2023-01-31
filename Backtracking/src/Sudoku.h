#ifndef SUDOKU_H
#define SUDOKU_H

#include <fstream>
#include <iostream>
#include <bitset>

class Sudoku{
public:
    Sudoku(const std::string filename);
    bool solve();
    int getUpperLeft();
    friend std::ostream& operator<< (std::ostream &out, const Sudoku &s);
private:
    int grid[9][9];
    std::bitset<9> present;
    bool solve(int grid[9][9], int row, int col);
    void findNext(int &row, int &col, int startRow, int startCol);
};

std::ostream& operator<< (std::ostream &out, const Sudoku &s){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            out << s.grid[i][j] << " " ;

            if ((j+1) % 3 == 0 && j < 8)
                out << "| ";
        }
        out << std::endl;
        if ((i+1) % 3 == 0 && i < 8){
            out << "------+-------+------" << std::endl;
        }
    }
    return out;
}

Sudoku::Sudoku(const std::string filename){
    std::ifstream infile(filename);
    if (infile){
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                infile >> grid[i][j];
            }
        }
    }
}

int Sudoku::getUpperLeft(){
    return grid[0][0]*100 + grid[0][1]*10 + grid[0][2];
}

/*
Return the location of the next missing number.
Both parameters are output parameters.
*/
void Sudoku::findNext(int &row, int &col){
    while (grid[row][col] != 0){
        col++;
        if (col == 9){
            col = 0;
            row++;
            if (row == 9){
                return;
            }
        }
    }
}

bool Sudoku::solve()
{
    Cell nextCell = findNext();
    if (!nextCell.valid)
    {
        return true;
    }
    
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(nextCell.row, nextCell.col, num))
        {
            board[nextCell.row][nextCell.col] = num;
            if (solve())
            {
                return true;
            }
            board[nextCell.row][nextCell.col] = 0;
        }
    }
    return false;
}

bool Sudoku::solve(int grid[9][9], int row, int col){

    for (int i = 1; i <= 9; i++){
        // check if we can put i at (row, col)

        bool valid = true;

        int k = 0;
        while (valid && k < 9){
            valid = grid[row][k] != i;
            k++;
        }

        k=0;
        while (valid && k < 9){
            valid = grid[k][col] != i;
            k++;
        }

        int start_row = (row/3)*3;
        int start_col = (col/3)*3;
        k = 0;
        while (valid && k < 9){
            valid = grid[start_row+(k/3)][start_col+(k%3)] != i;
            k++;
        }

        if (valid){
            grid[row][col] = i;
            int next_row = row;
            int next_col = col;
            findNext(next_row, next_col);
            if (next_row == 9 || solve(grid, next_row, next_col)){
                return true;
            }
        }
    }

    // No solution found
    grid[row][col] = 0;
    return false;
}

private int findNext(int[][] maze, int[] curr, int[] dest) {
    int row = curr[0];
    int col = curr[1];
    int steps = curr[2];
    if (row == dest[0] && col == dest[1])
        return steps;

    maze[row][col] = 0;

    int[][] dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    for (int[] dir : dirs) {
        int newRow = row + dir[0];
        int newCol = col + dir[1];
        if (newRow >= 0 && newRow < maze.length && newCol >= 0 && newCol < maze[0].length && maze[newRow][newCol] == 1) {
            int[] next = {newRow, newCol, steps + 1};
            queue.offer(next);
        }
    }
    return Integer.MAX_VALUE;
}

#endif
