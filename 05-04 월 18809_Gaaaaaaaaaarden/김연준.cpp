/*
BOJ 18809��: Gaaaaaaaaaarden
���� ���� : �ùķ��̼� (DFS,BFS)

1. ��������, Ȳ��� ĭ �� �ʷϻ� ������ �Ѹ� ���� �����Ѵ�(SelectGreen)
2. ���������� ��������, ���� �� �߿��� ������ ������ �Ѹ� ���� �����Ѵ�(SelectRed)
3. �ʷϻ� ���װ� ������ ������ �Ѹ� ���� �� ���������� ������ ������ ������ �۶߸�(BFS)
	-> pair<int,int> t_map�� first�� ������ ������ �ð�, second�� ������ ���� ����.
	-> BFS�� Ž�� ��, t_map�� second�� 1,2�� �̹� ���� ĭ�̰� ���� �ǿ� �� �ִ��� Ȯ��.
	-> t_map�� second�� 0�̸� ���� ������ �ʾ����Ƿ�, �ش� ĭ�� ����Ų��.
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
			cin >> board[i][j];    //0�� ȣ��, 1�� x, 2�� o
			if (board[i][j] == 2) {
				pos_list.push_back({ i,j });
			}
		}
	}
}
void BFS() {
	queue<pair<int, int>> que;
	pair<int, int> t_map[51][51]; //first �ð�, second ��
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
		if (t_map[cur.first][cur.second].second == 3) //������
			continue;
		for (int i = 0; i < 4; i++) {
			int nx = cur.first + dx[i];
			int ny = cur.second + dy[i];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M)
				continue;
			if (board[nx][ny] == 0)
				continue;
			if (t_map[nx][ny].second == 3) //�̹� ���ǿ��
				continue;
			if (t_map[nx][ny].second==1 ||t_map[nx][ny].second==2) { //�̹� ����.
				if (t_map[nx][ny].first == time + 1&&color!=t_map[nx][ny].second) { //���ǿ�
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