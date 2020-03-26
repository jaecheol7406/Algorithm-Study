/*
1. 기울이는 코드 완성
  function call: Input() -> Tilt(방향)
2. 기울이는 방향 탐색 고민중
*/
#include <iostream>
using namespace std;

int N, M;
char map[12][12];
int holeR, holeC;

void Input() {
	scanf("%d %d\n", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%1s", &map[i][j]);
			if (map[i][j] == 'O') {
				holeR = i;
				holeC = j;
			}
		}
	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%c", map[i][j]);
		}
		cout << endl;
	}
}

void Fallen(char color) {
	cout << color << "색 구슬이 빠졌습니다" << endl;
}

void Tilt(int dir) { // 0: 왼쪽 1: 오른쪽 2:위쪽 3:아래쪽

	if (dir == 0) {
		for (int i = 1; i < N - 1; i++) { // 모든 행에 대해서
			int next = 1;
			for (int j = 1; j < M - 1; j++) { // 맨 왼쪽부터
				if (map[i][j] == 'R' || map[i][j] == 'B') { 
					next = j - 1;
					while (map[i][next] == '.' || map[i][next] == 'O') {
						next--;
					}
					next++;

					if (holeR == i && next <= holeC && holeC <= j) {
						Fallen(map[i][j]);
					}

					if (next != j) { // 그 자리에 가만 있는 게 아니라 이동을 한다면
						map[i][next] = map[i][j];
						map[i][j] = '.';
					}
				}
			}

		}
	}
	else if (dir == 1) {
		for (int i = 1; i < N - 1; i++) {
			int next = 1;
			for (int j = M - 1; j > 0; j--) { // 맨 오른쪽부터
				if (map[i][j] == 'R' || map[i][j] == 'B') {
					next = j+1;
					while (map[i][next] == '.' || map[i][next] == 'O') {
						next++;
					}
					next--;

					if (holeR == i && j <= holeC && holeC <= next) {
						Fallen(map[i][j]);
					}

					if (next != j) { // 그 자리에 가만 있는 게 아니라 이동을 한다면
						map[i][next] = map[i][j];
						map[i][j] = '.';
					}
				}

			}
		}
	}

	else if (dir == 2) { // 위쪽
		for (int j = 1; j < M - 1; j++) { // 모든 열에 대해서
			int next = 1;
			for (int i = 1; i < N - 1; i++) { // 맨 위 행부터 검사
				if (map[i][j] == 'R' || map[i][j] == 'B') {
					
					next = i - 1;
					while (map[next][j] == '.' || map[next][j] == 'O') { // 갈 수 있는 자리를 찾아낸다
						next--;
					}
					next++;
					if (holeC == j && next <= holeR && holeR <= i) {
						Fallen(map[i][j]);
					}

					if (next != i) { // 그 자리에 가만 있는 게 아니라 이동을 한다면
						map[next][j] = map[i][j];
						map[i][j] = '.';
					}
					
				}
			}
		}
	}
	else if (dir = 3) { // 아래로
		for (int j = 1; j < M - 1; j++) { // 모든 열에 대해서
			int next = 1;
			for (int i = N-1; i > 0; i--) { // 맨 아래 행부터 검사
				if (map[i][j] == 'R' || map[i][j] == 'B') { // 구슬이 있으면
					next = i + 1;
					while (map[next][j] == '.' || map[next][j] == 'O') { // 갈 수 있는 자리를 찾아낸다
						next++;
					}
					next--;
					if (holeC == j && i <= holeR && holeR <= next) {
						Fallen(map[i][j]);
					}

					if (next != i) {
						map[next][j] = map[i][j];
						map[i][j] = '.';
					}
					

				}
			}
		}
	}
}

int main() {

	Input();
	Print();
	cout << endl;

	Tilt(3);
	Print();

	// 10번 해 본다.
	// 1번 한 뒤 떨어진 구슬을 모았을 때 파란 구슬이 있으면 -1을 출력한다. 빨간 구슬만 있으면 횟수를 출력한다.
	// 10번 초과하면 -1을 출력한다.

	

	return 0;
}