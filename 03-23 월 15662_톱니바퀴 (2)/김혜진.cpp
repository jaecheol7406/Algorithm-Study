/*
1. 2차원 배열 circle[1005][10]에 1번 ~ T번 톱니바퀴의 극 상태를 적어둔다.
2. i번째 톱니바퀴가 돌아야 한다면,
      2 ~ i 번째 톱니바퀴에 대해 <i번 톱니바퀴의 6번 톱니>와 <i-1번 톱니바퀴의 2번 톱니>를 비교해 돌지 말지 결정한다.
      i ~ T-1 번째 톱니바퀴에 대해 <i번 톱니바퀴의 2번 톱니>와 <i+1번 톱니바퀴의 6번 톱니>를 비교해 돌지 말지 결정한다.
3. 각 톱니바퀴가 돌지 말지와 도는 방향을 결정한 후, 지정된 방향대로 돌린다
*/
#include <iostream>
#include <string.h>
using namespace std;
#define LEFT 6
#define RIGHT 2

// ============ Input =============
int T, K;
int circle[1005][10]; // 톱니바퀴 상태
int roundCir[1005];   // 회전하는 톱니바퀴 번호
int roundDir[1005];	  // 회전 방향

// ============ 도출 ============
int evalRound[1005];  // 각 턴에서, 톱니바퀴가 돌 방향 (0: 돌지 않는다, 1: 시계, -1: 반시계)

void Input() {
	scanf("%d\n", &T);
	for (int i = 1; i <= T; i++) {
		for (int j = 0; j < 8; j++) {
			scanf("%1d", &circle[i][j]);
		}
	}
	scanf("%d\n", &K);
	for (int i = 1; i <= K; i++) {
		scanf("%d %d\n", &roundCir[i], &roundDir[i]);
	}
}

void Print() {
	for (int i = 1; i <= T; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%1d", circle[i][j]);
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 1; i <= K; i++) { 
		printf("%d %d\n", roundCir[i], roundDir[i]);
	}
}

void Round(int idx, int dir) { // idx번 톱니를 dir 방향으로 돌린다. 2.톱니바퀴 돌리기 에서 호출되는 함수
	int tmp;
	if (dir == 1) { // 시계 방향
		tmp = circle[idx][7];
		for (int i = 7; i >=1; i--) {
			circle[idx][i] = circle[idx][i-1];
		}
		circle[idx][0] = tmp;
	}
	else if (dir == -1) { // 반시계 방향
		tmp = circle[idx][0];
		for (int i = 0; i <= 6; i++) {
			circle[idx][i] = circle[idx][i+1];
		}
		circle[idx][7] = tmp;
	}

	
}

int main() {

	Input();
	// Print();

	for (int turn = 1; turn <= K; turn++) { // K번 돈다

		// ============= 1.톱니바퀴들의 도는 방향 계산 =============
		for (int i = 1; i <= T; i++) {
			evalRound[i] = 0;
		}

		evalRound[roundCir[turn]] = roundDir[turn]; // 이번에 돌기로 되어 있는 톱니

		for (int i = roundCir[turn]; i >= 2; i--) { // 돌기로 되어 있는 톱니의 왼쪽에 대해
			if (evalRound[i] == 0) continue;
			if (circle[i][LEFT] == circle[i - 1][RIGHT]) continue;
			evalRound[i - 1] = (-1) * evalRound[i];
		}

		for (int i = roundCir[turn]; i <= T-1; i++) {
			if (evalRound[i] == 0) continue;
			if (circle[i][RIGHT] == circle[i + 1][LEFT]) continue;
			evalRound[i + 1] = (-1) * evalRound[i];
		}

		// 계산한 방향 출력
		/*for (int i = 1; i <= T; i++) {
			cout << evalRound[i] << " ";
		}
		cout << endl;*/


		// ============= 2.톱니바퀴 돌리기 =============
		for (int i = 1; i <= T; i++) {
			if (evalRound[i] != 0) {
				Round(i, evalRound[i]);
			}
		}

		// 회전후 결과
		/*for (int i = 1; i <= T; i++) {
			for (int j = 0; j < 8; j++) {
				cout << circle[i][j];
			}
			cout << endl;
		}
		cout << endl;*/
	}

	int answer = 0;
	for (int i = 1; i <= T; i++) {
		if (circle[i][0] == 1) answer++;
	}
	cout << answer;

	return 0;
}