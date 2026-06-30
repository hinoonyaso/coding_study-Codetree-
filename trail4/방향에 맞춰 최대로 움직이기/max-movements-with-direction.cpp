#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;

vector<vector<int>> board;
vector<vector<int>> direction;
vector<vector<int>> dp;

int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

bool inRange(int r, int c) {
    return 0 <= r && r < n &&
           0 <= c && c < n;
}

int dfs(int r, int c){
    if (dp[r][c] != -1) {
        return dp[r][c];
    }

    dp[r][c] = 0;

    int dir = direction[r][c] - 1;

    int nr = r + dr[dir];
    int nc = c + dc[dir];

    while (inRange(nr, nc)) {
        if (board[nr][nc] > board[r][c]) {
            dp[r][c] = max(dp[r][c],1 + dfs(nr, nc));
        }

        nr += dr[dir];
        nc += dc[dir];
    }

    return dp[r][c];
}

int main() {
    cin>>n;

    board.assign(n,vector<int>(n));
    direction.assign(n,vector<int>(n));
    dp.assign(n, vector<int>(n, -1));

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> board[r][c];
        }
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> direction[r][c];
        }
    }

    int startR,startC;
    cin>>startR>>startC;

    startR--;
    startC--;

    cout << dfs(startR, startC);

    return 0;
}