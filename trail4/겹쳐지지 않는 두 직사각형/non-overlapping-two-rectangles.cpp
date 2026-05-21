#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int n, m;
vector<vector<long long>> board;
vector<vector<long long>> prefixSum;

long long getSum(int x1, int y1, int x2, int y2) {
    return prefixSum[x2 + 1][y2 + 1]
         - prefixSum[x1][y2 + 1]
         - prefixSum[x2 + 1][y1]
         + prefixSum[x1][y1];
}

int main() {
    cin>>n>>m;
    board.assign(n,vector<long long>(m));
    prefixSum.assign(n+1,vector<long long>(m+1,0));

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>board[i][j];
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            prefixSum[i + 1][j + 1] =
                prefixSum[i][j + 1]
              + prefixSum[i + 1][j]
              - prefixSum[i][j]
              + board[i][j];
        }
    }
    
    const long long NEG_INF = LLONG_MIN / 4;

    vector<long long> up(n, NEG_INF);
    vector<long long> down(n, NEG_INF);
    vector<long long> left(m, NEG_INF);
    vector<long long> right(m, NEG_INF);

    for (int x1 = 0; x1 < n; x1++) {
        for (int y1 = 0; y1 < m; y1++) {
            for (int x2 = x1; x2 < n; x2++) {
                for (int y2 = y1; y2 < m; y2++) {
                    long long sum = getSum(x1, y1, x2, y2);

                    up[x2] = max(up[x2], sum);
                    down[x1] = max(down[x1], sum);
                    left[y2] = max(left[y2], sum);
                    right[y1] = max(right[y1], sum);
                }
            }
        }
    }

    // up[i] = 0행 ~ i행 안에 완전히 포함되는 직사각형 중 최대 합
    for (int i = 1; i < n; i++) {
        up[i] = max(up[i], up[i - 1]);
    }

    // down[i] = i행 ~ n-1행 안에 완전히 포함되는 직사각형 중 최대 합
    for (int i = n - 2; i >= 0; i--) {
        down[i] = max(down[i], down[i + 1]);
    }

    // left[j] = 0열 ~ j열 안에 완전히 포함되는 직사각형 중 최대 합
    for (int j = 1; j < m; j++) {
        left[j] = max(left[j], left[j - 1]);
    }

    // right[j] = j열 ~ m-1열 안에 완전히 포함되는 직사각형 중 최대 합
    for (int j = m - 2; j >= 0; j--) {
        right[j] = max(right[j], right[j + 1]);
    }

    long long answer = NEG_INF;

    // 가로로 나누기
    for (int i = 0; i < n - 1; i++) {
        answer = max(answer, up[i] + down[i + 1]);
    }

    // 세로로 나누기
    for (int j = 0; j < m - 1; j++) {
        answer = max(answer, left[j] + right[j + 1]);
    }

    cout << answer << '\n';

    return 0;
}