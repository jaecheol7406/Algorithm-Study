/*
BOJ 16234번: 인구 이동
문제 유형 : 시뮬레이션, BFS

function call : main()->solve()->Input()->Solution()->BFS();

문제 풀이 : 1. BFS를 사용해서 국경선을 공유하는 두 나라를 탐색한다.
			2. BFS탐색시, 두 나라의 인구 차이가 L명 이상, R명 이하라면 그 나라의 좌표를 vector에 따로 저장.
			3. vector의 사이즈가 2 이상이면 인구 이동이 진행되므로, 인구를 이동시킨다.
			4. 한번이라도 인구이동이 진행되었으면 flag에 true값을 입력하여, 다음 인구 이동이 진행되게 한다.
			5. 모든 좌표를 방문 후, 더 이상 인구 이동이 진행되지 않으면 종료.

*/

#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
int N, L, R;
int board[50][50];
bool visit[50][50];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
void Input() {
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
}
bool BFS(int x, int y) {
	queue<pair<int, int>> que;
	que.push(make_pair(x, y));
	visit[x][y] = true;
	int sum = board[x][y];
	vector<pair<int, int>> lists;
	lists.push_back(make_pair(x, y));
	while (!que.empty()) {
		auto cur = que.front();
		que.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.first + dx[i];
			int ny = cur.second + dy[i];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N)
				continue;
			if (visit[nx][ny])
				continue;
			int diffNum = abs(board[cur.first][cur.second] - board[nx][ny]);
			if (diffNum >= L && diffNum <= R) {
				que.push(make_pair(nx, ny));
				lists.push_back(make_pair(nx, ny));
				visit[nx][ny] = true;
				sum += board[nx][ny];
			}
		}
	}

	if (lists.size() >= 2) {
		int newNum = sum / lists.size();
		for (int i = 0; i < lists.size(); i++) {
			int x = lists[i].first;
			int y = lists[i].second;
			board[x][y] = newNum;
		}
		return true;
	}
	return false;
}
void Solution() {
	int answer = 0;
	while (true) {
		memset(visit, 0, sizeof(visit));
		bool flag = false;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!visit[i][j])
					if (BFS(i, j)) {
						flag = true;
					}
			}
		}
		if (!flag) {
			cout << answer << endl;
			return;
		}
		answer++;
	}
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