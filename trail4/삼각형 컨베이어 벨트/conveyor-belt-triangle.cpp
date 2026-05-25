#include <iostream>
#include <deque>
using namespace std;

int main() {
    int n,t;
    cin>>n>>t;

    deque<int> belt;
    int direct1[200],direct2[200],direct3[200];

    for(int i=0;i<n;i++){
        cin>>direct1[i];
        belt.push_back(direct1[i]);
    }

    for(int i=0;i<n;i++){
        cin>>direct2[i];
        belt.push_back(direct2[i]);
    }

    for(int i=0;i<n;i++){
        cin>>direct3[i];
        belt.push_back(direct3[i]);
    }

    t%=(3*n);

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

    for(int i=2*n;i<3*n;i++){
        cout<<belt[i]<<" ";
    }
    cout<<"\n";

    return 0;
}