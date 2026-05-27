#include <iostream>
#include <vector>
using namespace std;

int n, m, q;
vector<vector<int>> board;

int dx[5] = {0, -1, 1, 0, 0};
int dy[5] = {0, 0, 0, -1, 1};

bool inRange(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void rotateClockwise(int r1, int c1, int r2, int c2) {
    vector<pair<int, int>> path;

    // 위쪽: 왼쪽 -> 오른쪽
    for (int y = c1; y <= c2; y++) {
        path.push_back({r1, y});
    }

    // 오른쪽: 위 -> 아래
    for (int x = r1 + 1; x <= r2; x++) {
        path.push_back({x, c2});
    }

    // 아래쪽: 오른쪽 -> 왼쪽
    for (int y = c2 - 1; y >= c1; y--) {
        path.push_back({r2, y});
    }

    // 왼쪽: 아래 -> 위
    for (int x = r2 - 1; x > r1; x--) {
        path.push_back({x, c1});
    }

    vector<int> values;

    for (auto [x, y] : path) {
        values.push_back(board[x][y]);
    }

    int len = path.size();

    // 시계 방향으로 한 칸 이동
    for (int i = 0; i < len; i++) {
        int nextIdx = (i + 1) % len;
        int nx = path[nextIdx].first;
        int ny = path[nextIdx].second;

        board[nx][ny] = values[i];
    }
}

void averageRectangle(int r1, int c1, int r2, int c2) {
    vector<vector<int>> temp = board;

    for (int x = r1; x <= r2; x++) {
        for (int y = c1; y <= c2; y++) {
            int sum = 0;
            int cnt = 0;

            for (int dir = 0; dir < 5; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                if (inRange(nx, ny)) {
                    sum += temp[nx][ny];
                    cnt++;
                }
            }

            board[x][y] = sum / cnt;
        }
    }
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
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        // 문제 입력은 1-indexed이므로 0-indexed로 변환
        r1--;
        c1--;
        r2--;
        c2--;

        rotateClockwise(r1, c1, r2, c2);
        averageRectangle(r1, c1, r2, c2);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << board[i][j] << " ";
        }
        cout << '\n';
    }

    return 0;
}