/*
BOJ 14889번: 스타트와 링크
문제 유형 : 브루트포스

1. DFS로 스타트팀과 링크팀을 나눈다.
2. 각 팀의 능력치를 구해서 최소값을 도출한다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N;
int board[21][21];
bool visit[21];
vector<int> start;
vector<int> link;
int answer = 987654321;
void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}

}
void calc() {
	int start_sum = 0;
	int link_sum = 0;
	for (int i = 0; i < start.size()-1; i++) {
		for (int j = i + 1; j < start.size(); j++) {
			start_sum += board[start[i]][start[j]] + board[start[j]][start[i]];
			link_sum += board[link[i]][link[j]] + board[link[j]][link[i]];
		}
	}
	answer = min(answer, abs(start_sum - link_sum));
}
void DFS(int idx, int cnt) {
	if (cnt == N / 2) {
		start.clear();
		link.clear();
		for (int i = 0; i < N; i++) {
			if (visit[i]) {
				start.push_back(i);
			}
			else
				link.push_back(i);
		}
		calc();

		return;
	}
	for (int i = idx; i < N; i++) {
		if (visit[i])
			continue;
		visit[i] = true;
		DFS(i, cnt + 1);
		visit[i] = false;
	}
}
void Solution() {
	DFS(0, 0);
	cout << answer << endl;
}
void Solve() {
	Input();
	Solution();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}