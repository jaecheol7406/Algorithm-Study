/*
BOJ 14503: �κ� û�ұ�
���� ���� : �ùķ��̼�

1. �κ��� ���� ��ġ�� û�� ���� ���̶�� û���Ѵ�(��ǥ�� ���� 2�� �ٲ�)
2. 4������ Ž���ؼ� û�� ���� ���� ã�´�.
	(1) û�� ���� ���� ������ ��ǥ�� �ٲ�.
3. 4���� �� û�ҵǾ������� �κ��� ���� ��Ų ��ǥ�� ������ ���� ���̸� ������.

*/
#include <iostream>

using namespace std;
int board[51][51];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int N, M;
int robot_x, robot_y, dir;
void Input() {
	cin >> N >> M;
	cin >> robot_x >> robot_y >> dir;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
}
void Solution() {
	int cnt = 0;
	while (true) {
		if (board[robot_x][robot_y] == 0) {
			board[robot_x][robot_y] = 2;
			cnt++;
		}
		bool flag = false;
		for (int i = 0; i < 4; i++) {
			dir = (dir + 3) % 4;
			int nx = robot_x + dx[dir];
			int ny = robot_y + dy[dir];
			if (board[nx][ny]==0) {
				robot_x = nx;
				robot_y = ny;
				flag = true;
				break;
			}
		}
		if (!flag) {
			robot_x = robot_x + dx[(dir + 2) % 4];
			robot_y = robot_y + dy[(dir + 2) % 4];
			if (board[robot_x][robot_y] == 1) {
				break;
			}
		}
	}
	cout << cnt << endl;
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