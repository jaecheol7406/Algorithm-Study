#include <iostream>
using namespace std;

// 21: 도착
int score[33] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 0, 13, 16, 19, 22, 24, 28, 27, 29, 25, 30, 35};
int table[33][5] = {
	{1, 2, 3, 4, 5},
	{2, 3, 4, 5, 6},
	{3, 4, 5, 6, 7},
	{4, 5, 6, 7, 8},
	{5, 6, 7, 8, 9},
	{22, 23, 24, 30, 31}, // 10에서 출발
	{7, 8, 9, 10, 11},
	{8, 9, 10, 11, 12},
	{9, 10, 11, 12, 13},
	{10, 11, 12, 13, 14},
	{25, 26, 30, 31, 32}, // 20에서 출발
	{12, 13, 14, 15, 16},
	{13, 14, 15, 16, 17},
	{14, 15, 16, 17, 18},
	{15, 16, 17, 18, 19},
	{27, 28, 29, 30, 31}, // 30에서 출발
	{17, 18, 19, 20, 21},
	{18, 19, 20, 21, 21},
	{19, 20, 21, 21, 21},
	{20, 21, 21, 21, 21},
	{21, 21, 21, 21, 21}, // 40에서 출발
	{21, 21, 21, 21, 21},
	{23, 24, 30, 31, 32}, // 13에서 출발 (22)
	{24, 30, 31, 32, 20},
	{30, 31, 32, 20, 21},
	{26, 30, 31, 32, 20},
	{30, 31, 32, 20, 21},
	{28, 29, 30, 31, 32},
	{29, 30, 31, 32, 20},
	{30, 31, 32, 20, 21},
	{31, 32, 20, 21, 21},
	{32, 20, 21, 21, 21},
	{20, 21, 21, 21, 21}
};

int cube[10]; // 주사위 눈금
int horse[4]; // 각 말의 위치
int visited[33];

int answer;
int sumScore;

void DFS(int cnt) {
	if (cnt >= 10) {

		if (sumScore > answer) answer = sumScore;
		sumScore = 0;

		return;
	}

	for (int i = 0; i < 4; i++) {
		// i번 말을 고를 수 있는지 검증
		if (horse[i] == 21) continue; // 이미 도착한 말은 고를 수 없다
		int nextPos = table[horse[i]][cube[cnt]]; // i번 말을 이번에 고르면 도착하게 될 위치
		if (visited[nextPos] != 0) continue; // 도착할 곳에 이미 누가 있으면 안된다

		// i번 말을 움직이기
		int origin = horse[i];
		visited[horse[i]] = 0;
		horse[i] = nextPos;
		visited[horse[i]] = i;
		sumScore += score[horse[i]];

		DFS(cnt + 1);

		// i번 말 되돌려놓기
		sumScore -= cube[horse[i]];
		visited[horse[i]] = 0;
		horse[i] = origin;
		visited[horse[i]] = i;
	}
}

int main() { 

	for (int i = 0; i < 10; i++) {
		scanf("%d ", &cube[i]);
		cube[i]--;
	}

	DFS(0);

	cout << answer;

	return 0;
}