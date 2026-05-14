#include <iostream>
using namespace std;

int n;
int ans=0;

void dfs(int len){
    if(len==n){
        ans++;
        return;
    }
    if(len>n) return;

    for(int i=1;i<=4;i++){
        dfs(len+i);
    }
}

int main() {
    cin>>n;

    dfs(0);

    cout<<ans<<"\n";
    return 0;
}