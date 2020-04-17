/*
BOJ 17837��: ���ο� ����2

���� ���� : �ùķ��̼�

1. �� ĭ�� ���� ������ int�� ������ �迭��, �� ĭ�� �ִ� ���� ������ ������ vector<int>�� ������ �迭�� ���
2. ���� ������ ��, �� ĭ(x,y)�� �ִ� ���� �ε��� �ѹ��� ã��, �� �ε��� ���� end()���� �����ϴ� �� ����
	���� ĭ(nx,ny)�� �߰���Ų��. (x,y)ĭ�� �ִ� �ε��� ���� end()���� erase�Ѵ�.
3. ���� ĭ�� blue�̰ų� ���� ����ٸ� ������ �ٲٰ� �ٽ� 2���� ����.
	��, �� blue ĭ�̶�� �������� �ʴ´�.




!! vector erase�Լ� ��� ��, vector.erase(position, end()) �ϸ� ��°�� ���� ����. !!
for���� ����ؼ� erase�ϸ� �ε��� ���� ���ϱ� ���, ������ �̷� ������� vector.erase����.

*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct horse {
	int x;
	int y;
	int dir;
};
int N, K;
int board[15][15];
int dx[5] = { 0,0,0,-1,1 };
int dy[5] = { 0,1,-1,0,0 };
vector<int> chess_map[15][15];
vector<horse> horse_list;
void Input() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 0; i < K; i++) {
		horse input;
		cin >> input.x >> input.y >> input.dir;
		horse_list.push_back(input);
		chess_map[input.x][input.y].push_back(i);
	}
}
int dir_change(int dir) {
	if (dir == 1)
		return 2;
	else if (dir == 2)
		return 1;
	else if (dir == 3)
		return 4;
	else
		return 3;
}
void move_white(int num, int x,int y,int nx,int ny) {
	int idx=0;
	for (int i = 0; i < chess_map[x][y].size(); i++) { //�ش� ĭ�� �����̴� �� ã��.
		if (chess_map[x][y][i] == num) {
			idx = i;
		}
	}
	for (int i = idx; i < chess_map[x][y].size(); i++) { //���� ĭ�� �߰�
		chess_map[nx][ny].push_back(chess_map[x][y][i]);
		horse_list[chess_map[x][y][i]].x = nx;
		horse_list[chess_map[x][y][i]].y = ny;
	}
	chess_map[x][y].erase(chess_map[x][y].begin() + idx, chess_map[x][y].end());

}
void move_red(int num, int x, int y, int nx, int ny) {
	int idx = 0;
	for (int i = 0; i < chess_map[x][y].size(); i++) { //�ش� ĭ�� �����̴� �� ã��.
		if (chess_map[x][y][i] == num) {
			idx = i;
		}
	}
	reverse(chess_map[x][y].begin() + idx, chess_map[x][y].end());
	for (int i = idx; i < chess_map[x][y].size(); i++) { //���� ĭ�� �߰�
		chess_map[nx][ny].push_back(chess_map[x][y][i]);
		horse_list[chess_map[x][y][i]].x = nx;
		horse_list[chess_map[x][y][i]].y = ny;
	}
	chess_map[x][y].erase(chess_map[x][y].begin() + idx, chess_map[x][y].end());

}
void move_blue(int num, int x, int y) {
	horse_list[num].dir = dir_change(horse_list[num].dir);
	int nx = x + dx[horse_list[num].dir];
	int ny = y + dy[horse_list[num].dir];
	if (nx<1 || nx>N || ny<1 || ny >N || board[nx][ny]==2)
		return;
	if (board[nx][ny] == 0) {
		move_white(num, x, y, nx, ny);
	}
	else if (board[nx][ny] == 1) {
		move_red(num, x, y, nx, ny);
	}
}
void Solution() {
	int time = 0;
	int answer = -1;
	int x, y, nx, ny;
	bool flag=false;
	while (++time <= 1000) {
		for (int i = 0; i < K; i++) {
			int x = horse_list[i].x;
			int y = horse_list[i].y;
			int nx = x + dx[horse_list[i].dir];
			int ny = y + dy[horse_list[i].dir];
			if (nx<1 || nx>N || ny<1 || ny>N || board[nx][ny] == 2) {
				move_blue(i, x, y);
				nx = x + dx[horse_list[i].dir];
				ny = y + dy[horse_list[i].dir];
			}
			else if (board[nx][ny] == 0) {//��
				move_white(i, x, y, nx, ny);
			}
			else if (board[nx][ny] == 1) { //��
				move_red(i, x, y, nx, ny);
			}

			if (chess_map[nx][ny].size() >= 4) {
				answer = time;
				flag = true;
				break;
			}
		}
		if (flag)
			break;
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