Master Sudoku

A console-based competitive Sudoku game developed in C++, featuring multiple difficulty levels, real-time scoring, a stopwatch, lifelines, debugging support, and a persistent leaderboard system.

This project was developed as part of SPL-01 coursework and demonstrates problem-solving, game logic, file handling, and time-based scoring in C++.

Features

9×9 Sudoku board with valid puzzle generation

Four difficulty levels:

Easy

Medium

Hard

Extremely Difficult

Real-time stopwatch using std::chrono

Scoring system with:

Mistake penalties

Rewrite penalties

Debug penalties (increasing cost)

Time-based penalties

Bonus for unused moves

Lifeline system (usable once per game)

Debug mode to remove incorrect entries

Persistent leaderboard using file I/O

Input validation and rule enforcement

How to Run
Requirements

C++ compiler (GCC / Clang)

Works on Linux, macOS, and Windows (MinGW)

Compile
g++ main.cpp -o sudoku

Run
./sudoku

Gameplay Instructions

Enter moves in the format:

row column number


Example:

2 5 9

Special Commands
Input	Action
0	Exit game
-1	Show game rules
-2	Debug incorrect entries
-3	Use lifeline (once per game)
Scoring System Overview

Base Score: Depends on difficulty level

Penalties:

Invalid move: −5 points

Rewriting a cell: −20 points

Debug usage: Increasing penalty (100, 200, 300…)

Time: −100 points per minute

Lifeline: −10% of total score

Bonus:

Remaining moves are converted into bonus points

Final score is always non-negative.

Project Structure
Master-Sudoku/
│
├── main.cpp          // Complete Sudoku game (~600 lines)
├── leaderboard.txt   // Stores top scores
├── README.md

Concepts Used

Arrays and matrix manipulation

Randomized Sudoku generation

File handling (ifstream, ofstream)

Sorting and vectors

Time measurement with std::chrono

Input validation

Modular function design

Known Limitations

Console-based UI (no graphics)

Uses a fixed 9×9 grid

Global variables used for simplicity

Future Improvements

Convert to object-oriented design

Add graphical interface

Save and resume unfinished games

Difficulty-based puzzle uniqueness validation

Cross-platform UI support

Author

Jim
IIT, DU
SPL-01 Project
