#include <iostream>
#include <algorithm>
using namespace std;
int board[500][500];
bool vis[500][500];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

int N, M;
int answer = 0;
void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
}
bool IsRange(int x, int y) {
	return x >= 0 && x < N &&y >= 0 && y < M;
}
void DFS(int x, int y, int dep,int sum) { //DFS�� 4���� ĭ�� �����Ѵ�.
	if (dep == 4) {
		//cout << sum << endl;
		answer = max(answer, sum);
		
		return;
	}
	vis[x][y] = true;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (!IsRange(nx, ny) || vis[nx][ny])
			continue;
		vis[nx][ny] = true;
		DFS(nx, ny, dep + 1,sum+board[nx][ny]);
		vis[nx][ny] = false;
	}
	vis[x][y] = false;
}
void ex_DFS(int x, int y) { //DFS�� �ذ��� �� ���� ��� (�ȸ��� �̸� ȸ���� 3���� ���)
	int sum;
	if (IsRange(x + 1, y - 1) && IsRange(x + 1, y) && IsRange(x + 1, y + 1)) {
		sum = board[x][y] + board[x + 1][y - 1] + board[x + 1][y] + board[x + 1][y + 1];
		answer = max(answer, sum);
	}
	if (IsRange(x, y + 1) && IsRange(x + 1, y+1) && IsRange(x, y + 2)) {
		sum = board[x][y] + board[x][y + 1] + board[x + 1][y+1] + board[x][y + 2];
		answer = max(answer, sum);
	}
	if (IsRange(x - 1, y + 1) && IsRange(x, y + 1) && IsRange(x + 1, y + 1)) {
		sum = board[x][y] + board[x - 1][y + 1] + board[x][y + 1] + board[x + 1][y + 1];
		answer = max(answer, sum);
	}
	if (IsRange(x + 1, y) && IsRange(x+2, y) && IsRange(x + 1, y + 1)) {
		sum = board[x][y] + board[x + 1][y] + board[x + 2][y] + board[x + 1][y + 1];
		answer = max(answer, sum);
	}

}
void Solution() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			DFS(i, j, 1,board[i][j]); //DFS�� ��Ʈ�ι̳� Ž��
			ex_DFS(i, j); //DFS�� Ž�� �Ұ����� ��Ʈ�ι̳� Ž�� (�ȸ��� �̸� ȸ���� 3���� ���)
		}
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