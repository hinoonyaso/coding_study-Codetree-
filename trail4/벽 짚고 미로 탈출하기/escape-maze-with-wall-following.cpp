#include <iostream>
#include <vector>
using namespace std;

int n;
int x, y;
vector<string> board;

int dx[4] = {0, 1, 0, -1};  // 오른쪽, 아래, 왼쪽, 위
int dy[4] = {1, 0, -1, 0};

bool inRange(int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < n;
}

int main() {
    cin >> n;
    cin >> x >> y;

    x--;
    y--;

    board.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> board[i];
    }

    vector<vector<vector<bool>>> visited(
        n, vector<vector<bool>>(n, vector<bool>(4, false))
    );

    int dir = 0;      // 처음에는 오른쪽 방향
    int answer = 0;   // 실제 이동한 칸 수

    while (true) {
        // 같은 위치 + 같은 방향이 다시 나오면 무한 반복
        if (visited[x][y][dir]) {
            cout << -1 << "\n";
            return 0;
        }

        visited[x][y][dir] = true;

        int nx = x + dx[dir];
        int ny = y + dy[dir];

        // Case 1: 앞이 격자 밖이면 한 칸 이동해서 탈출
        if (!inRange(nx, ny)) {
            cout << answer + 1 << "\n";
            return 0;
        }

        // Step 1: 앞이 벽이면 반시계 방향 회전
        if (board[nx][ny] == '#') {
            dir = (dir + 3) % 4;
            continue;
        }

        // 여기까지 왔으면 앞칸은 빈칸
        int rightDir = (dir + 1) % 4;
        int rx = nx + dx[rightDir];
        int ry = ny + dy[rightDir];

        // Case 2: 앞으로 갔을 때 오른쪽에 벽이 있다면 한 칸만 이동
        if (inRange(rx, ry) && board[rx][ry] == '#') {
            x = nx;
            y = ny;
            answer++;
        }
        // Case 3: 오른쪽에 벽이 없다면 앞으로 이동 후 오른쪽으로 꺾고 한 칸 더 이동
        else {
            // 먼저 현재 방향으로 한 칸 이동
            x = nx;
            y = ny;
            answer++;

            // 시계 방향 회전
            dir = rightDir;

            int nnx = x + dx[dir];
            int nny = y + dy[dir];

            // 두 번째 이동이 격자 밖이면 탈출
            if (!inRange(nnx, nny)) {
                cout << answer + 1 << "\n";
                return 0;
            }

            x = nnx;
            y = nny;
            answer++;
        }
    }

    return 0;
}