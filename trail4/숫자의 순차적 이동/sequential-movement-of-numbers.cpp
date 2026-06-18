#include <iostream>
#include <vector>
using namespace std;

int n, m;

vector<vector<int>> board;
vector<pair<int, int>> pos;

int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool inRange(int r,int c){
    return 0 <= r && r < n && 0 <= c && c < n; 
}

void moveNum(int num){
    auto [r,c]=pos[num];
    int maxValue=-1;
    int maxR=-1,maxC=-1;
    for(int d=0;d<8;d++){
        int nr=r+dr[d];
        int nc=c+dc[d];

        if(!inRange(nr,nc)) continue;

        if(maxValue<board[nr][nc]){
            maxValue=board[nr][nc];
            maxR=nr;
            maxC=nc;
        }
    }
    if(maxR==-1) return;

    int otherNum=board[maxR][maxC];
    swap(board[r][c],board[maxR][maxC]);

    pos[num]={maxR,maxC};
    pos[otherNum]={r,c};
}

int main() {
    cin>>n>>m;

    board.assign(n,vector<int>(n));
    pos.resize(n*n+1);

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>board[i][j];
            int num=board[i][j];
            pos[num]={i,j};
        }
    }

    for(int time=0;time<m;time++){
        for(int i=1;i<=n*n;i++){
            moveNum(i);
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}