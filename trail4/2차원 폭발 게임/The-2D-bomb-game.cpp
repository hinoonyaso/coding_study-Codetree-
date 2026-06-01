#include <iostream>
#include <vector>
using namespace std;

int n, m, k;
vector<vector<int>> board;

void applyGravity() {
    vector<vector<int>> temp(n, vector<int>(n, 0));

    for (int col = 0; col < n; col++) {
        int writeRow = n - 1;

        for (int row = n - 1; row >= 0; row--) {
            if (board[row][col] != 0) {
                temp[writeRow][col] = board[row][col];
                writeRow--;
            }
        }
    }

    board = temp;
}

bool explodeOnce() {
    vector<vector<bool>> boom(n, vector<bool>(n, false));
    bool exploded = false;

    for (int col = 0; col < n; col++) {
        int row = 0;

        while (row < n) {
            if (board[row][col] == 0) {
                row++;
                continue;
            }

            int start = row;
            int value = board[row][col];

            while (row < n && board[row][col] == value) {
                row++;
            }

            int length = row - start;

            if (length >= m) {
                exploded = true;

                for (int r = start; r < row; r++) {
                    boom[r][col] = true;
                }
            }
        }
    }

    if (!exploded) {
        return false;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (boom[i][j]) {
                board[i][j] = 0;
            }
        }
    }

    return true;
}

void explodeRepeatedly() {
    while (true) {
        bool exploded = explodeOnce();

        if (!exploded) {
            break;
        }

        applyGravity();
    }
}

void rotateClockwise() {
    vector<vector<int>> temp(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp[j][n - 1 - i] = board[i][j];
        }
    }

    board = temp;

    applyGravity();
}

int countBombs() {
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] != 0) {
                cnt++;
            }
        }
    }

    return cnt;
}

int main() {
    cin >> n >> m >> k;

    board.resize(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }

    for (int turn = 0; turn < k; turn++) {
        explodeRepeatedly();
        rotateClockwise();
    }

    explodeRepeatedly();

    cout << countBombs() << '\n';

    return 0;
}