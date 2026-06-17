#include <iostream>
#include <vector>
using namespace std;

int n,m,t;
vector<vector<int>> board;

int dr[4]={-1,1,0,0};
int dc[4]={0,0,-1,1};

bool inRange(int r, int c) {
    return 0 <= r && r < n &&
           0 <= c && c < n;
}

int main() {
    cin>>n>>m>>t;
    board.assign(n,vector<int>(n));

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>board[i][j];
        }
    }

    vector<pair<int,int>> balls;
    for(int i=0;i<m;i++){
        int r,c;
        cin>>r>>c;
        r--;
        c--;
        balls.push_back({r,c});
    }

    for(int time=0;time<t;time++){
        vector<vector<int>> count(n, vector<int>(n, 0));
        vector<pair<int, int>> movedBalls;

        for(auto [r,c] : balls){
            int maxValue=-1;
            int nextR,nextC;
            for(int d=0;d<4;d++){
                int nr=r+dr[d];
                int nc=c+dc[d];

                if (!inRange(nr, nc)) {
                    continue;
                }

                if(maxValue<board[nr][nc]){
                    nextR=nr;
                    nextC=nc;
                    maxValue=board[nr][nc];
                }
            }
            movedBalls.push_back({nextR, nextC});
            count[nextR][nextC]++;
        }

        vector<pair<int, int>> nextBalls;

        for (auto [r, c] : movedBalls) {
            if (count[r][c] == 1) {
                nextBalls.push_back({r, c});
            }
        }

        balls = nextBalls;
    }

    cout << balls.size();
    return 0;
}