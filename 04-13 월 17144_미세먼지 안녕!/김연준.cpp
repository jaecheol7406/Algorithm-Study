/*
BOJ 17144��: �̼����� �ȳ�!
���� ���� : �ùķ��̼�

1. Speard(�̼����� Ȯ��)
	(1) ������ ���⿡ Ȯ���� �Ͼ�� �ӽ� �迭�� �� ���� ������Ų��.
	(2) ������ ���� Ȯ���� ������ �ӽ� �迭�� ���� �̼����� ���� ������Ų��.
	(3) Ȯ���� ������ ������ board�� copy�Ѵ�.
2. actAir(����û���� �۵�)
	(1) ���� �ٶ���, ���� û���� ��ǥ �� x���� ���� ��ǥ�� �������� �ݽð� Ȯ���Ѵ�.
		�Ʒ��� �ٶ���, ���� û���� ��ǥ �� x���� ū ��ǥ�� �������� �ð���� Ȯ���Ѵ�.

		Ȯ�� ��, �𼭸��� �����ϸ� ������ �ٲ��ش�.

		
*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int R, C, T;
int board[51][51];
int t_board[51][51];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
vector<pair<int, int>> aircleaner;
void Input() {
	cin >> R >> C >> T;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> board[i][j];
			if(board[i][j]==-1)
				aircleaner.push_back({ i,j });
		}
	}
}
void Spread() {
	memset(t_board, 0, sizeof(t_board));
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (board[i][j] == 0)
				continue;
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (nx < 0 || nx >= R || ny < 0 || ny >= C)
					continue;
				if (nx == aircleaner[0].first && ny == aircleaner[0].second)
					continue;
				if (nx == aircleaner[1].first && ny == aircleaner[1].second)
					continue;
				t_board[nx][ny] += board[i][j] / 5;
				cnt++;
			}
			t_board[i][j] += (board[i][j] - (board[i][j] / 5) * cnt);
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			board[i][j] = t_board[i][j];
		}
	}
}
void actAir() {
	//���� �ٶ�
	int start_x = aircleaner[0].first;
	int start_y = aircleaner[0].second;
	int dir = 2;
	int nx = start_x - 1;
	int ny = start_y;
	while (!(nx==start_x && ny==start_y+1)) {
		board[nx][ny] = board[nx + dx[dir]][ny + dy[dir]];
		nx = nx + dx[dir];
		ny = ny + dy[dir];
		if (nx == 0 && ny == 0 || nx == 0 && ny == C - 1 || nx == start_x && ny == C - 1)
			dir = (dir + 3) % 4;

	}
	board[nx][ny] = 0;
	//�Ʒ��� �ٶ�
	start_x = aircleaner[1].first;
	start_y = aircleaner[1].second;
	dir = 0;
	nx = start_x + 1;
	ny = start_y;
	while (!(nx == start_x && ny == start_y + 1)) {
		board[nx][ny] = board[nx + dx[dir]][ny + dy[dir]];
		nx = nx + dx[dir];
		ny = ny + dy[dir];
		if (nx == R-1 && ny == 0 || nx == R-1 && ny == C - 1 || nx == start_x && ny == C - 1)
			dir = (dir + 1) % 4;

	}
	board[nx][ny] = 0;
	
}
void Solution() {
	while (T--) {
		Spread();
		actAir();
	}
	int sum = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (board[i][j] == -1)
				continue;
			sum += board[i][j];
		}
	}
	cout << sum << endl;
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