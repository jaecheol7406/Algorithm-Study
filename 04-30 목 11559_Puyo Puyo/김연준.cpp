/*
BOJ 11559��: Puyo Puyo
���� ���� : �ùķ��̼�(BFS)

1. BFS�� Ž���Ͽ� �ѿ䰡 4�� �̻��� �Ǽ� ���� �� �ִ��� Ȯ��.
	(1) ���� ���� �ѿ���� delete_list�� �����Ͽ�,
		delete_list�� ����� 4 �̻��̸� ���� �� ����(true�� ��ȯ)

2. board�� ��� ��ǥ�� Ž���ϸ鼭 BFS�� �ѹ��̶� true���, �ѿ���� ������(gravity)
*/
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

char board[12][6];
bool visit[12][6];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
vector<pair<int, int>> delete_list;
int answer = 0;
void Input() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			cin >> board[i][j];
		}
	}
}
bool BFS(int x, int y) {
	queue<pair<int, int>> que;
	que.push({ x,y });
	visit[x][y] = true;
	delete_list.clear();
	delete_list.push_back({ x,y });
	while (!que.empty()) {
		auto cur = que.front();
		que.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.first + dx[i];
			int ny = cur.second + dy[i];
			if (nx < 0 || ny >= 12 || ny < 0 || ny >= 6)
				continue;
			if (visit[nx][ny])
				continue;
			if (board[nx][ny] == board[x][y]) {
				visit[nx][ny] = true;
				que.push({ nx,ny });
				delete_list.push_back({ nx,ny });
			}
		}
	}
	if (delete_list.size() >= 4) {
		for (int i = 0; i < delete_list.size(); i++) {
			board[delete_list[i].first][delete_list[i].second] = '.';
		}
		return true;
	}
	return false;
}
void gravity() {
	for (int i = 0; i < 6; i++) {
		for (int j = 10; j >= 0; j--) {
			if (board[j][i] == '.')
				continue;
			for (int k = j + 1; k < 12; k++) {
				if (board[k][i] == '.') {
					board[k][i] = board[k - 1][i];
					board[k - 1][i] = '.';
				}
				else
					break;
			}
		}
	}
}
void print() {
	cout << "Puyo Puyo " << endl;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}
void Solution() {
	while (true) {
		memset(visit, 0, sizeof(visit));
		bool flag = false;
		for (int i = 11; i >= 0; i--) {
			for (int j = 0; j < 6; j++) {
				if (visit[i][j] || board[i][j] == '.')
					continue;
				if (BFS(i, j)) {
					flag = true;
				}
			}
		}
		if (!flag)
			break;
		gravity();
		answer++;
	}
	cout << answer << endl;
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