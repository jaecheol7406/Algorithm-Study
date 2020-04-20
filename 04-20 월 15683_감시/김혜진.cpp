/*
function call: main -> Input -> (DFS -> Init -> Look -> Count ) -> main

1. DFS로 각 카메라가 감시할 방향을 뽑는다.
단 카메라 번호별로 뽑을 수 있는 개수가 다르다. (DFS함수 안에서 정의)
2. 카메라 번호와 카메라 방향 정보를 가지고 감시 가능한 구역을 표시한다.

*/
#include <iostream>
#include <vector>
using namespace std;

struct Pos {
	int r;
	int c;
	int n;
};

int N, M;
int map[10][10];
int backup[10][10];
vector<Pos> cctvList;

// 각각 1 ~ 5번 카메라가 감시할 수 있는 방향을 배열로 정의
int dir1[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} }; // 총 4개 방향
int dir2[2][2][2] = { { {1, 0}, {-1, 0} }, { {0, 1}, {0, -1} } }; // 총 2개 방향, 방향 하나당 2군데 조사
int dir3[4][2][2] = { {{-1, 0}, {0, 1}}, {{0, 1}, {1, 0}}, {{1, 0}, {0, -1}}, {{0, -1}, {-1, 0}} }; // 총 4개 방향, 방향 하나당 2군데 조사
int dir4[4][3][2] = { {{-1, 0}, {0, 1}, {0, -1}}, {{1, 0}, {0, 1}, {0, -1}}, {{1, 0}, {-1, 0}, {0, -1}}, {{1, 0}, {-1, 0}, {0, 1}} }; // 총 4개 방향, 방향 하나당 3군데 조사
int dir5[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} }; // 총 1개 방향, 방향 하나당 4군데 조사

int minAnswer = 100;

void Input() {
	scanf("%d %d\n", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d ", &map[i][j]);
			backup[i][j] = map[i][j];

			if (map[i][j] > 0 && map[i][j] < 6) {
				cctvList.push_back(Pos{ i, j, map[i][j] });
			}
		}
	}
}

void Look(int idx, int dir) {
	int tmpR, tmpC;

	if (cctvList[idx].n == 1) { // 1번 카메라
		tmpR = cctvList[idx].r;
		tmpC = cctvList[idx].c;

		while (1) {
			tmpR += dir1[dir][0];
			tmpC += dir1[dir][1];

			if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) break;
			if (map[tmpR][tmpC] == 6) break;

			map[tmpR][tmpC] = -1; // 감시가능한 구역은 -1로 표시
		}
	}
	else if (cctvList[idx].n == 2) {
		for (int i = 0; i < 2; i++) {
			tmpR = cctvList[idx].r;
			tmpC = cctvList[idx].c;

			while (1) {
				tmpR += dir2[dir][i][0];
				tmpC += dir2[dir][i][1];

				if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) break;
				if (map[tmpR][tmpC] == 6) break;

				map[tmpR][tmpC] = -1; // 감시가능한 구역은 -1로 표시
			}
		}
	}
	else if (cctvList[idx].n == 3) {
		for (int i = 0; i < 2; i++) {
			tmpR = cctvList[idx].r;
			tmpC = cctvList[idx].c;

			while (1) {
				tmpR += dir3[dir][i][0];
				tmpC += dir3[dir][i][1];

				if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) break;
				if (map[tmpR][tmpC] == 6) break;

				map[tmpR][tmpC] = -1; // 감시가능한 구역은 -1로 표시
			}
		}
	}
	else if (cctvList[idx].n == 4) {
		for (int i = 0; i < 3; i++) {
			tmpR = cctvList[idx].r;
			tmpC = cctvList[idx].c;

			while (1) {
				tmpR += dir4[dir][i][0];
				tmpC += dir4[dir][i][1];

				if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) break;
				if (map[tmpR][tmpC] == 6) break;

				map[tmpR][tmpC] = -1; // 감시가능한 구역은 -1로 표시
			}
		}
	}
	else if (cctvList[idx].n == 5) {
		for (int i = 0; i < 4; i++) {
			tmpR = cctvList[idx].r;
			tmpC = cctvList[idx].c;

			while (1) {
				tmpR += dir5[i][0];
				tmpC += dir5[i][1];

				if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) break;
				if (map[tmpR][tmpC] == 6) break;

				map[tmpR][tmpC] = -1; // 감시가능한 구역은 -1로 표시
			}
		}
	}
}

void Init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			map[i][j] = backup[i][j];
		}
	}
}

void Count() {
	int minTmp = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 0) {
				minTmp++;
			}
		}
	}
	if (minTmp < minAnswer) minAnswer = minTmp;
}

vector<int> picked;
void DFS(int cnt) {
	if (cnt >= cctvList.size()) {
		/*for (int i = 0; i < picked.size(); i++) { // 고른 감시 방향
			cout << picked[i] << " ";
		}
		cout << endl;*/
		Init();

		for (int i = 0; i < picked.size(); i++) {
			Look(i, picked[i]); // i번 cctv는 picked[i] 방향을 본다는 상태에서 감시되는 구역을 표시한다.
		}

		Count();

		return;
	}

	if (cctvList[cnt].n == 2) { // 0 ~ 1 중에서 하나 고른다
		for (int i = 0; i < 2; i++) {
			picked.push_back(i);
			DFS(cnt + 1);
			picked.pop_back();
		}
	}
	else if (cctvList[cnt].n == 5) { // 무조건 0을 뱉는다
		picked.push_back(0);
		DFS(cnt + 1);
		picked.pop_back();
	}
	else { // 0 ~ 3 중에서 하나 고른다
		for (int i = 0; i < 4; i++) {
			picked.push_back(i);
			DFS(cnt + 1);
			picked.pop_back();
		}
	}
}

int main() {

	Input();

	DFS(0); // CCTV 방향 정하기

	cout << minAnswer;

	return 0;
}