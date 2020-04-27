/*
BOJ 15684번: 사다리 조작
문제 유형 : 시뮬레이션(DFS)

1. 가로선을 0개 추가하는 경우부터 3개 추가하는 경우를 순차적으로 탐색.
	-> i번 세로선이 i번이 나온다면 종료
2. 1번 사다리(세로선)와 2번 사다리(세로선)가 3번 가로선에 의해 연결되어 있다면 board[3][1]=true.
3. 새로운 사다리를 추가할 때 현재 사다리, 전 사다리, 후 사다리가 연결되어 있지 않다면 연결시켜줌.


*** 개선한 점 ***

처음에는 가로선을 0개 추가하는 경우부터 3개 추가하는 경우를 모두 탐색했더니,

시간이 2000ms로 너무 오래걸려서(정답은 통과),

0개 추가했을 때 i번 세로선이 i번이 나온다면 1개 ~3개 추가하는 경우는 탐색하지 않는 로직으로

변경하였더니, 시간이 많이 감소됨.

*/
#include <iostream>
#include <algorithm>
using namespace std;
bool board[31][11];
int N, M, H;//세로선, 가로선, 세로선마다 가로선을 놓을 수 있는 위치의 개수
int result = -1;
int limit;
void Input() {
	cin >> N >> M >> H;
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b; //H,N  , (b,b+1) 연결.
		board[a][b] = true;
	}
}
bool check() {
	for (int i = 1; i <= N; i++) {
		int idx = i;
		for (int j = 1; j <= H; j++) {
			if (board[j][idx]) {
				idx++;
			}
			else if (board[j][idx - 1]) {
				idx--;
			}
		}
		if (idx != i)
			return false;
	}
	return true;
}
void DFS(int idx, int cnt) {
	if (result!=-1) {
		return;
	}
	if (cnt == limit) {
		if (check()) {
			result = cnt;
		}
		return;
	}
	for (int i = idx; i < N; i++) {
		for (int j = 1; j <= H; j++) {
			if (board[j][i] || board[j][i - 1] || board[j][i + 1])
				continue;
			board[j][i] = true;
			DFS(i, cnt + 1);
			board[j][i] = false;
		}
	}
}
void Solution() {
	for (int i = 0; i < 4; i++) {
		limit = i;
		DFS(1, 0);
		if (result != -1)
			break;
	}
	cout << result << endl;
}
void Solve() {
	Input();
	Solution();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	Solve();
	return 0;
}