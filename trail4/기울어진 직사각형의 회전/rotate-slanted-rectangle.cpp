#include <iostream>
#include <vector>
using namespace std;

int n;
int board[105][105];

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }

    int r, c, m1, m2, m3, m4, dir;
    cin >> r >> c >> m1 >> m2 >> m3 >> m4 >> dir;

    // 0-index로 변환
    int x = r - 1;
    int y = c - 1;

    vector<pair<int, int>> path;

    int dx[4] = {-1, -1, 1, 1};
    int dy[4] = {1, -1, -1, 1};
    int moveCnt[4] = {m1, m2, m3, m4};

    // 경계 좌표 저장
    // 현재 칸을 저장하고, 그 다음 칸으로 이동한다.
    // 마지막 이동 후에는 시작점으로 돌아오므로 중복 저장되지 않는다.
    for (int d = 0; d < 4; d++) {
        for (int k = 0; k < moveCnt[d]; k++) {
            path.push_back({x, y});
            x += dx[d];
            y += dy[d];
        }
    }

    vector<int> values;

    for (auto [px, py] : path) {
        values.push_back(board[px][py]);
    }

    int len = path.size();

    if (dir == 0) {
        // 반시계 방향 회전
        // path 순서 자체가 반시계 순회이므로 i번째 값이 i+1 위치로 간다.
        for (int i = 0; i < len; i++) {
            int next = (i + 1) % len;
            int nx = path[next].first;
            int ny = path[next].second;

            board[nx][ny] = values[i];
        }
    } else {
        // 시계 방향 회전
        // i번째 값이 i-1 위치로 간다.
        for (int i = 0; i < len; i++) {
            int prev = (i - 1 + len) % len;
            int nx = path[prev].first;
            int ny = path[prev].second;

            board[nx][ny] = values[i];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}