#include <iostream>
#include <vector>
#include <deque>
#include <utility>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    // 사과가 있는 칸
    vector<vector<bool>> apple(n, vector<bool>(n, false));

    // 현재 뱀의 몸이 있는 칸
    vector<vector<bool>> occupied(n, vector<bool>(n, false));

    for (int i = 0; i < m; i++) {
        int r, c;
        cin >> r >> c;

        // 입력은 1번부터 시작하므로 0-index로 변환
        apple[r - 1][c - 1] = true;
    }

    // front: 머리, back: 꼬리
    deque<pair<int, int>> snake;

    snake.push_front({0, 0});
    occupied[0][0] = true;

    int elapsedTime = 0;
    bool gameOver = false;

    for (int command = 0; command < k; command++) {
        char direction;
        int distance;

        cin >> direction >> distance;

        int dr = 0;
        int dc = 0;

        if (direction == 'U') {
            dr = -1;
        }
        else if (direction == 'D') {
            dr = 1;
        }
        else if (direction == 'L') {
            dc = -1;
        }
        else if (direction == 'R') {
            dc = 1;
        }

        while (distance-- > 0 && !gameOver) {
            // 움직이는 데 1초가 걸림
            elapsedTime++;

            int headRow = snake.front().first;
            int headCol = snake.front().second;

            int nextRow = headRow + dr;
            int nextCol = headCol + dc;

            // 격자를 벗어나면 종료
            if (nextRow < 0 || nextRow >= n ||
                nextCol < 0 || nextCol >= n) {
                gameOver = true;
                break;
            }

            bool eatsApple = apple[nextRow][nextCol];

            /*
             * 사과가 없다면 꼬리가 동시에 사라진다.
             *
             * 새로운 머리가 기존 꼬리 위치로 들어가는 경우를
             * 정상 이동으로 처리하기 위해 충돌 검사 전에
             * 꼬리를 제거한다.
             */
            if (!eatsApple) {
                int tailRow = snake.back().first;
                int tailCol = snake.back().second;

                snake.pop_back();
                occupied[tailRow][tailCol] = false;
            }

            // 꼬리를 제외하고도 몸이 남아 있다면 자기 몸과 충돌
            if (occupied[nextRow][nextCol]) {
                gameOver = true;
                break;
            }

            // 새로운 머리 추가
            snake.push_front({nextRow, nextCol});
            occupied[nextRow][nextCol] = true;

            // 사과를 먹었다면 사과 제거
            if (eatsApple) {
                apple[nextRow][nextCol] = false;
            }
        }
    }

    cout << elapsedTime << '\n';

    return 0;
}