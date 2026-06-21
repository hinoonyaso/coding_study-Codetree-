#include <iostream>
#include <vector>
using namespace std;

int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int n, m;

vector<vector<vector<int>>> board;
vector<pair<int, int>> pos;

bool inRange(int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < n;
}

void moveNum(int num) {
    auto [r, c] = pos[num];

    vector<int>& source = board[r][c];

    // source에서 num의 위치 찾기
    int idx = 0;

    while (idx < static_cast<int>(source.size())
           && source[idx] != num) {
        idx++;
    }

    int maxNum = -1;
    int targetR = -1;
    int targetC = -1;

    // 주변 8칸 탐색
    for (int d = 0; d < 8; d++) {
        int nr = r + dr[d];
        int nc = c + dc[d];

        if (!inRange(nr, nc)) {
            continue;
        }

        // 해당 칸에 쌓여 있는 모든 숫자 확인
        for (int value : board[nr][nc]) {
            if (value > maxNum) {
                maxNum = value;
                targetR = nr;
                targetC = nc;
            }
        }
    }

    // 주변 8칸에 숫자가 없는 경우
    if (targetR == -1) {
        return;
    }

    // num과 num 위에 있는 숫자들을 분리
    vector<int> moving(
        source.begin(),
        source.begin() + idx + 1
    );

    // 원래 칸에서 제거
    source.erase(
        source.begin(),
        source.begin() + idx + 1
    );

    vector<int>& destination = board[targetR][targetC];

    // 목적지의 기존 숫자들 위에 삽입
    destination.insert(
        destination.begin(),
        moving.begin(),
        moving.end()
    );

    // 이동한 숫자들의 위치 갱신
    for (int value : moving) {
        pos[value] = {targetR, targetC};
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    board.assign(
        n,
        vector<vector<int>>(n)
    );

    pos.assign(
        n * n + 1,
        {-1, -1}
    );

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int num;
            cin >> num;

            board[i][j].push_back(num);
            pos[num] = {i, j};
        }
    }

    for (int i = 0; i < m; i++) {
        int num;
        cin >> num;

        moveNum(num);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j].empty()) {
                cout << "None\n";
                continue;
            }

            for (int num : board[i][j]) {
                cout << num << ' ';
            }

            cout << '\n';
        }
    }

    return 0;
}