#include <iostream>
#include <vector>
using namespace std;

int k,n;
vector<int> selected;

void dfs(int depth){
    if(depth==n){
        for(int num : selected){
            cout<<num<<' ';
        }
        cout<<"\n";
        return;
    }

    for(int num=1;num<=k;num++){
        if(depth>=2 && selected[depth-1]==num && selected[depth-2]==num){
            continue;
        }

        selected.push_back(num);
        dfs(depth+1);
        selected.pop_back();
    }
}

int main() {
    cin>>k>>n;

    dfs(0);

    return 0;
}