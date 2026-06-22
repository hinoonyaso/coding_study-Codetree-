#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Marble {
    int id;     // 구슬 번호
    int r, c;   // 현재 위치
    int dir;    // 이동 방향
    int v;      // 속도
};

int n, m, t, k;

// U, D, L, R
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool inRange(int r, int c) {
    return 0 <= r && r < n &&
           0 <= c && c < n;
}

int getDir(char dir) {
    if (dir == 'U') return 0;
    if (dir == 'D') return 1;
    if (dir == 'L') return 2;
    return 3;  // R
}

// 한 구슬을 1초 동안 이동
void moveMarble(Marble& marble) {
    for (int move = 0; move < marble.v; move++) {
        int nr = marble.r + dr[marble.dir];
        int nc = marble.c + dc[marble.dir];

        // 벽에 부딪히면 즉시 반대 방향으로 전환
        if (!inRange(nr, nc)) {
            marble.dir ^= 1;

            nr = marble.r + dr[marble.dir];
            nc = marble.c + dc[marble.dir];
        }

        marble.r = nr;
        marble.c = nc;
    }
}

// 우선순위가 높은 구슬이 앞으로 오도록 정렬
bool compareMarble(const Marble& a, const Marble& b) {
    if (a.v != b.v) {
        return a.v > b.v;
    }

    return a.id > b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> t >> k;

    vector<Marble> marbles;

    for (int id = 1; id <= m; id++) {
        int r, c, v;
        char dir;

        cin >> r >> c >> dir >> v;

        marbles.push_back({
            id,
            r - 1,
            c - 1,
            getDir(dir),
            v
        });
    }

    for (int time = 0; time < t; time++) {
        // 이동 후 각 칸에 도착한 구슬들을 저장
        vector<vector<vector<Marble>>> nextBoard(
            n,
            vector<vector<Marble>>(n)
        );

        // 1. 모든 구슬 이동
        for (Marble marble : marbles) {
            moveMarble(marble);
            nextBoard[marble.r][marble.c].push_back(marble);
        }

        // 2. 충돌 처리 후 살아남은 구슬 수집
        vector<Marble> nextMarbles;

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                vector<Marble>& cell = nextBoard[r][c];

                if (cell.empty()) {
                    continue;
                }

                sort(cell.begin(), cell.end(), compareMarble);

                int surviveCount =
                    min(k, static_cast<int>(cell.size()));

                for (int i = 0; i < surviveCount; i++) {
                    nextMarbles.push_back(cell[i]);
                }
            }
        }

        marbles = move(nextMarbles);
    }

    cout << marbles.size() << '\n';

    return 0;
}