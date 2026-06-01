#include <iostream>
#include <vector>
using namespace std;

int n;
vector<vector<int>> board;

bool inRange(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

void explode(int r, int c) {
    int power = board[r][c];

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    // 중심 칸 제거
    board[r][c] = 0;

    // 상하좌우 제거
    for (int dir = 0; dir < 4; dir++) {
        for (int dist = 1; dist < power; dist++) {
            int nx = r + dx[dir] * dist;
            int ny = c + dy[dir] * dist;

            if (inRange(nx, ny)) {
                board[nx][ny] = 0;
            }
        }
    }
}

void gravity() {
    for (int col = 0; col < n; col++) {
        vector<int> temp;

        // 아래에서 위로 보면서 살아있는 숫자 저장
        for (int row = n - 1; row >= 0; row--) {
            if (board[row][col] != 0) {
                temp.push_back(board[row][col]);
            }
        }

        // 일단 해당 열을 전부 0으로 초기화
        for (int row = 0; row < n; row++) {
            board[row][col] = 0;
        }

        // 아래부터 다시 채우기
        int row = n - 1;
        for (int value : temp) {
            board[row][col] = value;
            row--;
        }
    }
}

int main() {
    cin >> n;

    board.resize(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }

    int r, c;
    cin >> r >> c;

    // 문제 좌표는 보통 1-indexed이므로 0-indexed로 변환
    r--;
    c--;

    explode(r, c);
    gravity();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << '\n';
    }

    return 0;
}