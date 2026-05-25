#include <iostream>
#include <deque>
using namespace std;

int main() {
    int n,t;
    cin>>n>>t;

    deque<int> belt;
    int top[200],bottom[200];
    
    for(int i=0;i<n;i++){
        cin>>top[i];
        belt.push_back(top[i]);
    }

    for(int i=0;i<n;i++) {
        cin>>bottom[i];
        belt.push_back(bottom[i]);
    }

    t%=(2*n);

    while(t--){
        int last=belt.back();
        belt.pop_back();
        belt.push_front(last);
    }

    for(int i=0;i<n;i++){
        cout<<belt[i]<<" ";
    }
    cout<<"\n";

    for(int i=n;i<2*n;i++){
        cout<<belt[i]<<" ";
    }
    cout<<"\n";

    return 0;
}