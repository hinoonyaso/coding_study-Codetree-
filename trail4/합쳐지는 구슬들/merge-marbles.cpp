#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Ball {
    int r;
    int c;
    int dir;
    long long weight;
    int number;
};

int n, m, t;

// U, R, D, L
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

bool inRange(int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < n;
}

int getDir(char dir) {
    if (dir == 'U') return 0;
    if (dir == 'R') return 1;
    if (dir == 'D') return 2;
    return 3; // L
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> t;

    vector<Ball> balls;

    for (int number = 1; number <= m; number++) {
        int r, c, weight;
        char dir;

        cin >> r >> c >> dir >> weight;

        balls.push_back({
            r - 1,
            c - 1,
            getDir(dir),
            weight,
            number
        });
    }

    for (int time = 0; time < t; time++) {

        // 이동 후 각 칸에 도착한 구슬들을 저장한다.
        vector<vector<vector<Ball>>> nextBoard(
            n,
            vector<vector<Ball>>(n)
        );

        // 1. 모든 구슬 이동 또는 방향 전환
        for (Ball ball : balls) {
            int nr = ball.r + dr[ball.dir];
            int nc = ball.c + dc[ball.dir];

            if (!inRange(nr, nc)) {
                // 벽에 부딪히면 이동하지 않고 방향만 전환한다.
                ball.dir = (ball.dir + 2) % 4;
            } else {
                ball.r = nr;
                ball.c = nc;
            }

            nextBoard[ball.r][ball.c].push_back(ball);
        }

        balls.clear();

        // 2. 같은 칸에 있는 구슬들을 합친다.
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (nextBoard[r][c].empty()) {
                    continue;
                }

                long long totalWeight = 0;
                int maxNumber = -1;
                int nextDir = -1;

                for (const Ball& ball : nextBoard[r][c]) {
                    totalWeight += ball.weight;

                    if (ball.number > maxNumber) {
                        maxNumber = ball.number;
                        nextDir = ball.dir;
                    }
                }

                balls.push_back({
                    r,
                    c,
                    nextDir,
                    totalWeight,
                    maxNumber
                });
            }
        }
    }

    long long maxWeight = 0;

    for (const Ball& ball : balls) {
        maxWeight = max(maxWeight, ball.weight);
    }

    cout << balls.size() << ' ' << maxWeight;

    return 0;
}