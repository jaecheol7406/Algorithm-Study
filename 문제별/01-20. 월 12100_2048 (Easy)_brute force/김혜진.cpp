/*
10
0 0 64 32 32 0 0 0 0 0
0 32 32 64 0 0 0 0 0 0
0 0 128 0 0 0 0 0 0 0
64 64 128 0 0 0 0 0 0 0
0 0 64 32 32 0 0 0 0 0
0 32 32 64 0 0 0 0 0 0
0 0 128 0 0 0 0 0 0 0
64 64 128 0 0 0 0 0 0 0
128 32 2 4 0 0 0 0 0 0
0 0 128 0 0 0 0 0 0 0


답 : 1024
output: 512

7
2 2 2 2 2 2 2
2 0 2 2 2 2 2
2 0 2 2 2 2 2
2 0 2 2 2 2 2
2 2 2 0 2 2 2
2 2 2 2 2 2 0
2 2 2 2 2 2 0


답 : 32
output: 64

*/
#include <iostream>
using namespace std;

int N;
typedef int(*Temp)[30];
int map[30][30];



void Input() {
	scanf("%d\n", &N);
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void PrintThis(int (*thisMap)[30]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", thisMap[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int(*GoNorth(int(*thisMap)[30]))[30] {
	//printf("Input: \n");
	//PrintThis(thisMap);

	for (int j = 0; j < N; j++) {
		int idx = 0;
		for (int i = 1; i < N; i++) {
			if (thisMap[i][j] != 0) { // 요소를 발견
				if (thisMap[idx][j] == 0) { // 비었음
					thisMap[idx][j] = thisMap[i][j];
					thisMap[i][j] = 0;
				}
				else { // 안비었음
					if (thisMap[idx][j] == thisMap[i][j]) {
						thisMap[idx++][j] *= 2;
						thisMap[i][j] = 0;
					}
					else {
 						// idx++;
						thisMap[++idx][j] = thisMap[i][j];
						if (idx != i) {
							thisMap[i][j] = 0;
						}
							
					}
				}
			}
		}
	}
	return thisMap;
}

int(*GoSouth(int(*thisMap)[30]))[30]{
	//printf("Input: \n");
	//PrintThis(thisMap);

	for (int j = 0; j < N; j++) {
		int idx = N - 1;
		for (int i = N-2; i >= 0; i--) {
			if (thisMap[i][j] != 0) { // 요소를 발견
				if (thisMap[idx][j] == 0) { // 비었음
					thisMap[idx][j] = thisMap[i][j];
					thisMap[i][j] = 0;
				}
				else { // 안비었음
					if (thisMap[idx][j] == thisMap[i][j]) {
						thisMap[idx--][j] *= 2;
						thisMap[i][j] = 0;
					}
					else {
						// idx--;
						thisMap[--idx][j] = thisMap[i][j];
						if (idx != i) {
							thisMap[i][j] = 0;
						}
					}
				}
			}
		}
	}
	return thisMap;
}

int(*GoRight(int(*thisMap)[30]))[30]{
	//printf("Input: \n");
	//PrintThis(thisMap);

	for (int i = 0; i < N; i++) {
		int idx = N - 1;
		for (int j = N - 2; j >= 0; j--) {
			if (thisMap[i][j]!= 0) {
				if (thisMap[i][idx] == 0) {
					thisMap[i][idx] = thisMap[i][j];
					thisMap[i][j] = 0;
				}
				else {
					if (thisMap[i][idx] == thisMap[i][j]) {
						thisMap[i][idx--] *= 2;
						thisMap[i][j] = 0;
					}
					else {
						// idx--;
						thisMap[i][--idx] = thisMap[i][j];
						if (idx != j) {
							thisMap[i][j] = 0;
						}
					}
				}
			}
		}
	}
	return thisMap;
}

int(*GoLeft(int(*thisMap)[30]))[30] {
	//printf("Input: \n");
	//PrintThis(thisMap);

	for (int i = 0; i < N; i++) {
		int idx = 0;
		for (int j = 1; j < N; j++) {
			if (thisMap[i][j] != 0) {
				if (thisMap[i][idx] == 0) {
					thisMap[i][idx] = thisMap[i][j];
					thisMap[i][j] = 0;
				}
				else {
					if (thisMap[i][idx] == thisMap[i][j]) {
						thisMap[i][idx++] *= 2;
						thisMap[i][j] = 0;
					}
					else {
						// idx++;
						thisMap[i][++idx] = thisMap[i][j];
						if (idx != j) {
							thisMap[i][j] = 0;
						}
					}
				}
			}
		}
	}
	return thisMap;
}
int maxNum = 0;

void DFS(int(*thisMap)[30], int dir, int cnt) {
	if (cnt >= 6) {
		// 가장 큰 수를 maxNum과 비교
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (thisMap[i][j] > maxNum) {
					maxNum = thisMap[i][j];
				}
			}
		}
		return;
	}

	//printf("DFS(dir: %d, cnt: %d)\n", dir, cnt);
	int targetMap[30][30];

	

	if (dir == 1) {
		int(*newmap)[30] = GoNorth(thisMap);
		for (int d = 1; d <= 4; d++) {
			if (d == dir) continue;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					targetMap[i][j] = newmap[i][j];
				}
			}
			DFS(targetMap, d, cnt + 1);
		}
	}
	else if(dir == 2) {
		int(*newmap)[30] = GoSouth(thisMap);
		for (int d = 1; d <= 4; d++) {
			if (d == dir) continue;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					targetMap[i][j] = newmap[i][j];
				}
			}
			DFS(targetMap, d, cnt + 1);
		}
	}
	else if (dir == 3) {
		int(*newmap)[30] = GoLeft(thisMap);
		for (int d = 1; d <= 4; d++) {
			if (d == dir) continue;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					targetMap[i][j] = newmap[i][j];
				}
			}
			DFS(targetMap, d, cnt + 1);
		}
	}
	else {
		int(*newmap)[30] = GoRight(thisMap);
		for (int d = 1; d <= 4; d++) {
			if (d == dir) continue;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					targetMap[i][j] = newmap[i][j];
				}
			}
			DFS(targetMap, d, cnt + 1);
		}
	}
}

int main() {

	Input();
	// Print();
	/*printf("GoNorth\n");
	Item(*newmap)[30] = GoNorth(map);
	PrintThis(newmap);

	printf("Then GoRight\n");
	Item(*secondmap)[30] = GoRight(newmap);
	PrintThis(secondmap);

	printf("Then Go South\n");
	Item(*thirdmap)[30] = GoSouth(secondmap);
	PrintThis(thirdmap);
	*/
	// PrintThis(GoNorth(GoNorth(map))); 이렇게 하면 부정확함

	int original[30][30];

	for (int st = 1; st <= 4; st++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				original[i][j] = map[i][j];
			}
		}
		DFS(original, st, 1);
	}

	printf("%d", maxNum);

	return 0;
}