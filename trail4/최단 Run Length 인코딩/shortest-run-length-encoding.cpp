#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int getEncodedLength(string s) {
    int n = s.size();
    int len = 0;

    int cnt = 1;

    for (int i = 1; i < n; i++) {
        if (s[i] == s[i - 1]) {
            cnt++;
        } 
        else {
            len += 1 + to_string(cnt).size();
            cnt = 1;
        }
    }

    // 마지막 묶음 처리
    len += 1 + to_string(cnt).size();

    return len;
}

int main() {
    string s;
    cin >> s;

    int n = s.size();
    int ans = 1e9;

    for (int k = 0; k < n; k++) {
        string rotated = s.substr(n - k) + s.substr(0, n - k);

        int encodedLen = getEncodedLength(rotated);
        ans = min(ans, encodedLen);
    }

    cout << ans << "\n";

    return 0;
}