#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;

int getSum(vector<vector<int>>& prefix, int x1, int y1, int x2, int y2) {
    return prefix[x2 + 1][y2 + 1]
         - prefix[x1][y2 + 1]
         - prefix[x2 + 1][y1]
         + prefix[x1][y1];
}

int main() {
    cin >> n >> m;

    vector<vector<int>> board(n, vector<int>(m));
    vector<vector<int>> bad(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];

            if (board[i][j] <= 0) {
                bad[i][j] = 1;
            }
        }
    }

    // prefix[i + 1][j + 1] = (0,0)부터 (i,j)까지 bad 개수
    vector<vector<int>> prefix(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            prefix[i + 1][j + 1] =
                prefix[i][j + 1]
              + prefix[i + 1][j]
              - prefix[i][j]
              + bad[i][j];
        }
    }

    int ans = -1;

    // 좌상단 (x1, y1), 우하단 (x2, y2) 완전탐색
    for (int x1 = 0; x1 < n; x1++) {
        for (int y1 = 0; y1 < m; y1++) {
            for (int x2 = x1; x2 < n; x2++) {
                for (int y2 = y1; y2 < m; y2++) {

                    int badCount = getSum(prefix, x1, y1, x2, y2);

                    if (badCount == 0) {
                        int area = (x2 - x1 + 1) * (y2 - y1 + 1);
                        ans = max(ans, area);
                    }
                }
            }
        }
    }

    cout << ans << '\n';

    return 0;
}