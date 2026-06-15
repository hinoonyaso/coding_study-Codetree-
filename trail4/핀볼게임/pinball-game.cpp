#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> board;

// 0: 위, 1: 오른쪽, 2: 아래, 3: 왼쪽
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

bool inRange(int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < n;
}

int simulate(int r, int c, int dir) {
    int elapsedTime = 0;

    while (true) {
        // 한 칸 이동
        r += dr[dir];
        c += dc[dir];
        elapsedTime++;

        // 격자 밖으로 나가면 종료
        if (!inRange(r, c)) {
            return elapsedTime;
        }

        // '/' 모양 거울
        if (board[r][c] == 1) {
            dir ^= 1;
        }
        // '\' 모양 거울
        else if (board[r][c] == 2) {
            dir ^= 3;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    board.assign(n, vector<int>(n));

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> board[r][c];
        }
    }

    int answer = 0;

    for (int i = 0; i < n; i++) {
        // 위쪽에서 아래 방향으로 진입
        answer = max(answer, simulate(-1, i, 2));

        // 아래쪽에서 위 방향으로 진입
        answer = max(answer, simulate(n, i, 0));

        // 왼쪽에서 오른쪽 방향으로 진입
        answer = max(answer, simulate(i, -1, 1));

        // 오른쪽에서 왼쪽 방향으로 진입
        answer = max(answer, simulate(i, n, 3));
    }

    cout << answer << '\n';

    return 0;
}