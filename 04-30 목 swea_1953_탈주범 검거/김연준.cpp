/*
SWEA 1953��: Ż�ֹ� �˰�
���� ���� : �ùķ��̼�(BFS)

1. �� ���� �ͳ��� �̵��� �� �ִ� ���� ������ vector<vector<int>> dir�� �Է�.
2. BFS�� Ž��
3. �ش� ��ǥ�� �̵� �� ��ǥ�� ����Ǿ��ִ��� Ȯ��(IsPossible())
	-> ���� �̵��ϰ� �ִ� ����� ���� �ͳο����� ������ �ݴ뿩�� ����Ǿ� �����Ƿ�
		������ 180�� ȸ���ϰ�, ���� �ͳ��� ȸ���� ������ �����ϰ� �ִ��� Ȯ���Ѵ�.


*/
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
int N, M, start_x, start_y, L;
int board[51][51];
bool visit[51][51];
int answer;
int dx[4] = { 1,0,-1,0 }; // ��,��,��,��
int dy[4] = { 0,1,0,-1 };
vector<vector<int>> dir{ {}, {0,1,2,3},{0,2},{1,3},{1,2},{0,1},{0,3},{2,3} };
void Input() {
	cin >> N >> M >> start_x >> start_y >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
}
void Initialize() {
	memset(visit,0, sizeof(visit));
	answer = 1;
}
bool IsPossible(int d, int x,int y) {
	d = (d + 2) % 4; //�ݴ� �������� �ٲ�
	int type = board[x][y];
	for (int i = 0; i < dir[type].size(); i++) {
		if (dir[type][i] == d)
			return true;
	}
	return false;
}
void BFS() {
	queue<pair<pair<int, int>,int>> que;
	que.push({ { start_x,start_y },0 });
	visit[start_x][start_y] = true;

	while (!que.empty()) {
		int x = que.front().first.first;
		int y = que.front().first.second;
		int time = que.front().second;
		int type = board[x][y];
		que.pop();
		if (time >= L-1)
			break;
		for (int i = 0; i < dir[type].size(); i++) {
			int nd = dir[type][i];
			int nx = x + dx[nd];
			int ny = y + dy[nd];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M)
				continue;
			if (visit[nx][ny])
				continue;
			if (!IsPossible(nd, nx, ny))
				continue;
			visit[nx][ny] = true;
			que.push({ {nx,ny},time + 1 });
			answer++;
		}
		
	}
}
void Solution() {
	BFS();
}
void Solve() {
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Initialize();
		Input();
		Solution();
		cout << "#" << i << " " << answer << endl;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}