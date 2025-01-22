#include <bits/stdc++.h>
#define N 9
#define L 5

using namespace std;

int solution[N][N];

void fillBasePattern() {
    int base = 3;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            solution[row][col] = (row * base + row / base + col) % N + 1;
        }
    }
}

void swapRows(int row1, int row2) {
    for (int col = 0; col < N; col++) {
        swap(solution[row1][col], solution[row2][col]);
    }
}

void swapCols(int col1, int col2) {
    for (int row = 0; row < N; row++) {
        swap(solution[row][col1], solution[row][col2]);
    }
}

void shuffleRows() {
    int base = 3;
    for (int block = 0; block < base; block++) {
        int startRow = block * base;
        for (int i = 0; i < L; i++) {
            int row1 = startRow + rand() % base;
            int row2 = startRow + rand() % base;
            swapRows(row1, row2);
        }
    }
}

void shuffleCols() {
    int base = 3;
    for (int block = 0; block < L; block++) {
        int startCol = block * base;
        for (int i = 0; i < base; i++) {
            int col1 = startCol + rand() % base;
            int col2 = startCol + rand() % base;
            swapCols(col1, col2);
        }
    }
}

void shuffleRowBlocks() {
    int base = 3;
    for (int i = 0; i < L; i++) {
        int block1 = rand() % base;
        int block2 = rand() % base;
        for (int row = 0; row < base; row++) {
            swapRows(block1 * base + row, block2 * base + row);
        }
    }
}

void shuffleColBlocks() {
    int base = 3;
    for (int i = 0; i < L; i++) {
        int block1 = rand() % base;
        int block2 = rand() % base;
        for (int col = 0; col < base; col++) {
            swapCols(block1 * base + col, block2 * base + col);
        }
    }
}

void printSolution() {
    cout << " -----------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| ";
        for (int j = 0; j < N; j++) {
            cout << solution[i][j] << " ";
            if ((j + 1) % 3 == 0)
                cout << "| ";
        }
        cout << endl;
        if ((i + 1) % 3 == 0)
            cout << " -----------------------" << endl;
    }
}

void makeSoltuionSudoko(){
    fillBasePattern();
    shuffleRows();
    shuffleCols();
    shuffleRowBlocks();
    shuffleColBlocks();
}

int main() {
    srand(time(0));

    fillBasePattern();

    cout << "Generated based Sudoku Solution:\n";
    printSolution();

    shuffleRows();
    printSolution();
    shuffleCols();
    printSolution();
    shuffleRowBlocks();
    printSolution();
    shuffleColBlocks();
    printSolution();

    cout << "Generated Sudoku Solution:\n";
    printSolution();

    return 0;
}
