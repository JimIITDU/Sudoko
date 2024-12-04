#include <iostream>
using namespace std;

char FULL = 0x1FF;

int** createPuzzle();
void printPuzzle(int**);
//square*** setUpPuzzle(int**);

typedef struct box {
    struct Box* next;
}box;

typedef struct square {
    int number;
    char code;
    Box* box;
    int row;
    int column;
}Square;

int main(){
    int ** p = createPuzzle();
    printPuzzle(p);
}

int** createPuzzle() {
    int** puzzle;
    int arr[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    puzzle = (int **) malloc(sizeof(int*) * 9);
    for (int i = 0; i < 9; i++) {
        puzzle[i] = (int*)malloc(sizeof(int) * 9);
        for (int j = 0; j < 9; j++) {
            puzzle[i][j] = arr[i][j];
        }
    }
    return puzzle;
}

void printPuzzle(int** arr) {
    cout << " -----------------------" << endl;
    for (int i = 0; i < 9; i++) {
        cout << "|" << " ";
        for (int j = 0; j < 9; j++) {
            cout << arr[i][j] << " ";
            if ((j + 1) % 3 == 0)
                cout << "|" << " ";
        }
        cout << endl;
        if((i+1) % 3 == 0)
            cout << " -----------------------" << endl;
    }
    //cout << "-----------------" << endl;
}

square*** setUpPuzzle(int** puzzle) {
    Square*** sudoko;
    sudoko = (Square***)malloc(sizeof(Square*) * 9);
    puzzle = (int**)malloc(sizeof(int*) * 9);
    for (int i = 0; i < 9; i++) {
        sudoko[i] = (Square**)malloc(sizeof(Square**) * 9);
        for (int j = 0; j < 9; j++) {
            sudoko[i][j] = (Square*)malloc(sizeof(Square) * 9);
            sudoko[i][j]->number = puzzle[i][j];

            sudoko[i][j]->row = i;
            sudoko[i][j]->column = j;

            if (sudoko[i][j]->number != 0)
                sudoko[i][j]->code = 'POSSIBLE';
            else
                sudoko[i][j]->code = 0x0;
        }
    }
}
