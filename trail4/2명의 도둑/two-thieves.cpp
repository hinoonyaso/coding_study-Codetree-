#include <iostream>
#include <algorithm>
using namespace std;

int n, m, c;
int board[11][11];
int best[11][11];

int getMaxValue(int row, int startCol) {
    int maxValue = 0;

    for (int mask = 0; mask < (1 << m); mask++) {
        int weightSum = 0;
        int valueSum = 0;

        for (int i = 0; i < m; i++) {
            if (mask & (1 << i)) {
                int w = board[row][startCol + i];
                weightSum += w;
                valueSum += w * w;
            }
        }

        if (weightSum <= c) {
            maxValue = max(maxValue, valueSum);
        }
    }

    return maxValue;
}

bool isOverlap(int c1, int c2) {
    int end1 = c1 + m - 1;
    int end2 = c2 + m - 1;

    return !(end1 < c2 || end2 < c1);
}

int main() {
    cin >> n >> m >> c;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }

    for (int row = 0; row < n; row++) {
        for (int col = 0; col <= n - m; col++) {
            best[row][col] = getMaxValue(row, col);
        }
    }

    int ans = 0;

    for (int r1 = 0; r1 < n; r1++) {
        for (int c1 = 0; c1 <= n - m; c1++) {

            for (int r2 = 0; r2 < n; r2++) {
                for (int c2 = 0; c2 <= n - m; c2++) {

                    if (r1 == r2 && isOverlap(c1, c2)) {
                        continue;
                    }

                    ans = max(ans, best[r1][c1] + best[r2][c2]);
                }
            }
        }
    }

    cout << ans << '\n';

    return 0;
}