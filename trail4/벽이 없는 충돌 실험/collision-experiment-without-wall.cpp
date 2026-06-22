#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int OFFSET = 2000;
const int MAX_COORD = 4000;
const int SIZE = 4001;
const int EMPTY = -1;

struct Ball {
    int x;
    int y;
    int weight;
    int dir;
    int number;
};

// U, R, D, L
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

// 해당 좌표를 차지한 nextBalls의 인덱스
static int occupied[SIZE][SIZE];

int getDir(char dir) {
    if (dir == 'U') return 0;
    if (dir == 'R') return 1;
    if (dir == 'D') return 2;
    return 3;
}

bool isStronger(const Ball& a, const Ball& b) {
    if (a.weight != b.weight) {
        return a.weight > b.weight;
    }

    return a.number > b.number;
}

bool inRange(int x, int y) {
    return 0 <= x && x <= MAX_COORD &&
           0 <= y && y <= MAX_COORD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fill(&occupied[0][0],
         &occupied[0][0] + SIZE * SIZE,
         EMPTY);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<Ball> balls;
        balls.reserve(n);

        for (int number = 1; number <= n; number++) {
            int x, y, weight;
            char dir;

            cin >> x >> y >> weight >> dir;

            /*
             * 좌표를 2배하여 0.5칸 위치의 충돌도
             * 정수 좌표에서 처리한다.
             *
             * 원래 좌표: -1000 ~ 1000
             * 확대 및 평행 이동: 0 ~ 4000
             */
            x = x * 2 + OFFSET;
            y = y * 2 + OFFSET;

            balls.push_back({
                x,
                y,
                weight,
                getDir(dir),
                number
            });
        }

        int answer = -1;

        vector<Ball> nextBalls;
        nextBalls.reserve(n);

        for (int time = 1; time <= MAX_COORD; time++) {
            if (balls.size() <= 1) {
                break;
            }

            nextBalls.clear();

            for (const Ball& ball : balls) {
                Ball moved = ball;

                moved.x += dx[moved.dir];
                moved.y += dy[moved.dir];

                /*
                 * 이 범위를 벗어난 구슬은 다시 돌아오지 않는다.
                 * 방향이 바뀌지 않으므로 앞으로도 충돌할 수 없다.
                 */
                if (!inRange(moved.x, moved.y)) {
                    continue;
                }

                int& index = occupied[moved.x][moved.y];

                if (index == EMPTY) {
                    index = static_cast<int>(nextBalls.size());
                    nextBalls.push_back(moved);
                } else {
                    // 이미 같은 위치에 구슬이 있으므로 충돌
                    answer = time;

                    if (isStronger(moved, nextBalls[index])) {
                        nextBalls[index] = moved;
                    }
                }
            }

            /*
             * 전체 4001 × 4001 배열을 초기화하면 시간 초과가 난다.
             * 이번에 사용한 위치만 EMPTY로 되돌린다.
             */
            for (const Ball& ball : nextBalls) {
                occupied[ball.x][ball.y] = EMPTY;
            }

            balls.swap(nextBalls);
        }

        cout << answer << '\n';
    }

    return 0;
}