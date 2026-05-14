#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int ans = 0;

vector<pair<int, int>> lines;
vector<pair<int, int>> selected;

bool isOverlap(pair<int, int> a, pair<int, int> b) {
    int x1 = a.first;
    int x2 = a.second;
    int y1 = b.first;
    int y2 = b.second;

    // 끝점이 같아도 겹친 것으로 봄
    if (x2 < y1 || y2 < x1) {
        return false;
    }

    return true;
}

bool canSelect(pair<int, int> cur){
    for (int i = 0; i < selected.size(); i++) {
        if (isOverlap(selected[i], cur)) {
            return false;
        }
    }

    return true;
}

void dfs(int idx){
    if(idx==n){
        ans=max(ans,(int)selected.size());
        return;
    }
    dfs(idx+1);

    if(canSelect(lines[idx])){
        selected.push_back(lines[idx]);
        dfs(idx+1);
        selected.pop_back();
    }
}

int main() {
    cin>>n;

    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        lines.push_back({x,y});
    }

    dfs(0);

    cout<<ans<<"\n";
    return 0;
}