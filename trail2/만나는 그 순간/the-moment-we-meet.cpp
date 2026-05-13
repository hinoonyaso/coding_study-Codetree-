#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> makePath(int cnt) {
    vector<int> path;
    int pos = 0;

    for (int i = 0; i < cnt; i++) {
        char dir;
        int time;
        cin >> dir >> time;

        for (int j = 0; j < time; j++) {
            if (dir == 'R') pos++;
            else pos--;

            path.push_back(pos);
        }
    }

    return path;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a = makePath(n);
    vector<int> b = makePath(m);

    int totalTime = max(a.size(), b.size());

    while ((int)a.size() < totalTime) a.push_back(a.back());
    while ((int)b.size() < totalTime) b.push_back(b.back());

    for (int i = 0; i < totalTime; i++) {
        if (a[i] == b[i]) {
            cout << i + 1 << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';

    return 0;
}