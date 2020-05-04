/*
BOJ 18809번: Gaaaaaaaaaarden
문제 유형 : 시뮬레이션 (DFS,BFS)

1. 조합으로, 황토색 칸 중 초록색 배양액을 뿌릴 땅을 선택한다(SelectGreen)
2. 마찬가지로 조합으로, 남은 땅 중에서 빨간색 배양액을 뿌릴 땅을 선택한다(SelectRed)
3. 초록색 배양액과 빨간색 배양액을 뿌릴 땅을 다 선택했으면 인접한 땅으로 배양액을 퍼뜨림(BFS)
	-> pair<int,int> t_map의 first에 배양액이 도달한 시간, second에 배양액의 색을 저장.
	-> BFS로 탐색 시, t_map의 second가 1,2면 이미 배양된 칸이고 꽃을 피울 수 있는지 확인.
	-> t_map의 second가 0이면 아직 배양되지 않앗으므로, 해당 칸에 배양시킨다.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
struct med {
	int x;
	int y;
	//int 
};
vector<pair<int, int>> pos_list;
int board[51][51];
int N, M, G, R;
int result = 0;
bool visit[11];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
vector<int> green_idx;
vector<int> red_idx;
void Input() {
	cin >> N >> M >> G >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];    //0은 호수, 1은 x, 2는 o
			if (board[i][j] == 2) {
				pos_list.push_back({ i,j });
			}
		}
	}
}
void BFS() {
	queue<pair<int, int>> que;
	pair<int, int> t_map[51][51]; //first 시간, second 색
	int x, y;
	int answer = 0;
	for (int i = 0; i < green_idx.size(); i++) {
		x = pos_list[green_idx[i]].first;
		y = pos_list[green_idx[i]].second;
		t_map[x][y].first = 0;
		t_map[x][y].second = 1;
		que.push({ x,y });
	}
	for (int i = 0; i < red_idx.size(); i++) {
		x = pos_list[red_idx[i]].first;
		y = pos_list[red_idx[i]].second;
		t_map[x][y].first = 0;
		t_map[x][y].second = 2;
		que.push({ x,y });
	}
	while (!que.empty()) {
		auto cur = que.front();
		int x = cur.first;
		int y = cur.second;
		int time = t_map[x][y].first;
		int color = t_map[x][y].second;
		que.pop();
		if (t_map[cur.first][cur.second].second == 3) //꽃이핌
			continue;
		for (int i = 0; i < 4; i++) {
			int nx = cur.first + dx[i];
			int ny = cur.second + dy[i];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M)
				continue;
			if (board[nx][ny] == 0)
				continue;
			if (t_map[nx][ny].second == 3) //이미 꽃피운곳
				continue;
			if (t_map[nx][ny].second==1 ||t_map[nx][ny].second==2) { //이미 배양됨.
				if (t_map[nx][ny].first == time + 1&&color!=t_map[nx][ny].second) { //꽃피움
					t_map[nx][ny].second = 3;
					answer++;
				}
				continue;
			}
			t_map[nx][ny].first = time + 1;
			t_map[nx][ny].second = color;
			que.push({ nx,ny });


		}
	}
	result = max(result, answer);
}
void SelectRed(int idx,int cnt) {
	if (cnt == R) {
		BFS();

		
	}
	for (int i = idx; i < pos_list.size(); i++) {
		if (visit[i])
			continue;
		visit[i] = true;
		red_idx.push_back(i);
		SelectRed(i,cnt + 1);
		red_idx.pop_back();
		visit[i] = false;
	}
}
void SelectGreen(int idx,int cnt) {
	if (cnt == G) {
		SelectRed(0,0);
	}
	for (int i = idx; i < pos_list.size(); i++) {
		if (visit[i])
			continue;
		visit[i] = true;
		green_idx.push_back(i);
		SelectGreen(i,cnt + 1);
		green_idx.pop_back();
		visit[i] = false;
	}

}
void Solve() {
	Input();
	SelectGreen(0,0);
	cout << result << endl;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}