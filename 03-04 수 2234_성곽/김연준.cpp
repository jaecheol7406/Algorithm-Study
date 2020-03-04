/*
BOJ 2234번: 성곽
문제 유형 : BFS
어려웠던 점 : 하나의 벽을 제거하여 얻을 수 있는 가장 넓은 방의 크기를 구할 때 각 방에 대해서 인접한 방을 구하고 ,
              인접한 방들에 대해서 최댓값을 찾으려고 하였으나 너무 복잡해져서 풀지 못함.
			  블로그 보고 비트마스킹에 대한 힌트를 얻고 다시 품.

문제 풀이
1. BFS로 탐색하여 방의 개수와 가장 넓은 방의 넓이를 구함
   ->BFS로 탐색 시, 비트마스킹을 사용하여 상하좌우에 대하여 벽이 있는지 없는 지 판단 한다.

2. 각 칸에 대해서 벽을 한 개씩 제거한다음 BFS 탐색을 통해 방의 넓이를 구한다.
   -> 벽을 한 개씩 제거할 때 비트마스킹을 사용한다. ex) 1011(2)이면  1011 & (0001 or 0010 or 0100 or 1000) 을 수행하여 상하좌우에 벽이 있는지 확인한다.
   -> 벽이 존재한다면 board[i][j] -= (1or 2 or 4 or 8)을 하여 벽을 허물고 BFS 탐색 후 다시 board[i][j] += (1 or 2 or 3 or 4)를 하여 벽을 생성.
*/
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
int N, M;
int board[51][51];
bool visit[51][51];
int dx[4] = { 0,-1,0,1 }; //서 북 동 남 순
int dy[4] = { -1,0,1,0 };
int max_area = 0;
int cnt = 0;
vector<int> dir;
void Input() {
	cin >> N >> M; //7 4
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}
}
void check_dir(int x, int y) { //벽에 대한 정보 추출
	int val = board[x][y];
	dir.clear();
	while (val != 0) {
		dir.push_back(val % 2);
		val /= 2;
	}
	while (dir.size() != 4) { 
		dir.push_back(0);
	}
}
void BFS(int x, int y) {
	queue<pair<int, int>> que;
	que.push(make_pair(x, y));
	visit[x][y] = true;
	int area = 0;
	while (!que.empty()) {
		area++;
		auto cur = que.front();
		que.pop();
		//check_dir(cur.first, cur.second);
		int bit = 1;
		for (int i = 0; i < 4; i++) {
			//if (dir[i] == 1) //벽을 지날 수 없음
				//continue;
			if ((board[cur.first][cur.second] & bit) != bit) {
				int nx = cur.first + dx[i];
				int ny = cur.second + dy[i];
				if (nx >= 1 && nx <= M && ny >= 1 && ny <= N) {
					if (visit[nx][ny] == false) {
						que.push(make_pair(nx, ny));
						visit[nx][ny] = true;
					}
				}
			}
			bit *= 2;
			
		}
	}
	if (max_area < area)
		max_area = area;
	
}
void Solution() {

	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			if (visit[i][j] == true)
				continue;
			cnt++;
			BFS(i, j);
		}
	}

	cout << cnt << endl;
	cout << max_area << endl;
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			for (int bit = 1; bit <= 8; bit *= 2) {
				if ((board[i][j] & bit) == bit) {
					memset(visit, 0, sizeof(visit));
					board[i][j] -= bit;
					BFS(i, j);
					board[i][j] += bit; 
				}
			}
		}
	}
	cout << max_area << endl;
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