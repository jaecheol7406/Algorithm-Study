/*
BOJ 14499번: 주사위 굴리기
문제 유형 : 시뮬레이션
main()->solve()->input()->solution()->play();
1. 주사위 각 면의 값을 dice[7] 배열로 관리.
2. 명령에 따라 주사위의 값을 갱신.
	ex) 주사위 명령이 4(남쪽)이라면, 주사위의 윗면의 값은 주사위 뒷면의 값이 되고, 앞면의 값은 윗면의 값, 밑면의 값은 앞면의 값, 뒷면의 값은 밑면의 값
3. 윗면(dice[1]) 값 출력
*/

#include <iostream>

using namespace std;
int N, M;
int board[21][21];
int dx[5] = { 0,0,0,-1,1 };
int dy[5] = { 0,1,-1,0,0 };
int cmd[1000];
int dice[7] = { 0, };
int top = 1;
int x, y, k;
void Input() {
	cin >> N >> M >> x >> y >> k;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 0; i < k; i++) {
		cin >> cmd[i];
	}
}
void play(int c) {
	int t_dice[7];
	for (int i = 1; i <= 6; i++) {
		t_dice[i] = dice[i];
	}
	if (c == 1) {
		dice[1] = t_dice[4];
		dice[3] = t_dice[1];
		dice[6] = t_dice[3];
		dice[4] = t_dice[6];
	}
	else if (c == 2) {
		dice[1] = t_dice[3];
		dice[4] = t_dice[1];
		dice[6] = t_dice[4];
		dice[3] = t_dice[6];
	}
	else if (c == 3) {
		dice[2] = t_dice[1];
		dice[1] = t_dice[5];
		dice[5] = t_dice[6];
		dice[6] = t_dice[2];
	}
	else {
		dice[1] = t_dice[2];
		dice[5] = t_dice[1];
		dice[6] = t_dice[5];
		dice[2] = t_dice[6];
	}
}
void Solution() {
	for (int i = 0; i < k; i++) {
		int nx = x + dx[cmd[i]];
		int ny = y + dy[cmd[i]];
		if (nx < 0 || nx >= N || ny < 0 || ny >= M)
			continue;
		play(cmd[i]);
		if (board[nx][ny] == 0) {
			board[nx][ny] = dice[6];
		}
		else {
			dice[6] = board[nx][ny];
			board[nx][ny] = 0;
		}
		x = nx;
		y = ny;
		cout << dice[1] << endl;

	}
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