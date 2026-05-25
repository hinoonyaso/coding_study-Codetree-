#include <iostream>
#include <vector>
using namespace std;

int n, m, q;
vector<vector<int>> board;

char opposite(char dir) {
    return dir == 'L' ? 'R' : 'L';
}

void shiftRow(int row, char dir) {
    if (dir == 'L') {
        int temp = board[row][0];

        for (int j = 0; j < m - 1; j++) {
            board[row][j] = board[row][j + 1];
        }

        board[row][m - 1] = temp;
    } 
    else {
        int temp = board[row][m - 1];

        for (int j = m - 1; j >= 1; j--) {
            board[row][j] = board[row][j - 1];
        }

        board[row][0] = temp;
    }
}

bool canSpread(int r1, int r2) {
    for (int j = 0; j < m; j++) {
        if (board[r1][j] == board[r2][j]) {
            return true;
        }
    }

    return false;
}

int main() {
    cin >> n >> m >> q;

    board.resize(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    while (q--) {
        int r;
        char dir;
        cin >> r >> dir;

        r--;

        // 입력 방향은 바람이 불어오는 방향.
        // 실제 shift 방향은 반대.
        dir = opposite(dir);

        // 1. 바람이 직접 분 행 shift
        shiftRow(r, dir);

        // 2. 위쪽 전파
        char curDir = dir;

        for (int row = r - 1; row >= 0; row--) {
            if (!canSpread(row + 1, row)) {
                break;
            }

            curDir = opposite(curDir);
            shiftRow(row, curDir);
        }

        // 3. 아래쪽 전파
        curDir = dir;

        for (int row = r + 1; row < n; row++) {
            if (!canSpread(row - 1, row)) {
                break;
            }

            curDir = opposite(curDir);
            shiftRow(row, curDir);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << board[i][j] << " ";
        }
        cout << '\n';
    }

    return 0;
}