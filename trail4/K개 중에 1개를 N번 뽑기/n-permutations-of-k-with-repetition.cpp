#include <iostream>
#include <vector>
using namespace std;

int k,n;
vector<int> result;

void dfs(int depth){
    if(depth==n){
        for (int i = 0; i < n; i++) {
            cout << result[i] << " ";
        }
        cout<<"\n";
        return;
    }

    for(int i=1;i<=k;i++){
        result.push_back(i);
        dfs(depth+1);
        result.pop_back();
    }
}

int main(){
    cin>>k>>n;

    dfs(0);
    return 0;
}