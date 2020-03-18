/*
BOJ 3190번: 뱀
문제 유형 : 시뮬레이션
문제 풀이 : 
			1. 해당 좌표에 사과가 있는지 없는지 와 뱀의 몸이 존재하는지 아닌지를 bool형 이차원 배열을 통해 판별한다.
			2. 뱀의 머리를 push하고, 뱀의 꼬리를 pop을 해야하므로 deque를 사용해서 뱀의 이동경로를 저장한다.
			3. 뱀의 머리를 기준으로 다음 칸이 벽인지, 자기 몸인지 확인
			4. 사과가 있는 곳인지 아닌지 확인
			5. 사과가 있다면 뱀의 이동경로에 머리 추가, visit 방문 true로 변경, 사과 없앰
			6. 사과가 없다면 뱀의 이동경로에 머리 추가, 꼬리 삭제, 머리 좌표 visit, 꼬리 좌표 !visit
			7. 방향 변경이 필요하면 변경

*/

#include <iostream>
#include <deque>
#include <vector>
using namespace std;
int N, K, L;
bool board[101][101];
bool visit[101][101];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
vector<pair<int, char>> dirInfo;
deque<pair<int, int>> snake;
void Input() {
	cin >> N >> K;
	int x, y;
	for (int i = 0; i < K; i++) {
		cin >> x >> y;
		board[x][y] = true;
	}
	cin >> L;
	int X;
	char C;
	for (int i = 0; i < L; i++) {
		cin >> X >> C;
		dirInfo.push_back(make_pair(X, C));
	}

}
int Chage_Dir(int dir, char C) {
	if (C == 'L') { //왼쪽 회전
		dir = (dir + 3) % 4;
	}
	else { //오른쪽 회전
		dir = (dir + 1) % 4;
		
	}
	return dir;
}
void Solution() {
	snake.push_back(make_pair(1, 1));
	visit[1][1] = true;
	int dir = 0;
	int time = 0;
	int dirInfo_cnt = 0;
	while (true) {
		time++;
		auto cur = snake.front();
		int nx = cur.first + dx[dir];
		int ny = cur.second + dy[dir];
		//cout << nx << " " << ny << endl;
		if (nx<1 || nx>N || ny<1 || ny>N) //벽에 부딪힘
			break;
		if (visit[nx][ny] == true) //자기자신에 부딪힘
			break;

		if (board[nx][ny] == true) { //다음칸에 사과가 있다면
			board[nx][ny] = false;
			snake.push_front(make_pair(nx, ny));
			visit[nx][ny] = true;
		}
		else { //다음칸에 사과가 없다면
			snake.push_front(make_pair(nx, ny));
			visit[nx][ny] = true;
			visit[snake.back().first][snake.back().second] = false;
			snake.pop_back();

		}
		if (dirInfo_cnt < dirInfo.size()) {
			if (dirInfo[dirInfo_cnt].first == time) {
				dir = Chage_Dir(dir, dirInfo[dirInfo_cnt].second);
				dirInfo_cnt++;
			}
		}
	}
	cout << time << endl;
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