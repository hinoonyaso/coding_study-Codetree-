#include <iostream>
#include <vector>
using namespace std;

int n, m;
int r, c;

vector<vector<int>> board;

int topFace=1;
int bottomFace=6;
int frontFace=2;
int backFace=5;
int leftFace=4;
int rightFace=3;

void rollDice(char dir){
    int oldTop = topFace;
    int oldBottom = bottomFace;
    int oldFront = frontFace;
    int oldBack = backFace;
    int oldRight = rightFace;
    int oldLeft = leftFace;

    if (dir == 'L') {
        topFace = oldRight;
        rightFace = oldBottom;
        bottomFace = oldLeft;
        leftFace = oldTop;
    }
    else if (dir == 'R') {
        topFace = oldLeft;
        leftFace = oldBottom;
        bottomFace = oldRight;
        rightFace = oldTop;
    }
    else if (dir == 'U') {
        topFace = oldFront;
        frontFace = oldBottom;
        bottomFace = oldBack;
        backFace = oldTop;
    }
    else if (dir == 'D') {
        topFace = oldBack;
        backFace = oldBottom;
        bottomFace = oldFront;
        frontFace = oldTop;
    }
}

bool inRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

int main() {
    cin>>n>>m>>r>>c;

    r--;
    c--;

    board.assign(n, vector<int>(n, 0));

    // 처음 놓인 위치에도 아랫면 숫자를 기록
    board[r][c] = bottomFace;

    for (int i = 0; i < m; i++) {
        char dir;
        cin >> dir;

        int nr = r;
        int nc = c;

        if (dir == 'L') {
            nc--;
        }
        else if (dir == 'R') {
            nc++;
        }
        else if (dir == 'U') {
            nr--;
        }
        else if (dir == 'D') {
            nr++;
        }

        // 격자를 벗어나면 이동과 회전을 모두 무시
        if (!inRange(nr, nc)) {
            continue;
        }

        // 주사위를 굴린 후 위치 변경
        rollDice(dir);
        r = nr;
        c = nc;

        // 현재 아랫면 숫자로 덮어쓰기
        board[r][c] = bottomFace;
    }

    int answer = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            answer += board[i][j];
        }
    }

    cout << answer << '\n';
    return 0;
}