/*
map 배열: 빈 곳 0, 사과 1, 뱀이 점유한 곳 2
snake 큐: front가 꼬리, back이 머리. 머리를 늘릴 겨우 큐의 가장 뒤에 push

이와 같이 상태 저장하며, 종료 조건에 걸릴 때까지 계속 이동한다.
*/
#include <iostream>
#include <queue>

using namespace std;

int N, K, L;
int map[105][105]; // 사과는 1, 뱀은 2, 빈 곳은 0

int turnExist[10005]; // index: 방향전환해야 하는 시간, value: 1이면 돌아야 함, 0이면 아님
char turn[10005]; // index: 방향전환해야 하는 시간, value: 방향

struct Snake {
	int r;
	int c;
};
queue<Snake> snake; // 뱀의 위치가 담긴 큐. 가장 앞이 꼬리, 가장 뒤가 머리

void Input() {
	scanf("%d\n%d\n", &N, &K);

	int r, c;
	for (int i = 0; i < K; i++) {
		scanf("%d %d\n", &r, &c);
		map[r - 1][c - 1] = 1;
	}

	scanf("%d\n", &L);

	int t;
	char p;
	for (int i = 0; i < L; i++) {
		scanf("%d %c\n", &t, &p);
		turnExist[t] = 1;
		turn[t] = p;
	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", map[i][j]);
		}
		cout << endl;
	}

	/*for (int i = 0; i < 10005; i++) {
		if(turnExist[i] == 1) printf("%c ", turn[i]);
	}*/
}

int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
int nowDir = 0; // 현재 뱀이 바라보고 있는 방향

int answer = 0;
int main() {
	Input();

	// 뱀의 최초 위치
	snake.push(Snake{ 0, 0 });
	map[0][0] = 2;
	int newR, newC;
	Snake tail;
	//Print();

	while (1) {
		answer++;

		// 이동
		newR = snake.back().r + dir[nowDir][0];
		newC = snake.back().c + dir[nowDir][1];

		// 종료 조건 검사
		if (newR < 0 || newC < 0 || N <= newR || N <= newC) break; // 범위를 벗어나면
		if (map[newR][newC] == 2) break; // 자신의 몸에 부딪히면

		// 몸길이를 늘려 머리 위치를 바꾼다 (머리위치 = 큐의 맨끝)
		snake.push(Snake{ newR, newC });

		// 사과가 있는지 검사
		if (map[newR][newC] != 1) { // 사과가 없으면 꼬리를 줄인다
			tail = Snake{ snake.front().r, snake.front().c };
			map[tail.r][tail.c] = 0;
			snake.pop();
		}
		map[newR][newC] = 2; // 머리 위치를 표시하는 동시에 먹은 사과를 없애게 된다

		// 방향 전환
		if (turnExist[answer] == 1) {
			if (turn[answer] == 'D') { // 오른쪽으로 90도 회전
				nowDir = (nowDir + 1) % 4;
			}
			else {
				nowDir = (nowDir + 3) % 4;
			}
		}

		//cout << answer << "초 후=============" << endl;
		//Print();
	}
	cout << answer;

	return 0;
}