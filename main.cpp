#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <random>
#include <ctime>
#include <thread>
#include <X11/Xlib.h>

const int PUZZLE_SIZE = 9;
const int EMPTY_VALUE = 0;
std::array<int, 9> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
int numberOfSolution = 0;
Display* display; // Define the X display variable
Window window;

void setCursorPosition(int x, int y) {
    XWarpPointer(display, None, window, 0, 0, 0, 0, x, y);
    XFlush(display);
}

void sleep(int miliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
}

void printPuzzle(int puzzle[PUZZLE_SIZE][PUZZLE_SIZE], bool clear = true)
{
    if (clear)
    {
        setCursorPosition( 0, 0);
    }
    std:: string separator = "";
    std:: string text, padding;
    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        text = "|";
        separator = " -";
        padding = "|";
        for (int j = 0; j < PUZZLE_SIZE; j++)
        {
            std::string value = puzzle[i][j] == EMPTY_VALUE ? " " : std::to_string(puzzle[i][j]);
            text += "  " + value + "  |";
            separator += "------";
            padding += "     |";

            if (j % 3 == 2 && j != PUZZLE_SIZE - 1)
            {
                padding += "|";
                text += "|";
            }
        }

        if (i% 3 == 0 && i != 0)
        {
            std::replace(separator.begin(), separator.end(), '-', '=');
        }

        std::cout << separator << std::endl;
        std::cout << padding << std::endl;
        std::cout << text << std::endl;
        std::cout << padding << std::endl;
    }
    std::cout << separator << std::endl;
}

bool isValid(int puzzle[PUZZLE_SIZE][PUZZLE_SIZE], int row, int column, int value)
{
    //check if this row already has this value
    for (int c = 0; c < PUZZLE_SIZE; c++) {
        if (puzzle[row][c] == value) return false;
    }

    //check if this column already has his value
    for (int r = 0; r < PUZZLE_SIZE; r++) {
        if (puzzle[r][column] == value) return false;
    }

    int startRow = floor(row/3) * 3, startColumn = floor(column/3) * 3;
    for (int r = startRow; r < startRow + 3; r++)
    {
        for (int c = startColumn; c < startColumn + 3; c++)
        {
            if (puzzle[r][c] == value)
                return false;
        }
    }

    return true;
}

bool hasEmptyCell(int puzzle[PUZZLE_SIZE][PUZZLE_SIZE])
{
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        for (int j = 0; j < PUZZLE_SIZE; j++) {
            if (puzzle[i][j] == EMPTY_VALUE) return true;
        }
    }

    return false;
}

bool fillPuzzle(int (&puzzle)[PUZZLE_SIZE][PUZZLE_SIZE])
{
    int row, column;

    for (int i = 0; i < PUZZLE_SIZE * PUZZLE_SIZE; i++)
    {
        row = floor(i/PUZZLE_SIZE);
        column = i % PUZZLE_SIZE;

        if (puzzle[row][column] == EMPTY_VALUE) {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(values.begin(), values.end(), std::default_random_engine(seed));

            for (int j = 0; j < PUZZLE_SIZE; j++) {
                if (isValid(puzzle, row, column, values[j]))
                {
                    puzzle[row][column] = values[j];

                    if (!hasEmptyCell(puzzle) || fillPuzzle(puzzle)) {
                        return true;
                    }
                }
            }

            break;
        }
    }

    puzzle[row][column] = EMPTY_VALUE;
    return false;
}

bool solveSudoku(int puzzle[PUZZLE_SIZE][PUZZLE_SIZE], bool visualize = false)
{
    int row, column;

    for (int i=0; i < PUZZLE_SIZE * PUZZLE_SIZE; i++){
        row = floor(i/PUZZLE_SIZE);
        column = i % PUZZLE_SIZE;

        if (puzzle[row][column] == EMPTY_VALUE) {
            for (int value = 1; value <= PUZZLE_SIZE; value++){
                if (isValid(puzzle, row, column, value)) {

                    puzzle[row][column] = value;

                    if (visualize)
                    {
                        sleep(100);
                        printPuzzle(puzzle);
                    }

                    if (!hasEmptyCell(puzzle))
                    {
                        numberOfSolution++;
                        if (visualize)
                        {
                            sleep(100);
                            printPuzzle(puzzle);
                            return true;
                        }
                        break;
                    }
                    else if (solveSudoku(puzzle, visualize)) {
                        return true;
                    }
                }
            }

            break;
        }
    }

    puzzle[row][column] = EMPTY_VALUE;

    if (visualize)
    {
        sleep(100);
        printPuzzle(puzzle);
    }

    return false;
}

void generatePuzzle(int (&puzzle)[PUZZLE_SIZE][PUZZLE_SIZE], int difficulty = 1)
{
    for (int i = 0; i < PUZZLE_SIZE; i++) {
       for (int j = 0; j < PUZZLE_SIZE; j++) {
           puzzle[i][j] = EMPTY_VALUE;
       }
    }
    fillPuzzle(puzzle);

    //start remove cells from a fulfilled sudoku puzzle

    int attempt = difficulty;
    srand((unsigned)time(0));

    while (attempt > 0)
    {
        //generate random value between 0 to 8
        int row = floor(rand() % PUZZLE_SIZE);
        int column = floor(rand() % PUZZLE_SIZE);

        while (puzzle[row][column]== EMPTY_VALUE)
        {
            row = floor(rand() % PUZZLE_SIZE);
            column = floor(rand() % PUZZLE_SIZE);
        }

        int oldValue = puzzle[row][column];
        puzzle[row][column] = EMPTY_VALUE;

        numberOfSolution = 0;
        solveSudoku(puzzle);

        //if by set this cell to empty, the sudoku puzzle won't have only1 solution
        //then we're not going to remove this cell
        if (numberOfSolution != 1) {
            puzzle[row][column] = oldValue;
            attempt--;
        }
    }
}

int main(int, char **)
{
    display = XOpenDisplay(NULL);
    if (display == nullptr) {
        fprintf(stderr, "Error: Unable to open X display\n");
        return 1;
    }

    window = DefaultRootWindow(display);

    // Set the cursor position to (100, 100)
    setCursorPosition(100, 100);

    int puzzle[PUZZLE_SIZE][PUZZLE_SIZE];

    generatePuzzle(puzzle);
    printPuzzle(puzzle);

    std::string solve;
    std::cout << "Do you want to get the solution? (y/n) ";
    std::cin >> solve;

    if (solve == "n" || solve == "N")
    {
        return 0;
    }

    solveSudoku(puzzle, true);

    XCloseDisplay(display);

    return 0;
}