#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> bombs(n);

    for (int i = 0; i < n; i++) {
        cin >> bombs[i];
    }

    while (true) {
        vector<int> nextBombs;
        bool exploded = false;

        int i = 0;

        while (i < (int)bombs.size()) {
            int j = i + 1;

            while (j < (int)bombs.size() && bombs[j] == bombs[i]) {
                j++;
            }

            int count = j - i;

            if (count >= m) {
                exploded = true;
            } 
            else {
                for (int k = i; k < j; k++) {
                    nextBombs.push_back(bombs[k]);
                }
            }

            i = j;
        }

        bombs = nextBombs;

        if (!exploded) {
            break;
        }
    }

    cout << bombs.size() << "\n";

    for (int bomb : bombs) {
        cout << bomb << "\n";
    }

    return 0;
}