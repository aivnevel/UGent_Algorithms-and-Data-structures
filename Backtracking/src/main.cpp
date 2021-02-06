#include <iostream>
#include "Sudoku.h"

int main() {
    Sudoku s("src/1.txt");
    std::cout << s << std::endl;
    std::cout << s.isSolved() << std::endl;
    
    bool solved = s.solve();
    std::cout << (solved ? "Solved !" : "Not solvable") << std::endl;
    std::cout << s << std::endl;
    std::cout << s.isSolved() << std::endl;

    int sum = 0;
    for (int i=1; i<=50; i++){
        Sudoku s("src/sudokus/" + std::to_string(i) +".txt");
        s.solve();
        sum += s.getUpperLeft();
    }
    std::cout << sum << std::endl;

}