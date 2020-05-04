/*
BOJ 16236��: �Ʊ� ���
���� ���� : �ùķ��̼�(BFS)


1. BFS�� ���� �� �ִ� �������� Ž��.
2. ���� �� �ִ� ������(fish_list)�� ���� 0�̸� ����.
3. 0�� �ƴϸ�, �� ������ ��������
	-> ���� ���� 2�̻� �̸� fish_list ����
		-> �Ÿ� �� ����, �Ÿ��� ������ x��ǥ�� ���� �� , �Ÿ��� x��ǥ�� ������ y��ǥ ���� ��
	-> fish_list�� ù��° ����⸦ �� ��� ����.

*/
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
struct shark {
	int x;
	int y;
	int size;
	int cnt;
};
struct fish {
	int x;
	int y;
	int dis;
};
bool visit[21][21];
int board[21][21];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
int N;
shark s;
vector<fish> fish_list;
bool cmp(fish& a, fish& b) {
	if (a.dis == b.dis) {
		if (a.x == b.x)
			return a.y < b.y;
		return a.x < b.x;
	}
	return a.dis < b.dis;

}
void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			if (board[i][j] == 9) {
				s.x = i;
				s.y = j;
				s.size = 2;
				s.cnt = 0;
				board[i][j] = 0;
			}
		}
	}
}
void BFS() {
	queue<fish> que;
	que.push({ s.x,s.y,0 });
	visit[s.x][s.y] = true;
	while (!que.empty()) {
		fish cur = que.front();
		que.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dx[i];
			int ny = cur.y + dy[i];
			int nd = cur.dis + 1;
			if (nx < 0 || nx >= N || ny < 0 || ny >= N)
				continue;
			if (visit[nx][ny])
				continue;
			if (board[nx][ny] > s.size)
				continue;
			else if (board[nx][ny] == s.size ||board[nx][ny]==0) {
				visit[nx][ny] = true;
				que.push({ nx,ny,nd });
			}
			else {
				visit[nx][ny] = true;
				que.push({ nx,ny,nd });
				fish_list.push_back({ nx,ny,nd });
			}
		}
	}
}
void Initialize() {
	fish_list.clear();
	memset(visit, 0, sizeof(visit));
}
void Solution() {
	int answer = 0;
	int c = 0;
	while (true) {
		Initialize();
		BFS();
		if (fish_list.size() == 0) {
			break;
		}
		else {
			if (fish_list.size() > 1) {
				//����
				sort(fish_list.begin(), fish_list.end(), cmp);
			}
			s.x = fish_list[0].x;
			s.y = fish_list[0].y;
			board[s.x][s.y] = 0;
			answer += fish_list[0].dis;
			if (++s.cnt == s.size) {
				s.cnt = 0;
				s.size++;
			}
		}
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
	cout.tie(NULL);
	Solve();
	return 0;
}