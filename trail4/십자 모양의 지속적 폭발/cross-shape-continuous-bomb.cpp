#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<vector<int>> board;

bool inRange(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

void applyGravity() {
    vector<vector<int>> temp(n, vector<int>(n, 0));

    for (int c = 0; c < n; c++) {
        int writeRow = n - 1;

        for (int r = n - 1; r >= 0; r--) {
            if (board[r][c] != 0) {
                temp[writeRow][c] = board[r][c];
                writeRow--;
            }
        }
    }

    board = temp;
}

void explode(int col) {
    int row = -1;

    // 선택한 열에서 가장 위에 있는 숫자 찾기
    for (int r = 0; r < n; r++) {
        if (board[r][col] != 0) {
            row = r;
            break;
        }
    }

    // 해당 열에 폭탄이 없으면 변화 없음
    if (row == -1) return;

    int power = board[row][col];

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    // 중심 터뜨리기
    board[row][col] = 0;

    // 상하좌우 터뜨리기
    for (int dir = 0; dir < 4; dir++) {
        for (int dist = 1; dist < power; dist++) {
            int nr = row + dr[dir] * dist;
            int nc = col + dc[dir] * dist;

            if (inRange(nr, nc)) {
                board[nr][nc] = 0;
            }
        }
    }

    applyGravity();
}

int main() {
    cin >> n >> m;

    board.resize(n, vector<int>(n));

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> board[r][c];
        }
    }

    for (int i = 0; i < m; i++) {
        int col;
        cin >> col;
        col--; // 입력은 1번 열부터 시작하므로 0-index로 변환

        explode(col);
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cout << board[r][c] << " ";
        }
        cout << "\n";
    }

    return 0;
}