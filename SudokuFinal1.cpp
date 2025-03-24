#include <bits/stdc++.h>
#define N 9

using namespace std;
using namespace std::chrono;

int difficulty;

class Stopwatch {
    public:
        steady_clock::time_point start_time;
        steady_clock::time_point stop_time; 
        bool running = false;               
    
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
        int getStopTime() {
            if (!running) {
                return duration_cast<seconds>(stop_time - start_time).count();
            } else {
                cout << "Stopwatch is still running!" << endl;
                return -1;  
            }
        }        
};
    

struct LeaderboardEntry {
    string name;
    int score;
    int position;
};

vector<LeaderboardEntry> readLeaderboard(const string& filename) {
    vector<LeaderboardEntry> leaderboard;
    ifstream leaderboardFile(filename);
    
    if (!leaderboardFile) {
        cerr << "Error: Unable to open the leaderboard file.\n";
        return leaderboard;
    }

    string line;
    getline(leaderboardFile, line);

    while (getline(leaderboardFile, line)) {
        istringstream iss(line);
        int position;
        string name;
        int score;
        
        iss >> position >> name >> score;
        leaderboard.push_back({name, score, position});
    }

    leaderboardFile.close();
    return leaderboard;
}

void showRules() {
    cout << "Welcome to Sudoku! This game offers four difficulty levels:" << endl;
    cout << "1. Easy - Score: 1000" << endl;
    cout << "2. Medium - Score: 2000" << endl;
    cout << "3. Hard - Score: 3000" << endl;
    cout << "4. Extremely Difficult - Score: 5000" << endl;

    cout << "\nFeatures and Penalties:" << endl;
    cout << "1. **Mistake Penalty**: Placing a number that already exists in the row, column, or sub-grid." << endl;
    cout << "   - **Score Deduction**: 5 points" << endl;
    cout << "2. **Rewrite Penalty**: Editing a previously placed number." << endl;
    cout << "   - **Score Deduction**: 20 points" << endl;
    cout << "3. **Debug Option**: Removes incorrectly placed numbers by comparing them with the solution." << endl;
    cout << "   - **Score Deduction**: Each time increases by 100 (100, 200, 300....)" << endl;
    cout << "4. **Lifelines**: Replaces the most difficult cell with the correct number. Can be used only once" << endl;
    cout << "   - **Score Deduction**: 10%" << "of total" << endl;
    cout << "5. **Time Penalty**: A penalty is applied for every minute spent." << endl;
    cout << "   - **Score Deduction**: 100 points per minute" << endl;

    cout << "\nBonus System:" << endl;
    cout << "Any unused moves at the end of the game will be converted into bonus points." << endl;
    cout << "For instance, if 10 moves remain, the bonus will be calculated as the sum of the numbers from 1 to 10 (i.e., 1 + 2 + 3 + ... + 10)." << endl;
}

void writeLeaderboard(const vector<LeaderboardEntry>& leaderboard, const string& filename) {
    ofstream leaderboardFile(filename);
    
    if (!leaderboardFile) {
        cerr << "Error: Unable to open the leaderboard file.\n";
        return;
    }

    leaderboardFile << "No Name Score" << endl;

    for (const auto& entry : leaderboard) {
        leaderboardFile << entry.position << " " << entry.name << " " << entry.score << endl;
    }

    leaderboardFile.close();
}

void updateLeaderboard(const string& name, int score, const string& filename) {

    vector<LeaderboardEntry> leaderboard = readLeaderboard(filename);
    
    LeaderboardEntry newEntry = {name, score, 0};

    leaderboard.push_back(newEntry);

    sort(leaderboard.begin(), leaderboard.end(), [](const LeaderboardEntry& a, const LeaderboardEntry& b) {
        return a.score > b.score;  
    });

    for (int i = 0; i < leaderboard.size(); i++) {
        leaderboard[i].position = i + 1;  
    }

    writeLeaderboard(leaderboard, filename);

    cout << "Leaderboard updated successfully!" << endl;
}

void getPlayerName(int score){
    string playerName;
    int playerScore;

    cout << "Enter your name: ";
    cin >> playerName;

    playerScore = score;

    string filename = "leaderboard.txt";
    cout << "Name: " << playerName << "\t" << "Score: " << playerScore << endl;
    updateLeaderboard(playerName, playerScore, filename);
}

int L;

int puzzle[N][N], locked[N][N], solution[N][N], score;

