#include "sudoku_solver.h"

bool isValid(int grid[9][9], int row, int col, int num) {
    // Check if 'num' is not already in current row, column, or 3x3 subgrid
    for (int x = 0; x < 9; x++) {
        if (grid[row][x] == num || grid[x][col] == num || grid[row - row % 3 + x / 3][col - col % 3 + x % 3] == num) {
            return false;
        }
    }
    return true;
}

bool SudokuSolver::solveSudoku(int grid[9][9]) {
    int row, col;

    // Find an empty cell
    bool found = false;
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (grid[row][col] == 0) {
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }

    // No empty cell found, puzzle solved
    if (!found) {
        return true;
    }

    for (int num = 1; num <= 9; num++) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) {
                return true;
            }
            grid[row][col] = 0;
        }
    }

    return false;
}
