#include <iostream>
using namespace std;

int n, m, k;
int board[100][100];

bool shouldStop(int row) {
    // 바닥에 닿으면 멈춤
    if (row == n - 1) {
        return true;
    }

    // 바로 아래 칸들 중 하나라도 1이면 멈춤
    for (int col = k; col < k + m; col++) {
        if (board[row + 1][col] == 1) {
            return true;
        }
    }

    return false;
}

int main() {
    cin >> n >> m >> k;

    // 입력의 K는 1번 열 기준이므로 0-index로 바꿈
    k--;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }

    int landingRow = 0;

    for (int row = 0; row < n; row++) {
        if (shouldStop(row)) {
            landingRow = row;
            break;
        }
    }

    // 블럭 놓기
    for (int col = k; col < k + m; col++) {
        board[landingRow][col] = 1;
    }

    // 결과 출력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}