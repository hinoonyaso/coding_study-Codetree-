#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> board;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool inRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

void explode(vector<vector<int>>& temp, int x, int y) {
    int power = temp[x][y];

    temp[x][y] = 0;

    for (int dir = 0; dir < 4; dir++) {
        for (int dist = 1; dist < power; dist++) {
            int nx = x + dx[dir] * dist;
            int ny = y + dy[dir] * dist;

            if (inRange(nx, ny)) {
                temp[nx][ny] = 0;
            }
        }
    }
}

void applyGravity(vector<vector<int>>& temp) {
    for (int col = 0; col < n; col++) {
        vector<int> nums;

        for (int row = n - 1; row >= 0; row--) {
            if (temp[row][col] != 0) {
                nums.push_back(temp[row][col]);
            }
        }

        int idx = 0;

        for (int row = n - 1; row >= 0; row--) {
            if (idx < (int)nums.size()) {
                temp[row][col] = nums[idx++];
            } else {
                temp[row][col] = 0;
            }
        }
    }
}

int countPairs(const vector<vector<int>>& temp) {
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (temp[i][j] == 0) continue;

            if (j + 1 < n && temp[i][j] == temp[i][j + 1]) {
                cnt++;
            }

            if (i + 1 < n && temp[i][j] == temp[i + 1][j]) {
                cnt++;
            }
        }
    }

    return cnt;
}

int simulate(int x, int y) {
    vector<vector<int>> temp = board;

    explode(temp, x, y);
    applyGravity(temp);

    return countPairs(temp);
}

int main() {
    cin >> n;

    board.resize(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }

    int answer = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            answer = max(answer, simulate(i, j));
        }
    }

    cout << answer << '\n';

    return 0;
}