void fillBasePattern() {
    int base = 3;
    int nums[N];
    iota(nums, nums + N, 1); // Fill nums with values 1-9
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            solution[row][col] = nums[(col + (row * base + row / base) % N) % N];
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
            if (row1 != row2) swapRows(row1, row2);
        }
    }
}

void shuffleCols() {
    int base = 3;
    for (int block = 0; block < base; block++) {
        int startCol = block * base;
        for (int i = 0; i < L; i++) {
            int col1 = startCol + rand() % base;
            int col2 = startCol + rand() % base;
            if (col1 != col2) swapCols(col1, col2);
        }
    }
}

void shuffleRowBlocks() {
    int base = 3;
    for (int i = 0; i < L; i++) {
        int block1, block2;
        do {
            block1 = rand() % base;
            block2 = rand() % base;
        } while (block1 == block2);

        for (int row = 0; row < base; row++) {
            swapRows(block1 * base + row, block2 * base + row);
        }
    }
}

void shuffleColBlocks() {
    int base = 3;
    for (int i = 0; i < L; i++) {
        int block1, block2;
        do {
            block1 = rand() % base;
            block2 = rand() % base;
        } while (block1 == block2);

        for (int col = 0; col < base; col++) {
            swapCols(block1 * base + col, block2 * base + col);
        }
    }
}

void makeSoltuionSudoko(){
    fillBasePattern();
    shuffleRows();
    shuffleCols();
    shuffleRowBlocks();
    shuffleColBlocks();
}

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

void printLocked() {
    cout << " -----------------------" << endl;
    for (int i = 0; i < 9; i++) {
        cout << "| ";
        for (int j = 0; j < 9; j++) {
            cout << locked[i][j] << " ";
            if ((j + 1) % 3 == 0)
                cout << "| ";
        }
        cout << endl;
        if ((i + 1) % 3 == 0)
            cout << " -----------------------" << endl;
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

void debugPuzzle() {
    cout << "Debugging: Checking for incorrect values..." << endl;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] != 0 && puzzle[i][j] != solution[i][j]) {
                cout << "Incorrect value at (" << i + 1 << ", " << j + 1 << ") removed." << endl;
                puzzle[i][j] = 0; // Remove the incorrect number
            }
        }
    }
    
    cout << "Debugging complete. " << endl;
}

bool checkCol(int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (puzzle[row][i] == num) {
            cout << "Value already exists in the row" << endl;
            return false;
        }
    }
    return true;
}

bool checkRow(int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (puzzle[i][col] == num) {
            cout << "Value already exists in the column" << endl;
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
    r = checkRow(row, col, num);
    c = checkCol(row, col, num);
    s = checkSquare(row, col, num);
    return s && c && r;
}

void copySolutionToPuzzle() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            locked[i][j] = puzzle[i][j] = solution[i][j];
        }
    }
}

void generatePuzzle() {
    cout << "Welcome to Sudoku!\nGood luck—aim for the top of the leaderboard!" << endl;
    showRules();
    cout << "Choose Difficulty Level:" << endl;
    cout << "1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard" << endl;
    cout << "4. Extremely Difficult" << endl;
    cin >> difficulty;
    
    int remove;

    if (difficulty == 1) {
        remove = 41;
        L = 5;
        cout << "Difficulty choosen: Easy" << endl;
    } else if (difficulty == 2) {
        remove = 46;
        L = 8;
        cout << "Difficulty choosen: Medium" << endl;
    } else if (difficulty == 3) {
        remove = 51;
        L = 10;
        cout << "Difficulty choosen: Hard" << endl;
    } else {
        remove = 61;
        L = 20;
        cout << "Difficulty choosen: Extremely Difficult" << endl;
    }
    makeSoltuionSudoko();
    copySolutionToPuzzle();

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

void useLifeline() {
    int mostDifficultRow = -1, mostDifficultCol = -1, maxConstraints = -1;

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (puzzle[row][col] == 0) {  
                int constraints = 0;

                for (int i = 0; i < N; i++)
                    if (puzzle[row][i] != 0) constraints++;

                for (int i = 0; i < N; i++)
                    if (puzzle[i][col] != 0) constraints++;

                int startRow = (row / 3) * 3, startCol = (col / 3) * 3;
                for (int i = startRow; i < startRow + 3; i++)
                    for (int j = startCol; j < startCol + 3; j++)
                        if (puzzle[i][j] != 0) constraints++;

                if (constraints > maxConstraints) {
                    maxConstraints = constraints;
                    mostDifficultRow = row;
                    mostDifficultCol = col;
                }
            }
        }
    }

    if (mostDifficultRow != -1 && mostDifficultCol != -1) {
        puzzle[mostDifficultRow][mostDifficultCol] = solution[mostDifficultRow][mostDifficultCol];
        cout << "Lifeline used! The cell at (" << mostDifficultRow + 1 << ", " << mostDifficultCol + 1
             << ") has been filled with the correct number." << endl;
    } else {
        cout << "No empty cells found to use the lifeline!" << endl;
    }
}


