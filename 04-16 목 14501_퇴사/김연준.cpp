/*
BOJ 14501번: 퇴사
Main()=>Solve()->Input()->DFS();
1. 상담 완료하고, 그 후로 넘어가거나
2. 상담 하지 않고 다음 날로 넘어간다.
위 두 가지 case에 대해 DFS 탐색.
*/

#include <iostream>
#include <algorithm>
using namespace std;
int N;
int board[16][2];
bool visit[16];
int answer = 0;
void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> board[i][0] >> board[i][1];
	}

}
void DFS(int idx, int money) {
	if (idx==N+1) {
		answer = max(answer, money);
		return;
	}
	if (idx + board[idx][0] <= N + 1) {
		DFS(idx + board[idx][0], money + board[idx][1]);
	}
	if (idx + 1 <= N+1) {
		DFS(idx + 1, money);
	}
}

void Solve() {
	Input();
	DFS(1, 0);
	cout << answer << endl;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}