/*
BOJ 2234��: ����
���� ���� : BFS
������� �� : �ϳ��� ���� �����Ͽ� ���� �� �ִ� ���� ���� ���� ũ�⸦ ���� �� �� �濡 ���ؼ� ������ ���� ���ϰ� ,
              ������ ��鿡 ���ؼ� �ִ��� ã������ �Ͽ����� �ʹ� ���������� Ǯ�� ����.
			  ��α� ���� ��Ʈ����ŷ�� ���� ��Ʈ�� ��� �ٽ� ǰ.

���� Ǯ��
1. BFS�� Ž���Ͽ� ���� ������ ���� ���� ���� ���̸� ����
   ->BFS�� Ž�� ��, ��Ʈ����ŷ�� ����Ͽ� �����¿쿡 ���Ͽ� ���� �ִ��� ���� �� �Ǵ� �Ѵ�.

2. �� ĭ�� ���ؼ� ���� �� ���� �����Ѵ��� BFS Ž���� ���� ���� ���̸� ���Ѵ�.
   -> ���� �� ���� ������ �� ��Ʈ����ŷ�� ����Ѵ�. ex) 1011(2)�̸�  1011 & (0001 or 0010 or 0100 or 1000) �� �����Ͽ� �����¿쿡 ���� �ִ��� Ȯ���Ѵ�.
   -> ���� �����Ѵٸ� board[i][j] -= (1or 2 or 4 or 8)�� �Ͽ� ���� �㹰�� BFS Ž�� �� �ٽ� board[i][j] += (1 or 2 or 3 or 4)�� �Ͽ� ���� ����.
*/
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
int N, M;
int board[51][51];
bool visit[51][51];
int dx[4] = { 0,-1,0,1 }; //�� �� �� �� ��
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
void check_dir(int x, int y) { //���� ���� ���� ����
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
			//if (dir[i] == 1) //���� ���� �� ����
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