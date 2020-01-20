/*
Print Input 하면 이상한 예
5
0 0 2 0 0
0 0 2 2 0
0 0 0 0 0
0 0 2 0 0
0 0 0 0 0

오답예
10
0 0 0 0 2 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 2 0 8 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0

런타임 에러예
20
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 8 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

*/
#include <iostream>
using namespace std;

int N;
typedef int(*Temp)[30];

int (*Input())[30] {
	scanf("%d\n", &N);
	int map[30][30]; 
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
	return map;
}

void Print(Temp map) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}

int (*GoNorth(Temp map))[30] {
	for (int j = 0; j < N; j++) {
		int idx = 0;
		for (int i = 1; i < N; i++) {
			if (map[i][j] != 0) { // 요소를 발견
				if (map[idx][j] == 0) { // 비었음
					map[idx][j] = map[i][j];
					map[i][j] = 0;
				}
				else { // 안비었음
					if (map[idx][j] == map[i][j]) {
						map[idx++][j] *= 2;
						map[i][j] = 0;
					}
					else {
 						// idx++;
						map[++idx][j] = map[i][j];
						if (idx != i) {
							map[i][j] = 0;
						}
							
					}
				}
			}
		}
	}
	return map;
}

int (*GoSouth(Temp map))[30] {
	for (int j = 0; j < N; j++) {
		int idx = N - 1;
		for (int i = N-2; i >= 0; i--) {
			if (map[i][j] != 0) { // 요소를 발견
				if (map[idx][j] == 0) { // 비었음
					map[idx][j] = map[i][j];
					map[i][j] = 0;
				}
				else { // 안비었음
					if (map[idx][j] == map[i][j]) {
						map[idx--][j] *= 2;
						map[i][j] = 0;
					}
					else {
						// idx--;
						map[--idx][j] = map[i][j];
						if (idx != i) {
							map[i][j] = 0;
						}
					}
				}
			}
		}
	}
	return map;
}

int (*GoRight(Temp map))[30] {
	for (int i = 0; i < N; i++) {
		int idx = N - 1;
		for (int j = N - 2; j >= 0; j--) {
			if (map[i][j] != 0) {
				if (map[i][idx] == 0) {
					map[i][idx] = map[i][j];
					map[i][j] = 0;
				}
				else {
					if (map[i][idx] == map[i][j]) {
						map[i][idx--] *= 2;
						map[i][j] = 0;
					}
					else {
						// idx--;
						map[i][--idx] = map[i][j];
						if (idx != i) {
							map[i][j] = 0;
						}
					}
				}
			}
		}
	}
	return map;
}

int (*GoLeft(Temp map))[30] {
	for (int i = 0; i < N; i++) {
		int idx = 0;
		for (int j = 1; j < N; j++) {
			if (map[i][j] != 0) {
				if (map[i][idx] == 0) {
					map[i][idx] = map[i][j];
					map[i][j] = 0;
				}
				else {
					if (map[i][idx] == map[i][j]) {
						map[i][idx++] *= 2;
						map[i][j] = 0;
					}
					else {
						// idx++;
						map[i][++idx] = map[i][j];
						if (idx != i) {
							map[i][j] = 0;
						}
					}
				}
			}
		}
	}
	return map;
}
int maxNum = 0;

void DFS(int (*map)[30], int dir, int cnt) {
	if (cnt >= 6) {
		// 가장 큰 수를 maxNum과 비교
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] > maxNum) {
					maxNum = map[i][j];
				}
			}
		}
		return;
	}

	if (dir == 1) {
		int(*newmap)[30] = GoNorth(map);
		DFS(newmap, 2, cnt + 1);
		DFS(newmap, 3, cnt + 1);
		DFS(newmap, 4, cnt + 1);
	}
	else if(dir == 2) {
		int(*newmap)[30] = GoSouth(map);
		DFS(newmap, 1, cnt + 1);
		DFS(newmap, 3, cnt + 1);
		DFS(newmap, 4, cnt + 1);
	}
	else if (dir == 3) {
		int(*newmap)[30] = GoLeft(map);
		DFS(newmap, 1, cnt + 1);
		DFS(newmap, 2, cnt + 1);
		DFS(newmap, 4, cnt + 1);
	}
	else {
		int(*newmap)[30] = GoRight(map);
		DFS(newmap, 1, cnt + 1);
		DFS(newmap, 2, cnt + 1);
		DFS(newmap, 3, cnt + 1);
	}
}

int main() {

	int(*map)[30] = Input();
	Print(map);
	Print(GoRight(map));

	/*DFS(map, 1, 1);
	DFS(map, 2, 1);
	DFS(map, 3, 1);
	DFS(map, 4, 1);

	printf("%d", maxNum);*/

	return 0;
}