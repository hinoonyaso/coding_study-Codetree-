#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m, r, c;
    cin >> n >> m >> r >> c;

    // 입력은 1번부터 시작하므로 0-index로 변경
    r--;
    c--;

    vector<vector<bool>> hasBomb(
        n,
        vector<bool>(n, false)
    );

    vector<pair<int, int>> bombs;

    // 상, 하, 좌, 우
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    bombs.push_back({r, c});
    hasBomb[r][c] = true;

    long long dist = 1;

    for (int time = 1; time <= m; time++) {
        /*
         * 거리가 n 이상이면 어떤 위치에서 움직여도
         * 격자 내부에 새로운 폭탄을 만들 수 없다.
         * 이후 거리는 계속 커지므로 종료해도 된다.
         */
        if (dist >= n) {
            break;
        }

        // 이번 초가 시작될 때 존재했던 폭탄 개수
        int bombCount = bombs.size();

        for (int i = 0; i < bombCount; i++) {
            int row = bombs[i].first;
            int col = bombs[i].second;

            for (int dir = 0; dir < 4; dir++) {
                long long nextRow = row + dr[dir] * dist;
                long long nextCol = col + dc[dir] * dist;

                // 격자를 벗어난 경우
                if (nextRow < 0 || nextRow >= n ||
                    nextCol < 0 || nextCol >= n) {
                    continue;
                }

                // 이미 폭탄이 있는 경우
                if (hasBomb[nextRow][nextCol]) {
                    continue;
                }

                hasBomb[nextRow][nextCol] = true;
                bombs.push_back({
                    static_cast<int>(nextRow),
                    static_cast<int>(nextCol)
                });
            }
        }

        dist *= 2;
    }

    cout << bombs.size() << '\n';

    return 0;
}