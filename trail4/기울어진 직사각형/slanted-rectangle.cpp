#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> board;

int dx[4]={-1,-1,1,1};
int dy[4]={1,-1,-1,1};

bool inRange(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

int getSum(int sx,int sy,int len1,int len2){
    int moveCnt[4]={len1,len2,len1,len2};

    int x = sx;
    int y = sy;
    int sum = 0;

    for(int dir=0;dir<4;dir++){
        for(int step=0;step<moveCnt[dir];step++){
            x+=dx[dir];
            y+=dy[dir];

            if (!inRange(x, y)) {
                return -1;
            }

            sum+=board[x][y];
        }
    }
    return sum;
}

int main(){
    cin>>n;
    board.resize(n,vector<int>(n));

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>board[i][j];
        }
    }

    int ans=0;
    for(int x=0;x<n;x++){
        for(int y=0;y<n;y++){
            for(int len1=1;len1<n;len1++){
                for(int len2=1;len2<n;len2++){
                    int sum=getSum(x,y,len1,len2);

                    if(sum!=-1) ans=max(ans,sum);
                }
            }
        }
    }

    cout<<ans<<"\n";

    return 0;
}