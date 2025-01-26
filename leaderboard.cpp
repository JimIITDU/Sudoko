#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void updateLeaderboard(const string& name, int score, const string& filename) {

    ofstream leaderboardFile(filename, std::ios::app);
    if (!leaderboardFile) {
        std::cerr << "Error: Unable to open the leaderboard file.\n";
        return;
    }

    char playerName[25];

    for(int i=0; i<30; i++){
        playerName[i] = '\0';
    }

    for(int i=0; name[i] != '\0'; i++){
        playerName[i] = name[i];
    }

    for(int i=0; i<30; i++){
        if(playerName[i] != '\0')
        leaderboardFile << playerName[i];
        else
        leaderboardFile << " ";
    }

    leaderboardFile << score << endl;

    leaderboardFile.close();
    cout << "Leaderboard updated successfully!" << endl;
}

void getPlayerName(int score){
    string playerName;
    int playerScore;

    cout << "Enter your name: ";
    cin >> playerName;

    playerScore = score;

    string filename = "leaderboard.txt";
    updateLeaderboard(playerName, playerScore, filename);
}

int main() {
    int score = 2537;
    getPlayerName(score);
    return 0;
}
