#include <iostream>
#include <vector>
using namespace std;

int board[4][4];
int resultBoard[4][4];
char dir;

vector<int> mergeLine(vector<int> line) {
    vector<int> merged;

    for (int i = 0; i < (int)line.size(); i++) {
        if (i + 1 < (int)line.size() && line[i] == line[i + 1]) {
            merged.push_back(line[i] * 2);
            i++; // 바로 다음 숫자는 이미 합쳐졌으므로 건너뜀
        } else {
            merged.push_back(line[i]);
        }
    }

    return merged;
}

int main() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> board[i][j];
        }
    }

    cin >> dir;

    if (dir == 'L') {
        for (int r = 0; r < 4; r++) {
            vector<int> line;

            for (int c = 0; c < 4; c++) {
                if (board[r][c] != 0) {
                    line.push_back(board[r][c]);
                }
            }

            vector<int> merged = mergeLine(line);

            for (int c = 0; c < (int)merged.size(); c++) {
                resultBoard[r][c] = merged[c];
            }
        }
    }

    else if (dir == 'R') {
        for (int r = 0; r < 4; r++) {
            vector<int> line;

            for (int c = 3; c >= 0; c--) {
                if (board[r][c] != 0) {
                    line.push_back(board[r][c]);
                }
            }

            vector<int> merged = mergeLine(line);

            for (int i = 0; i < (int)merged.size(); i++) {
                resultBoard[r][3 - i] = merged[i];
            }
        }
    }

    else if (dir == 'U') {
        for (int c = 0; c < 4; c++) {
            vector<int> line;

            for (int r = 0; r < 4; r++) {
                if (board[r][c] != 0) {
                    line.push_back(board[r][c]);
                }
            }

            vector<int> merged = mergeLine(line);

            for (int r = 0; r < (int)merged.size(); r++) {
                resultBoard[r][c] = merged[r];
            }
        }
    }

    else if (dir == 'D') {
        for (int c = 0; c < 4; c++) {
            vector<int> line;

            for (int r = 3; r >= 0; r--) {
                if (board[r][c] != 0) {
                    line.push_back(board[r][c]);
                }
            }

            vector<int> merged = mergeLine(line);

            for (int i = 0; i < (int)merged.size(); i++) {
                resultBoard[3 - i][c] = merged[i];
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << resultBoard[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}