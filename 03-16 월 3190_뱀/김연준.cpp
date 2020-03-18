/*
BOJ 3190��: ��
���� ���� : �ùķ��̼�
���� Ǯ�� : 
			1. �ش� ��ǥ�� ����� �ִ��� ������ �� ���� ���� �����ϴ��� �ƴ����� bool�� ������ �迭�� ���� �Ǻ��Ѵ�.
			2. ���� �Ӹ��� push�ϰ�, ���� ������ pop�� �ؾ��ϹǷ� deque�� ����ؼ� ���� �̵���θ� �����Ѵ�.
			3. ���� �Ӹ��� �������� ���� ĭ�� ������, �ڱ� ������ Ȯ��
			4. ����� �ִ� ������ �ƴ��� Ȯ��
			5. ����� �ִٸ� ���� �̵���ο� �Ӹ� �߰�, visit �湮 true�� ����, ��� ����
			6. ����� ���ٸ� ���� �̵���ο� �Ӹ� �߰�, ���� ����, �Ӹ� ��ǥ visit, ���� ��ǥ !visit
			7. ���� ������ �ʿ��ϸ� ����

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
	if (C == 'L') { //���� ȸ��
		dir = (dir + 3) % 4;
	}
	else { //������ ȸ��
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
		if (nx<1 || nx>N || ny<1 || ny>N) //���� �ε���
			break;
		if (visit[nx][ny] == true) //�ڱ��ڽſ� �ε���
			break;

		if (board[nx][ny] == true) { //����ĭ�� ����� �ִٸ�
			board[nx][ny] = false;
			snake.push_front(make_pair(nx, ny));
			visit[nx][ny] = true;
		}
		else { //����ĭ�� ����� ���ٸ�
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