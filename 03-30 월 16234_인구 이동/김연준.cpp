/*
BOJ 16234��: �α� �̵�
���� ���� : �ùķ��̼�, BFS

function call : main()->solve()->Input()->Solution()->BFS();

���� Ǯ�� : 1. BFS�� ����ؼ� ���漱�� �����ϴ� �� ���� Ž���Ѵ�.
			2. BFSŽ����, �� ������ �α� ���̰� L�� �̻�, R�� ���϶�� �� ������ ��ǥ�� vector�� ���� ����.
			3. vector�� ����� 2 �̻��̸� �α� �̵��� ����ǹǷ�, �α��� �̵���Ų��.
			4. �ѹ��̶� �α��̵��� ����Ǿ����� flag�� true���� �Է��Ͽ�, ���� �α� �̵��� ����ǰ� �Ѵ�.
			5. ��� ��ǥ�� �湮 ��, �� �̻� �α� �̵��� ������� ������ ����.

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