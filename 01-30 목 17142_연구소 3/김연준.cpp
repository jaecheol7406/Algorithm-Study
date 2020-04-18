#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
struct virus {
	int x;
	int y;
	int t;
};
int N, M, tmp_empty_cnt, empty_cnt=0;
int result = 999999;
int Map[52][52];
int t_Map[52][52];

bool vis[52][52];
bool Select[10];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
vector<virus> vir_list;
vector<virus> active_vir;

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 2) { // 바이러스 위치 저장
				vir_list.push_back(virus{ i,j,0 });
			}
			if (Map[i][j] == 0) {
				empty_cnt++;
			}
		}
	}
}
void CopyMap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			t_Map[i][j] = Map[i][j];
		}
	}
}
void Print() {
	cout << "----------------------" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << t_Map[i][j] << " ";
		}
		cout << endl;
	}
	cout << "----------------------" << endl;
}
bool com(virus a, virus b) {
	return a.t > b.t;
}
void Initialize() {
	CopyMap();
	memset(vis, 0, sizeof(vis));
	active_vir.clear();
	tmp_empty_cnt = empty_cnt;
}
void BFS() { //바이러스 퍼트림
	queue<virus> que;
	for (int i = 0; i < active_vir.size(); i++) {
		que.push(virus{ active_vir[i].x,active_vir[i].y,0 });
	}
	while (!que.empty()) {
		virus cur = que.front();
		que.pop();
		vis[cur.x][cur.y] = true;

		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dx[i];
			int ny = cur.y + dy[i];
			int nt = cur.t + 1;
			if (nx < 0 || nx >= N || ny < 0 || ny >= N)
				continue;
			if (Map[nx][ny] == 1 )
				continue;
			if (!vis[nx][ny]) {
				if (Map[nx][ny] == 2) {
					if (tmp_empty_cnt == 0) {
						continue;
					}
					else
						tmp_empty_cnt++;
				}
				
				vis[nx][ny] = true;
				que.push(virus{ nx,ny,nt });
				active_vir.push_back(virus{ nx,ny,nt });
				tmp_empty_cnt--;
			}
		}
	}
	if (tmp_empty_cnt == 0) {
		sort(active_vir.begin(), active_vir.end(), com);
		if (result > active_vir[0].t)
			result = active_vir[0].t;
	}
}
void DFS(int Idx, int Cnt) { //바이러스 DFS로 선택
	if (Cnt == M) {
		Initialize();
		for (int i = 0; i < vir_list.size(); i++) {
			if (Select[i] == true) {
				active_vir.push_back(vir_list[i]);
			}
		}
		BFS();
		return;
	}

	for (int i = Idx; i < vir_list.size(); i++) {
		if (Select[i] == true)
			continue;
		Select[i] = true;
		DFS(i, Cnt + 1);
		Select[i] = false;
	}
}
void Solution() {
	DFS(0, 0);
	if (result == 999999) {
		cout << "-1" << endl;
	}
	else {
		cout << result << endl;
	}
}
void solve() {
	input();
	Solution();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();

	return 0;
}