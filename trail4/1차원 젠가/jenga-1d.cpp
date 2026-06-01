#include <iostream>
#include <vector>
using namespace std;

vector<int> removeRange(vector<int> blocks, int s, int e) {
    vector<int> result;

    for (int i = 0; i < (int)blocks.size(); i++) {
        int pos = i + 1; // 위에서부터 몇 번째 블록인지, 1-indexed

        if (pos < s || pos > e) {
            result.push_back(blocks[i]);
        }
    }

    return result;
}

int main() {
    int n;
    cin >> n;

    vector<int> blocks(n);

    for (int i = 0; i < n; i++) {
        cin >> blocks[i];
    }

    for (int i = 0; i < 2; i++) {
        int s, e;
        cin >> s >> e;

        blocks = removeRange(blocks, s, e);
    }

    cout << blocks.size() << '\n';

    for (int i = 0; i < (int)blocks.size(); i++) {
        cout << blocks[i] << '\n';
    }

    return 0;
}