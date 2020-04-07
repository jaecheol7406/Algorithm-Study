/*
BOJ 17142: 연구소 3
문제 유형 : 시뮬레이션
*/
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
struct virus {
	int x;
	int y;
	int time;
};
int N, M;
int board[51][51];
//int t_board[51][51];
bool visit[52][52];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
int blankCnt = 0;
vector<virus> virusLoc;
vector<virus> virusAct;
bool selected[11];
int answer = 987654321;
bool cmp(virus& a, virus& b) {
	return a.time > b.time;
}
void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) { //0은 빈칸, 1은 벽, 2는 바이러스
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			if (board[i][j] == 0)
				blankCnt++;
			else if (board[i][j] == 1)
				board[i][j] = -1;

			else {
				virusLoc.push_back({ i,j,0});
			}
		}
	}
}
void BFS() {
	queue<virus> que;
	int blankCheck = 0;
	for (int i = 0; i < virusAct.size(); i++) {
		que.push(virusAct[i]);
		visit[virusAct[i].x][virusAct[i].y] = true;
	}
	while (!que.empty()) {
		virus cur = que.front();
		que.pop();

		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dx[i];
			int ny = cur.y + dy[i];
			int ntime = cur.time + 1;

			if (nx < 0 || nx >= N || ny < 0 || ny >= N)
				continue;
			if (visit[nx][ny])
				continue;
			if (board[nx][ny] == -1)
				continue;
			if (board[nx][ny] == 2 && blankCheck==blankCnt) {
				continue;
			}
			if (board[nx][ny] == 0)
				blankCheck++;
			que.push({ nx,ny,ntime });
			visit[nx][ny] = true;
			virusAct.push_back({ nx,ny,ntime });
		}
	}
	if (blankCheck == blankCnt) {
		sort(virusAct.begin(), virusAct.end(), cmp);
		answer = min(answer, virusAct[0].time);
	}
}
void Initialize() {
	virusAct.clear();
	memset(visit, 0, sizeof(visit));
}
void selectVirus(int idx, int cnt) {
	if (cnt == M) {
		Initialize();
		for (int i = 0; i < virusLoc.size(); i++) {
			if (selected[i])
				virusAct.push_back(virusLoc[i]);
		}
		BFS();
		return;
	}
	for (int i = idx; i < virusLoc.size(); i++) {
		if (selected[i])
			continue;
		selected[i] = true;
		selectVirus(i, cnt + 1);
		selected[i] = false;
	}
}
void Solve() {
	Input();
	selectVirus(0, 0);
	if (answer == 987654321)
		cout << "-1" << endl;
	else
		cout << answer << endl;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}