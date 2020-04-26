/*
BOJ 17825번: 주사위 윷놀이
문제 유형 : 시뮬레이션



1. 윷놀이 판의 경로 5가지를 설정.
	(1) 꺾지 않는 경우
	(2) 10에서 꺾는 경우
	(3) 20에서 꺾는 경우
	(4) 30에서 꺾는 경우
	(5) 25에서 꺾는 경우
2. 중복순열로 이동하는 말을 선택.
3. 각 말을 이동할 때, 꺾는 칸에 도달하면 조건에 맞게 말의 위치를 변경한다.
	(1) 만약, 해당 경로의 도착하면 그 말의 finish변수를 true로 설정하여 끝났다는 체크를 해줌.
	(2) 이동 후 말이 도착 칸이 아니면 다른 말들의 좌표와 비교한다.
		-> 같은 위치라면 더이상 진행하지 않고 종료

<!-- 주의사항 -->
0번 경로의 40과, 4번 경로의 40이 같은 위치인 것을 체크해야함.


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
			else if (y == 20) { //0번 경로의 40이면 4번경로의 40으로 바꿔줌.
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