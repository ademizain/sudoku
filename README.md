# Sudoku Game
This is a Sudoku game program written in C++ that allows you to play Sudoku, generate new puzzles, and solve existing ones. It utilizes the X11 library for displaying the game board and XQuartz for macOS compatibility. Passed Google Tests for all test functions

### Features:
- Play Sudoku
- Generate new puzzles with various levels of difficulty
- Solve Sudoku puzzles
- Visualize the Sudoku solving process

### Requirements:
- C++ Compiler
- X11 library
- XQuartz (for macOS users)

### Installation:
- Clone the repository to your local machine:
```
$ git clone https://github.com/your-username/sudoku-game.git
```
- Build the program:
 ```
$ cd sudoku-game
$ cmake . -B build
$ cd build
$ make
```  
- Run the program:
```
$ ./sudoku_game
```

### Usage:
Follow the on-screen instructions to play Sudoku.
Use generatePuzzle and solveSudoku functions in the code to generate or solve Sudoku puzzles programmatically.

### Troubleshooting:
#### Error: Unable to open X display: 
Make sure you have XQuartz installed on macOS, and X11 forwarding is enabled for SSH connections. If running on a local machine, make sure your X server is properly configured.

### Contributing
Contributions are welcome! If you find any issues or want to improve the program, please open an issue or submit a pull request.

### License:
This project is licensed under the MIT License - see the LICENSE file for details.
