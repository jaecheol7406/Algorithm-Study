#include <iostream>

using namespace std;
int board[20][20];
int command[1000];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };
int N, M,K;
int dice_x, dice_y;
int dice[7];
void Input() {
	cin >> N >> M >> dice_x >> dice_y >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 0; i < K; i++) {
		cin >> command[i];
	}
}
void Roll_DIce(int dir) {
	int tmp_dice[7];
	for (int i = 1; i <= 6; i++) {
		tmp_dice[i] = dice[i];
	}
	if (dir == 1) { //µ¿
		dice[1] = tmp_dice[4];
		dice[3] = tmp_dice[1];
		dice[6] = tmp_dice[3];
		dice[4] = tmp_dice[6];
	}
	else if (dir == 2) {//¼­
		dice[1] = tmp_dice[3];
		dice[4] = tmp_dice[1];
		dice[6] = tmp_dice[4];
		dice[3] = tmp_dice[6];
	}
	else if (dir == 3) {//ºÏ
		dice[1] = tmp_dice[5];
		dice[5] = tmp_dice[6];
		dice[6] = tmp_dice[2];
		dice[2] = tmp_dice[1];
	}
	else {//³²
		dice[1] = tmp_dice[2];
		dice[5] = tmp_dice[1];
		dice[6] = tmp_dice[5];
		dice[2] = tmp_dice[6];
	}

}
void Solution() {
	int x = dice_x;
	int y = dice_y;
	for (int i = 0; i < K; i++) {
		
		int nx = x + dx[command[i]-1];
		int ny = y + dy[command[i]-1];
		int dir = command[i];

		if (nx < 0 || nx >= N || ny < 0 || ny >= M)
			continue;
		Roll_DIce(dir);

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