#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int ans = 0;

vector<pair<int, int>> bombs;
int destroyed[25][25];

int dx[3][5]={
    {-2,-1,0,1,2},
    {-1,0,0,0,1},
    {-1,-1,0,1,1}
};

int dy[3][5]={
    {0,0,0,0,0},
    {0,-1,0,1,0},
    {-1,1,0,-1,1}
};

bool isRange(int x,int y){
    return x >= 0 && x < n && y >= 0 && y < n;
}

void dfs(int idx,int cnt){
    if(idx==bombs.size()){
        ans=max(ans,cnt);
        return;
    }

    int x=bombs[idx].first;
    int y=bombs[idx].second;

    for(int type=0;type<3;type++){
        int added = 0;
        vector<pair<int, int>> changed;
        for(int dir=0;dir<5;dir++){
            int nx=x+dx[type][dir];
            int ny=y+dy[type][dir];

            if(!isRange(nx,ny)) continue;

            if(destroyed[nx][ny]==0){
                added++;
            }

            destroyed[nx][ny]++;
            changed.push_back({nx,ny});
        }
        dfs(idx + 1, cnt + added);

        for (auto pos : changed) {
            int cx = pos.first;
            int cy = pos.second;

            destroyed[cx][cy]--;
        }
    }
}

int main() {
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int x;
            cin>>x;
            if(x==1) bombs.push_back({i,j});
        }
    }

    dfs(0,0);

    cout<<ans<<"\n";

    return 0;
}