/*
Swea 2105: ����Ʈ ī��

�������� : �ùķ��̼�, ����Ž��

1. DFS�� ����ؼ� ����Ž��, 0����� ���� ���Ͽ� ������ ���� N-3�� ������ �ݺ��ϸ� ��, 0���� N-1�� ���� ������ ���� �� ����.
2. DFS Ž�� ��, �� ��ǥ���� ���� ������ ���� �� �����̴�.
	(1) ������� ����
	(2) ������⿡�� 90�� ����(���� ��ǥ�� 3�� �� ���� ���� ���̻� ��������)
3. ���� ��ǥ(nx,ny)�� ���� ��ǥ(start_x,start_y)���� Ȯ���ϴ� ���ǹ� �ʿ� 
	(start_x,start_y�� �̹� �湮 üũ�Ǿ��� ������)
3. DFS Ž���ϴ� ���� ��ǥ�� �����ϸ� ��� ����.
*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int N;
int board[20][20];
int dx[4] = { 1,1,-1,-1 };
int dy[4] = { 1,-1,-1,1 };
bool visit[101];
int result,start_x, start_y;
void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
}
void Initialize() {
	memset(board, 0, sizeof(board));
	memset(visit, 0, sizeof(visit));

	result = -1;
}
void DFS(int x, int y, int dir, int cnt) {
	if (x == start_x && y == start_y && cnt > 1) {
		result = max(result, cnt);
		return;
	}
	for (int i = 0; i < 2; i++) {
		int nx, ny, nd;
		if (i == 0) {
			nd = dir;
		}
		else {
			if ((x == start_x && y == start_y) || dir == 3)
				continue;
			nd = dir + 1;
		}
		nx = x + dx[nd];
		ny = y + dy[nd];
		if (nx == start_x && ny == start_y) {
			DFS(nx, ny, nd, cnt);
			continue;
		}
		if (nx < 0 || nx >= N || ny < 0 || ny >= N)
			continue;
		if (visit[board[nx][ny]])
			continue;
		visit[board[nx][ny]] = true;
		DFS(nx, ny, nd, cnt + 1);
		visit[board[nx][ny]] = false;
	}
}
void Solution() {
	for (int i = 0; i < N - 2; i++) {
		for (int j = 1; j < N - 1; j++) {
			visit[board[i][j]] = true;
			start_x = i;
			start_y = j;
			DFS(i, j, 0, 1);
			visit[board[i][j]] = false;
		}
	}
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