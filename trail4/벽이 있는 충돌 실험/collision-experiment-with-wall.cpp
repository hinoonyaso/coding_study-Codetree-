#include <iostream>
#include <vector>
using namespace std;

int n,m;

struct Ball{
    int r,c;
    int dir;
};

int dr[4]={-1,0,1,0};
int dc[4]={0,1,0,-1};

bool inRange(int r,int c,int n){
    return 0 <= r && r < n && 0 <= c && c < n; 
}

int getDir(char dir){
    if(dir=='U') return 0;
    else if(dir=='R') return 1;
    else if(dir=='D') return 2;
    return 3;
}

int main() {
    int t;
    cin>>t;
    
    while(t--){
        cin>>n>>m;

        vector<Ball> balls;

        for(int i=0;i<m;i++){
            int r,c;
            char dir;

            cin>>r>>c>>dir;
            balls.push_back({r-1,c-1,getDir(dir)});
        }

        for(int time=0;time<2*n;time++){
            for(Ball &ball : balls){
                int nr=ball.r + dr[ball.dir];
                int nc=ball.c + dc[ball.dir];

                if(inRange(nr, nc, n)){
                    ball.r=nr;
                    ball.c=nc;
                }
                else{
                    ball.dir=(ball.dir+2) % 4;
                }
            }
            vector<vector<int>> count(n,vector<int>(n,0));
            for(const Ball &ball : balls){
                count[ball.r][ball.c]++;
            }

            vector<Ball> survived;
            for (const Ball& ball : balls) {
                if (count[ball.r][ball.c] == 1) {
                    survived.push_back(ball);
                }
            }
            balls = survived;
        }
        cout << balls.size() << '\n';
    }
    return 0;
}