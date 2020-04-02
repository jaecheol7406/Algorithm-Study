#include <iostream>
#include <stdlib.h>
using namespace std;

int N, L, R;
int map[150][150];
int region[150][150]; // 연합 라벨링

int number[3000]; // 연합 구성국가 개수
int sum[3000]; // 각 연합의 전체 인구 합

void Input() {
	scanf("%d %d %d\n", &N, &L, &R);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
}

int regionNum = 1;
void Init() {
	regionNum = 1;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			region[i][j] = 0;
		}
	}

	for (int i = 0; i < 3000; i++) {
		sum[i] = 0;
		number[i] = 0;
	}
}

int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

void DFS(int r, int c) {
	region[r][c] = regionNum;
	sum[regionNum] += map[r][c];
	number[regionNum]++;

	int tmpR, tmpC;

	for (int i = 0; i < 4; i++) {
		tmpR = r + dir[i][0];
		tmpC = c + dir[i][1];

		if (tmpR < 0 || tmpC < 0 || N <= tmpR || N <= tmpC) continue;
		if (region[tmpR][tmpC] != 0) continue;
		if (abs(map[tmpR][tmpC] - map[r][c]) >= L && abs(map[tmpR][tmpC] - map[r][c]) <= R) {
			region[tmpR][tmpC] = regionNum;
			DFS(tmpR, tmpC);
		}
	}

}


int main() {

	Input();
	int nums = 0;

	while (1) {
		Init();

		// DFS로 연합 나누기
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (region[i][j] == 0) {
					DFS(i, j);
					regionNum++;
				}
			}
		}

		// 연합 확인
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%d ", region[i][j]);
			}
			cout << endl;
		}

		if (regionNum - 1 == N * N) break;
		nums++;

		// 인구이동
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				map[i][j] = sum[region[i][j]] / number[region[i][j]];
			}
		}
		
	}

	cout << nums;

	return 0;
}