int calculateScore(int move, int difficulty, int time, int debug, bool Lifeline, int mistake, int rewrite) {

    int finalScore = 0;

    cout << endl << "Here is your score" << endl;

    finalScore = difficulty*1000;
    if(difficulty==4){
        cout << "Level based score addition: 5000" << endl;
        finalScore += 1000;
    }else{
        cout << "Level based score addition: " << 1000*difficulty << endl;
    }

    cout << "Mistake penalty: " << mistake*5 << " (Total mistake: " << mistake << ") " << endl;
    finalScore -= mistake*5;

    cout << "Rewrite Penalty: " << rewrite*20 << " (Rewriting Occured: " << rewrite << ") " << endl;
    finalScore -= rewrite*20;

    int sumDebug = 100*(debug * (debug + 1)/2);
    cout << "Debug penalty: " << sumDebug << " (Debugger used: " << debug << ") " << endl;
    finalScore -= sumDebug;

    if(Lifeline == true){
        cout << "LifeLine penalty: 0%" <<  " (Lifeline Used: No)" << endl;
    }else{
        cout << "LifeLine penalty: 10%" << " (Lifeline Used: Yes)" << endl;
    }
    
    int timeScore = (time/60)*100;
    cout << "Time penalty: " << timeScore << " (Used Time: " << time << " seconds) " << endl; 
    finalScore -= time;
    
    int sumMove = (move * (move + 1)) / 2;
    cout << "Move based Score Addition: " << sumMove << " (Remainging moves: " << move << ")" << endl;
    finalScore += sumMove;

    if(Lifeline){
        finalScore *= .90;
    }

    finalScore = max(finalScore, 0);
    
    cout << "Score: " << finalScore << endl;
    return finalScore;
}

void playSudoku() {
    cout << "Start solving the Sudoku!" << endl;
    Stopwatch stopwatch;
    stopwatch.start();
    int move = 69;
    int debug = 0;
    bool ll = true;
    int mistake = 0;
    int rewrite = 0;
    int time;
    while (move--) {
        cout << "Remaining moves: " << move + 1 << endl;
        stopwatch.elapsed();
        printPuzzle(); 

        cout << "Enter your move in the format: row col num (e.g., 2 5 5)" << endl;
        if(ll)
        cout << "Type 0 to exit.\t Type -1 to see rules.\t -2 for debugging.\t -3 for LifeLine" << endl;
        else
        cout << "Type 0 to exit.\t Type -1 to see rules.\t -2 for debugging." << endl;

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

        if (row == -1) {  
            debugPuzzle();
            move++;
            debug++;
            continue;
        }

        if (row == -2){
            if(ll){
                useLifeline();
                ll = false;
            }else{
                 cout << "Lifeline already used! You can only use it once." << endl;
            }
            continue;
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
            cout << "Here is the Locked Numbers: " << endl;
            printLocked();
            move++;
            continue;
        }

        if (!isValid(row, col, num)) {
            cout << "Invalid move! This number violates Sudoku rules." << endl;
            mistake++;
            continue;
        }

        if(puzzle[row][col] != 0){
            cout << "Rewriting the cell" << endl; 
            rewrite++;
        }

        puzzle[row][col] = num;

        if (memcmp(puzzle, solution, sizeof(solution)) == 0) {
            printPuzzle();
            cout << "Congratulations! You have solved the Sudoku!" << endl;
            cout << "Here is the solution: " << endl;
            printSolution();
            stopwatch.stop();
            time = stopwatch.getStopTime();
            int score = calculateScore(move, difficulty, time, debug, ll, mistake, rewrite);
            getPlayerName(score);
            break;
        }
    }
}


int main() {
    char ans;
    do {
        generatePuzzle();
        playSudoku();
        cout << "Do you want to play another match? (y to play, n to quit): ";
        cin >> ans;
    } while (ans == 'y');

    return 0;
}
