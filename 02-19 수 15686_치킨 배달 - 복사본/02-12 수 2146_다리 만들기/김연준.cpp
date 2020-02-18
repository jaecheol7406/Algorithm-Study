/*
백준 2146번: 다리만들기
BFS로 구역 나누고, DFS로 탐색하기?
*/
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int N;
const int INF = 987654321;
int answer = INF;
int board[100][100];
int island[100][100];
bool vis[100][100];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
struct brid {
	int x;
	int y;
	int len;
};
void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
}
bool IsRange(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}
void BFS() { //섬 구역 나누기
	int isl_cnt = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == 1 && !vis[i][j]) {
				queue<pair<int, int>> que;
				que.push(make_pair(i, j));
				vis[i][j] = true;
				island[i][j] = isl_cnt;
				while (!que.empty()) {
					auto cur = que.front();
					que.pop();
					for (int i = 0; i < 4; i++) {
						int nx = cur.first + dx[i];
						int ny = cur.second + dy[i];

						if (!IsRange(nx, ny) || board[nx][ny] == 0 || vis[nx][ny])  //범위 밖이거나 바다거나 방문한 곳
							continue;
						que.push(make_pair(nx, ny));
						vis[nx][ny] = true;
						island[nx][ny] = isl_cnt;
					}
				}
				isl_cnt++;
			}
		}
	}
}
void BFS2() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == 1) {
				memset(vis, 0, sizeof(vis));
				queue<brid> que;
				que.push(brid{ i,j,0 });
				vis[i][j] = true;
				//cout << "시작 좌표: " << i << " " << j << endl;
				while (!que.empty()) {
					brid cur = que.front();
					//cout << cur.x << " " << cur.y <<" "<<cur.len <<endl;
					que.pop();
					if ((board[cur.x][cur.y] == 1) && (island[cur.x][cur.y] != island[i][j])) {
						//cout << "도착 좌표: " << cur.x << " " << cur.y << " " << cur.len << endl;
						if (answer > cur.len - 1)
							answer = cur.len - 1;
						break;
					}
					for (int k = 0; k < 4; k++) {
						int nx = cur.x + dx[k];
						int ny = cur.y + dy[k];
						int nlen = cur.len + 1;
						if (!IsRange(nx, ny) || vis[nx][ny]|| (island[i][j] == island[nx][ny]))
							continue;	
						vis[nx][ny] = true;
						que.push(brid{ nx,ny,nlen });
					}
				}


			}
		}
	}

}
void Print() {
	cout << "------------------" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << island[i][j] << " ";
		}
		cout << endl;
	}
}
void Solution() {
	BFS();
	//Print();
	BFS2();
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