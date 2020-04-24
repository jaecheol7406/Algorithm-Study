/*
SWEA 2112번 : 보호 필름
문제유형 : 시뮬레이션(DFS)

1. DFS 조합으로 막을 선택하고, 약품 A를 넣을지 B를 넣을지 정함.(DFS의 반복문)
	(1) 막과 약품을 선택했으면 해당 막에 약품을 투여함(Change(x,med,true))
	(2) 재귀가 return되었으면, 해당 막을 복구 시킴(Change(x,med,false))

2. 성능검사(Check())


<!-- 조심할 것 -->
D의 범위가 최대 13이라서, 시간초과 발생.

DFS에서 약을 투여하는 막을 선택한 횟수(cnt)가 result보다 커지면 해당 재귀는 멈춰야함.
(최소값을 구하는 문제이므로 이미 정답이 된 횟수보다 더 많은 막에 약을 투여하는 재귀는 할 필요 없음.)
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
int N, M, K, result;
int board[14][21];
int t_board[14][21];
bool visit[14];
vector<int> v;
void Input() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
			t_board[i][j] = board[i][j];
		}
	}

}
void Initialize() {
	memset(board, 0, sizeof(board));
	memset(t_board, 0, sizeof(t_board));
	result = 987654321;
}
bool Check() {
	for (int i = 0; i < M; i++) { //A는 0, B는 1
		int cnt = 1;
		bool flag = false;
		for (int j = 0; j < N - 1; j++) {
			if (board[j][i] == board[j + 1][i]) {
				cnt++;
			}
			else
				cnt = 1;
			if (cnt >= K) {
				flag = true;
				break;
			}
		}
		if (!flag) { //통과 실패
			return false;
		}
	}
	return true;
}
void Change(int x, int med, bool f) {
	if (f) { //투여
		for (int i = 0; i < M; i++) {
			board[x][i] = med;
		}
	}
	else {//복구
		for (int i = 0; i < M; i++) {
			board[x][i] = t_board[x][i];
		}
	}
}
void DFS(int idx, int cnt) {
	if (cnt >= result)
		return;
	if (Check()) {
		result = min(result, cnt);
		return;
	}
	for (int i = idx; i < N; i++) { //막 선택
		if (visit[i])
			continue;
		visit[i] = true;
		for (int j = 0; j < 2; j++) { //약 선택
			//약품투여
			Change(i, j, true);
			DFS(i, cnt + 1);
			Change(i, j, false);
			//원상복귀
		}
		visit[i] = false;
	}
}
void Solution() {
	DFS(0, 0);
}
void Solve() {
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Initialize();
		Input();
		Solution();
		cout << "#" << i << " " << result << endl;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}