#include <iostream>
#include <vector>
using namespace std;

int n, r, c;
vector<vector<int>> board;

int dr[4] = {-1, 1, 0, 0}; // 상, 하, 좌, 우
int dc[4] = {0, 0, -1, 1};

bool inRange(int row, int col) {
    return row >= 1 && row <= n && col >= 1 && col <= n;
}

int main() {
    cin >> n >> r >> c;

    board.resize(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> board[i][j];
        }
    }

    while (true) {
        cout << board[r][c] << " ";

        bool moved = false;

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (!inRange(nr, nc)) {
                continue;
            }

            if (board[nr][nc] > board[r][c]) {
                r = nr;
                c = nc;
                moved = true;
                break;
            }
        }

        if (!moved) {
            break;
        }
    }

    return 0;
}