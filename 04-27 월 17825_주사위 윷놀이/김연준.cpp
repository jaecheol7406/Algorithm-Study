/*
BOJ 17825��: �ֻ��� ������
���� ���� : �ùķ��̼�



1. ������ ���� ��� 5������ ����.
	(1) ���� �ʴ� ���
	(2) 10���� ���� ���
	(3) 20���� ���� ���
	(4) 30���� ���� ���
	(5) 25���� ���� ���
2. �ߺ������� �̵��ϴ� ���� ����.
3. �� ���� �̵��� ��, ���� ĭ�� �����ϸ� ���ǿ� �°� ���� ��ġ�� �����Ѵ�.
	(1) ����, �ش� ����� �����ϸ� �� ���� finish������ true�� �����Ͽ� �����ٴ� üũ�� ����.
	(2) �̵� �� ���� ���� ĭ�� �ƴϸ� �ٸ� ������ ��ǥ�� ���Ѵ�.
		-> ���� ��ġ��� ���̻� �������� �ʰ� ����

<!-- ���ǻ��� -->
0�� ����� 40��, 4�� ����� 40�� ���� ��ġ�� ���� üũ�ؾ���.


*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct info {
	int x;
	int y;
	bool finish;
};
int cmd[10];
int visit[10];
int result = 0;
vector<info> player_list(4);
vector<vector<int>> board{{0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,0},
						  {10,13,16,19,25},
						  {20,22,24,25},
						  {30,28,27,26,25},
						  {25,30,35,40,0}};
void Input() {
	for (int i = 0; i < 10; i++) {
		cin >> cmd[i];
	}
}
void Play() {
	int answer = 0;
	for (int i = 0; i < 4; i++) {
		player_list[i].x = 0;
		player_list[i].y = 0;
		player_list[i].finish = false;
	}
	int player,x, y, nx, ny;
	for (int i = 0; i < 10; i++) {
		player = visit[i];
		if (player_list[player].finish)
			return;
		x = player_list[player].x;
		y = player_list[player].y + cmd[i];
		if (x == 0) {
			if (y == 5) {
				x = 1;
				y = 0;
			}
			else if (y == 10) {
				x = 2;
				y = 0;
			}
			else if (y == 15) {
				x = 3;
				y = 0;
			}
			else if (y == 20) { //0�� ����� 40�̸� 4������� 40���� �ٲ���.
				x = 4;
				y = 3;
			}
			else if (y >= 21) {
				player_list[player].finish = true;
				continue;
			}
		}
		else if (x == 1||x==3) {
			if (y >= 4) {
				x = 4;
				y = y - 4;
				if (y >= 4) {
					player_list[player].finish = true;
					continue;
				}
			}
		}
		else if (x == 2) {
			if (y >= 3) {
				x = 4;
				y = y - 3;
				if (y >= 4) {
					player_list[player].finish = true;
					continue;
				}
			}
		}
		else if (x == 4) {
			if (y >= 4) {
				player_list[player].finish = true;
				continue;
			}
		}
		for (int j = 0; j < 4; j++) {
			if (player == j || player_list[j].finish)
				continue;
			if (x == player_list[j].x &&y == player_list[j].y)
				return;
		}
		answer += board[x][y];
		player_list[player].x = x;
		player_list[player].y = y;
	}
	result = max(result, answer);
}
void DFS(int cnt) {
	if (cnt == 10) {
		Play();
		return;
	}
	for (int i = 0; i < 4; i++) {
		visit[cnt] = i;
		DFS(cnt + 1);
	}
}
void Solution() {
	DFS(0);
	cout << result << endl;
}
void Solve() {
	Input();
	Solution();
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}