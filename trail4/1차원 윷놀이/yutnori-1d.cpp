#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int n,m,k;
int ans = 0;

vector<int> moveCnt;
vector<int> position;

void dfs(int turn){
    if(turn==n){
        int score=0;
        for(int &p : position){
            if(p>=m){
                score++;
            }
        }
        ans=max(ans,score);
        return;
    }

    set<int> usedPosition;

    for(int horse=0;horse<k;horse++){
        if(usedPosition.count(position[horse])){
            continue;
        }

        usedPosition.insert(position[horse]);

        int prePosition=position[horse];
        position[horse]+=moveCnt[turn];
        position[horse]=min(position[horse],m);

        dfs(turn+1);

        position[horse]=prePosition;
    }
}

int main() {
    cin>>n>>m>>k;

    moveCnt.resize(n);
    position.assign(k,1);

    for(int i=0;i<n;i++){
        cin>>moveCnt[i];
    }

    dfs(0);

    cout<<ans<<"\n";

    return 0;
}