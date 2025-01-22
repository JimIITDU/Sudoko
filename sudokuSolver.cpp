#include <bits/stdc++.h>
#define N 9

using namespace std;
using namespace std::chrono;

class Stopwatch {
private:
    steady_clock::time_point start_time;
    steady_clock::time_point stop_time; 
    bool running = false;               

public:
    void start() {
        start_time = steady_clock::now();  
        running = true;                    
        cout << "The game has begun" << endl;
    }

    void stop() {
        if (running) {
            stop_time = steady_clock::now();
            running = false;
            cout << "The Game has ended." << endl;
            auto duration = duration_cast<seconds>(stop_time - start_time);
            cout << "Total time spent: " << duration.count() << " seconds" << endl;
        } else {
            cout << "Stopwatch is not running!" << endl;
        }
    }

    void elapsed() {
        if (running) {
            auto current_time = steady_clock::now();  
            auto duration = duration_cast<seconds>(current_time - start_time); 
            cout << "Total time: " << duration.count() << " seconds" << endl;
        }
    }
};

int puzzle[N][N], locked[N][N];

int solution[N][N] = {
    {5, 3, 4, 6, 7, 8, 9, 1, 2},
    {6, 7, 2, 1, 9, 5, 3, 4, 8},
    {1, 9, 8, 3, 4, 2, 5, 6, 7},
    {8, 5, 9, 7, 6, 1, 4, 2, 3},
    {4, 2, 6, 8, 5, 3, 7, 9, 1},
    {7, 1, 3, 9, 2, 4, 8, 5, 6},
    {9, 6, 1, 5, 3, 7, 2, 8, 4},
    {2, 8, 7, 4, 1, 9, 6, 3, 5},
    {3, 4, 5, 2, 8, 6, 1, 7, 9}
};

void printPuzzle() {
    cout << " -----------------------" << endl;
    for (int i = 0; i < 9; i++) {
        cout << "| ";
        for (int j = 0; j < 9; j++) {
            cout << puzzle[i][j] << " ";
            if ((j + 1) % 3 == 0)
                cout << "| ";
        }
        cout << endl;
        if ((i + 1) % 3 == 0)
            cout << " -----------------------" << endl;
    }
}

bool checkCol(int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (puzzle[row][i] == num) {
            cout << "Value already exists in the column" << endl;
            return false;
        }
    }
    return true;
}

bool checkRow(int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (puzzle[i][col] == num) {
            cout << "Value already exists in the row" << endl;
            return false;
        }
    }
    return true;
}

bool checkSquare(int row, int col, int num) {
    row = (row / 3) * 3;
    col = (col / 3) * 3;
    for (int i = row; i < row + 3; i++) {
        for (int j = col; j < col + 3; j++) {
            if (puzzle[i][j] == num) {
                cout << "Value already exists in the SubSquare" << endl;
                return false;
            }
        }
    }
    return true;
}

bool isValid(int row, int col, int num) {
    bool s, c, r;
    s = checkSquare(row, col, num);
    c = checkCol(row, col, num);
    r = checkRow(row, col, num);
    return s && c && r;
}

void copySolutionToPuzzle() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            locked[i][j] = puzzle[i][j] = solution[i][j];
        }
    }
}

void generatePuzzle(int difficulty) {
    copySolutionToPuzzle();
    int remove;

    if (difficulty == 1) {
        remove = 41;
        cout << "Difficulty chosen: Easy" << endl;
    } else if (difficulty == 2) {
        remove = 46;
        cout << "Difficulty chosen: Medium" << endl;
    } else if (difficulty == 3) {
        remove = 51;
        cout << "Difficulty chosen: Hard" << endl;
    } else {
        remove = 61;
        cout << "Difficulty chosen: Extremely Difficult" << endl;
    }

    srand(time(0));
    while (remove > 0) {
        int i = rand() % N;
        int j = rand() % N;
        if (puzzle[i][j] != 0) {
            locked[i][j] = puzzle[i][j] = 0;
            remove--;
        }
    }
}

void playSudoku() {
    cout << "Start solving the Sudoku!" << endl;
    Stopwatch stopwatch;
    stopwatch.start();
    int move = 69;
    while (move--) {
        cout << "Remaining moves: " << move + 1 << endl;
        stopwatch.elapsed();
        printPuzzle(); 

        cout << "Enter your move in the format: row col num (e.g., 2 5 5)" << endl;
        cout << "Type 0 to exit." << endl;

        int row, col, num;
        cin >> row;
        if (row == 0) {
            cout << "Do you want to quit? (y to quit, c to cancel): ";
            char exit;
            cin >> exit;
            if (exit == 'y') {
                cout << "Thanks for playing!" << endl;
                break;
            } else {
                move++;
                continue;
            }
        }
        cin >> col >> num;
        row--;
        col--;

        if (row < 0 || row >= N || col < 0 || col >= N || num < 1 || num > 9) {
            cout << "Invalid input! Please enter valid row, column, and number." << endl;
            move++;
            continue;
        }

        if (locked[row][col] != 0) {
            cout << "This cell can't be modified. Try another move." << endl;
            continue;
        }

        if (!isValid(row, col, num)) {
            cout << "Invalid move! This number violates Sudoku rules." << endl;
            continue;
        }

        puzzle[row][col] = num;

        if (memcmp(puzzle, solution, sizeof(puzzle)) == 0) {
            cout << "Congratulations! You solved the Sudoku!" << endl;
            printPuzzle();
            break;
        }
    }
    stopwatch.stop();
}

int main() {
    cout << "Choose Difficulty Level:" << endl;
    cout << "1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard" << endl;
    cout << "4. Extremely Difficult" << endl;
    int difficulty;
    cin >> difficulty;
    generatePuzzle(difficulty);

    char ans = 'n';
    do {
        playSudoku();
        cout << "Do you want to play another match? (y to play, n to quit): ";
        cin >> ans;
    } while (ans == 'y');

    return 0;
}
