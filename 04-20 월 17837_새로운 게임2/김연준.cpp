/*
BOJ 17837번: 새로운 게임2

문제 유형 : 시뮬레이션

1. 각 칸의 색을 저장할 int형 이차원 배열과, 각 칸에 있는 말의 정보를 저장할 vector<int>형 이차원 배열을 사용
2. 말이 움직일 때, 그 칸(x,y)에 있는 말의 인덱스 넘버를 찾고, 그 인덱스 부터 end()까지 존재하는 말 들을
	다음 칸(nx,ny)에 추가시킨다. (x,y)칸에 있는 인덱스 부터 end()까지 erase한다.
3. 다음 칸이 blue이거나 맵을 벗어난다면 방향을 바꾸고 다시 2번을 수행.
	단, 또 blue 칸이라면 움직이지 않는다.




!! vector erase함수 사용 시, vector.erase(position, end()) 하면 통째로 삭제 가능. !!
for문을 사용해서 erase하면 인덱스 오류 범하기 쉬운데, 앞으로 이런 방식으로 vector.erase하자.

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
	for (int i = 0; i < chess_map[x][y].size(); i++) { //해당 칸의 움직이는 말 찾기.
		if (chess_map[x][y][i] == num) {
			idx = i;
		}
	}
	for (int i = idx; i < chess_map[x][y].size(); i++) { //다음 칸에 추가
		chess_map[nx][ny].push_back(chess_map[x][y][i]);
		horse_list[chess_map[x][y][i]].x = nx;
		horse_list[chess_map[x][y][i]].y = ny;
	}
	chess_map[x][y].erase(chess_map[x][y].begin() + idx, chess_map[x][y].end());

}
void move_red(int num, int x, int y, int nx, int ny) {
	int idx = 0;
	for (int i = 0; i < chess_map[x][y].size(); i++) { //해당 칸의 움직이는 말 찾기.
		if (chess_map[x][y][i] == num) {
			idx = i;
		}
	}
	reverse(chess_map[x][y].begin() + idx, chess_map[x][y].end());
	for (int i = idx; i < chess_map[x][y].size(); i++) { //다음 칸에 추가
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
			else if (board[nx][ny] == 0) {//흰
				move_white(i, x, y, nx, ny);
			}
			else if (board[nx][ny] == 1) { //빨
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