/*
헷갈리는 부분
1. DFS 탐색완료시 조기종료시키기 (전역변수 answer 활용)
2. 사다리 위치를 고를 때, 순열이 아니라 조합으로 뽑아야 함.
   1,3 순회 때 (1,3) & (3, 3) 을 뽑아놓고, 
   3, 3 순회에서 또 (3, 3) & (1,3)을 뽑으면 시간초과
*/
#include <iostream>
#include <vector>
using namespace std;

int N, M, H;
int map[35][15];

int limit;
int answer = -1;

void Input() {
	cin >> N >> M >> H;
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		map[a][b] = 1;
	}
}

void Print() {
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

bool Test() {
	for (int j = 1; j <= N; j++) { // j열에서 출발
		int pos = j; // 현재 몇열에 있는지
		for (int i = 1; i <= H; i++) {
			if (pos+1 <= N && map[i][pos] == 1) {
				pos++;
			}
			else if (pos - 1 >= 1 && map[i][pos - 1] == 1) {
				pos--;
			}
		}
		if (pos != j) return false;
	}
	return true;
}

void DFS(int pre, int cnt) {
	if (answer != -1) return; // 주의점 1. 답이 이미 나왔음, DFS를 중간에 종료시키는 방법

	if (cnt >= limit) {

		if (Test()) {
			answer = limit;
		}
		//cout << endl;
		//Print();
		return;
	}

	for (int i = 1; i <= H; i++) {
		for (int j = pre; j < N; j++) {
			if (map[i][j] ) continue;
			if (j - 1 >= 1 && map[i][j - 1] == 1) continue;
			if (j + 1 < N && map[i][j + 1] == 1) continue;

			map[i][j] = 1;
			//cout << cnt << "번째 선택: " << "(" << i << "," << j << ") ";
			DFS(pre + 1, cnt + 1); // 2. 사다리 위치를 고를 때, 순열이 아니라 조합으로 뽑아야 함.
			if (answer != -1) break;  // 주의점 1. 답이 이미 나왔음, DFS를 중간에 종료시키는 방법
			map[i][j] = 0;
		}
	}

}

int main() {

	Input();
	// Print();

	for (int i = 0; i < 4; i++) {
		limit = i;

		DFS(1, 0); // 2. 사다리 위치를 고를 때, 순열이 아니라 조합으로 뽑아야 함.
		if (answer != -1) break;  // 주의점 1. 답이 이미 나왔음, DFS를 중간에 종료시키는 방법
	}

	cout << answer;

	return 0;
}