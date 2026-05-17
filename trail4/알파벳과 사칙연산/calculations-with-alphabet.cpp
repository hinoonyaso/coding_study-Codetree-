#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

int n;
string expr;

int valueOf[6];
bool used[6];

vector<int> letters;

long long ans = LLONG_MIN;

long long calculate() {
    long long result = valueOf[expr[0] - 'a'];

    for (int i = 1; i < n; i += 2) {
        char op = expr[i];
        long long nextValue = valueOf[expr[i + 1] - 'a'];

        if (op == '+') {
            result += nextValue;
        }
        else if (op == '-') {
            result -= nextValue;
        }
        else if (op == '*') {
            result *= nextValue;
        }
    }

    return result;
}

void dfs(int idx) {
    if (idx == (int)letters.size()) {
        ans = max(ans, calculate());
        return;
    }

    int alphabetIndex = letters[idx];

    for (int num = 1; num <= 4; num++) {
        valueOf[alphabetIndex] = num;
        dfs(idx + 1);
    }
}

int main() {
    cin >> expr;
    n = expr.size();

    for (char c : expr) {
        if ('a' <= c && c <= 'f') {
            int idx = c - 'a';

            if (!used[idx]) {
                used[idx] = true;
                letters.push_back(idx);
            }
        }
    }

    dfs(0);

    cout << ans << '\n';

    return 0;
}