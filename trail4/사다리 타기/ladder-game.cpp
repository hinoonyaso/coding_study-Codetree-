#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n,m;
int ans=1e9;
vector<pair<int, int>> lines; 

vector<bool> selected;
vector<int> targetResult;

vector<int> simulate(bool useSelectedOnly){
    vector<int> result(n+1);

    for(int i=1;i<=n;i++){
        result[i]=i;
    }
    for(int i=0;i<m;i++){
        if(useSelectedOnly && !selected[i]){
            continue;
        }

        int pos=lines[i].second;
        swap(result[pos],result[pos+1]);
    }
    return result;
}

void backtracking(int idx,int cnt){
    if(cnt>=ans){
        return;
    }

    if(idx==m){
        vector<int> currentResult=simulate(true);

        if(currentResult == targetResult){
            ans=min(ans,cnt);
        }
        return;
    }

    selected[idx]=true;
    backtracking(idx+1,cnt+1);

    selected[idx]=false;
    backtracking(idx+1,cnt);
}

int main() {
    cin>>n>>m;
    selected.resize(m, false);

    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;

        lines.push_back({b,a});
    }
    sort(lines.begin(),lines.end());

    targetResult=simulate(false);
    backtracking(0,0);

    cout<<ans<<"\n";

    return 0;
}