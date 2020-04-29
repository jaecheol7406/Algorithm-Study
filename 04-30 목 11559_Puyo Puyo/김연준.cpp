/*
BOJ 11559번: Puyo Puyo
문제 유형 : 시뮬레이션(BFS)

1. BFS로 탐색하여 뿌요가 4개 이상이 되서 터질 수 있는지 확인.
	(1) 같은 색의 뿌요들을 delete_list에 저장하여,
		delete_list의 사이즈가 4 이상이면 터질 수 있음(true를 반환)

2. board의 모든 좌표를 탐색하면서 BFS가 한번이라도 true라면, 뿌요들이 내려옴(gravity)
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