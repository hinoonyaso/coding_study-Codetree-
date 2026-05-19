#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int n,m;
vector<vector<int>> board;

int getCost(int k){
    return k*k+(k+1)*(k+1);
}

int countGold(int x,int y,int k){
    int cnt=0;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int dist=abs(x-i)+abs(y-j);
            if(dist<=k) cnt+=board[i][j];
        }
    }

    return cnt;
}

int main() {
    cin>>n>>m;

    board.resize(n,vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>board[i][j];
        }
    }

    int ans=0;

    for(int x=0;x<n;x++){
        for(int y=0;y<n;y++){
            for(int k=0;k<=2*n;k++){
                int gold=countGold(x,y,k);
                int cost=getCost(k);

                if(gold*m>=cost){
                    ans=max(ans,gold);
                }
            }
        }
    }

    cout<<ans<<"\n";

    return 0;
}