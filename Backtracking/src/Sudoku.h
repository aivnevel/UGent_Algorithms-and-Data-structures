#ifndef SUDOKU_H
#define SUDOKU_H

#include <fstream>
#include <iostream>
#include <bitset>

class Sudoku{
public:
    Sudoku(const std::string filename);
    bool isSolved();
    bool solve();
    int getUpperLeft();
    friend std::ostream& operator<< (std::ostream &out, const Sudoku &s);
private:
    int grid[9][9];
    bool solve(int grid[9][9], int row, int col);
    void findNext(int &row, int &col);
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

bool Sudoku::isSolved(){
    std::bitset<9> present;

    // Check rows
    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            int value = grid[row][col];
            if (value < 1 || value > 9 || present[value])
                return false;
            present[value] = true;
        }
        if (present.count() != 9)
            return false;
        present.reset();
    }


    // Check columns
    for (int col = 0; col < 9; col++){
        for (int row = 0; row < 9; row++){
            if (present[grid[row][col]])
                return false;
            present[grid[row][col]] = true;
        }
        if (present.count() != 9)
            return false;
        present.reset();
    }


    // Check squares
    for (int row = 0; row < 9; row += 3){
        for (int col = 0; col < 9; col += 3){
            for (int i=row; i < row+3; i++){
                for (int j=col; j<col+3; j++){
                    if (present[grid[i][j]])
                        return false;
                present[grid[i][j]] = true;
                }
            }
            if (present.count() != 9)
                return false;
            present.reset();
        }        
    }

    return true;
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

bool Sudoku::solve(){
    int row = 0;
    int col = 0;

    findNext(row, col);

    if (row < 9)
        return solve(grid, row, col);

    // it was already solved
    return true;
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
            // Put the number here for now and continue the search
            grid[row][col] = i;

            // Find the location of the next missing number
            int next_row = row;
            int next_col = col;
            findNext(next_row, next_col);

            if (next_row == 9){
                // No mising numbers ? The sudoku is solved !
                return true;
            }

            // Try to solve the remainder
            if (solve(grid, next_row, next_col)){
                return true;
            }
            // The number was incorrect, reset
            else{
                grid[row][col] = 0;
            }
        }        
    }
    // If we end up here, it was a dead end
    return false;
}

#endif