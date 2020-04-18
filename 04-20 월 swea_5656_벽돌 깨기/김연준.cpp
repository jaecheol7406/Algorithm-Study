/*
SWEA 5656.[���� SW �����׽�Ʈ] ���� ����
���� ���� : �ùķ��̼�, ����Ž��
function call() : main -> Solve - > Initialize - >input->solution->DFS->play->gravity->getResult.
1. �ߺ������� ������ ���� ������ ���Ѵ�.(DFS())
2. ������ ����(play())
	(1) BFS�� ����ؼ� ������ ������ �����ϸ� �� ������ ������ �ִ� ������ queue�� �߰�.
	(2) queue�� �߰��� ��, visit���� �湮 üũ�� �Ͽ� �ߺ� �湮�� ����.
	(3) �ش� ������ ������ ��� �˻�������, ������ ���ŵǾ����Ƿ� 0���� �ٲ��ش�.(gravity()�� ����)
3. ������ ������ ����߸�(gravity())
4. ��� ���

*/
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
int T, N, M; //[H][W];
int board[16][16];
int t_board[16][16];
int visit[16];
bool vis[16][16];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
int result = 987654321;
void Input() {
	cin >> T >> M >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
}
void copy_board() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			t_board[i][j] = board[i][j];
		}
	}
}
void BFS(int x, int y) {
	queue<pair<int, int>> que;
	memset(vis, 0, sizeof(vis));
	que.push({ x,y });
	vis[x][y] = true;

	while (!que.empty()) {
		auto cur = que.front();
		que.pop();
		for (int i = 1; i <= t_board[cur.first][cur.second] - 1; i++) {
			for (int j = 0; j < 4; j++) {
				int nx = cur.first + dx[j] * i;
				int ny = cur.second + dy[j] * i;
				if (nx < 0 || nx >= N || ny < 0 || ny >= M)
					continue;
				if (vis[nx][ny])
					continue;
				if (t_board[nx][ny] == 0)
					continue;
				vis[nx][ny] = true;
				que.push({ nx,ny });
			}
		}
		t_board[cur.first][cur.second] = 0;

	}
}
void gravity() {
	for (int i = 0; i < M; i++) {
		for (int j = N - 2; j >= 0; j--) {
			for (int k = j + 1; k < N; k++) {
				if (t_board[k][i] == 0) {
					t_board[k][i] = t_board[k - 1][i];
					t_board[k - 1][i] = 0;
				}
			}
		}
	}
}
void print() {
	cout << "------------------------" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << t_board[i][j] << " ";
		}
		cout << endl;
	}
	cout << "------------------------" << endl;
}
void play(int idx) {
	//�����Ʊ�
	bool flag = false;
	for (int i = 0; i < N; i++) {
		if (t_board[i][idx] != 0) {
			BFS(i, idx);
			flag = true;
			break;
		}
	}
	//�߷�
	if (flag) {
		gravity();
	}
}
void getResult() {
	int answer = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (t_board[i][j] != 0)
				answer++;
		}
	}
	result = min(answer, result);
}
void DFS(int cnt) {
	if (cnt == T) {
		copy_board();
		for (int i = 0; i < T; i++) {
			play(visit[i]);
		}
		//print();
		getResult();
		return;
	}
	for (int i = 0; i < M; i++) {
		visit[cnt] = i;
		DFS(cnt + 1);
	}
}
void Solution() {
	DFS(0);
}
void Initialize() {
	result = 987654321;
	memset(visit, 0, sizeof(visit));
}
void Solve() {
	int t_case;
	cin >> t_case;
	for (int i = 1; i <= t_case; i++) {
		Initialize();
		Input();
		Solution();
		cout << "#" << i << " "<<result<< endl;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}