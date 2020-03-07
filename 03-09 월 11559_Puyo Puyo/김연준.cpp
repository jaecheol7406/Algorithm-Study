/*
BOJ 11559: Puyo Puyo
���� ���� : �ùķ��̼� (BFS)
���� Ǯ�� : BFS�� ����ؼ� ������ �ѿ�ѿ䰡 �ִ��� üũ�Ѵ�.
            �ѿ�ѿ䰡 �����ٸ� �߷��ۿ�, ������ ������ �ݺ����� ���߰� ��� ���
			�߷� �ۿ� �� üũ �ϴ� �������� x��ǥ�� ��ĭ�� ���̸鼭 �ش� ���� '.'�̶�� ������.

*/

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
char board[12][6];
bool flag = true;
int result = 0;
bool visit[12][6];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

void Input() {
	for (int i = 11; i >= 0; i--) {
		for (int j = 0; j < 6; j++) {
			cin >> board[i][j];
		}
	}
}
void Print() {
	cout << "---------------" << endl;
	for (int i = 11; i >=0; i--) {
		for (int j = 0; j < 6; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << "---------------" << endl;
}
void BFS(int x, int y) {
	queue<pair<int, int>> puyo;
	queue<pair<int, int>> delete_list;
	int cnt = 1;
	puyo.push(make_pair(x, y));
	delete_list.push(make_pair(x, y));
	visit[x][y] = true;
	while (!puyo.empty()) {
		auto cur = puyo.front();
		puyo.pop();
		//cout << cur.first << " " << cur.second << endl;
		for (int i = 0; i < 4; i++) {
			int nx = cur.first + dx[i];
			int ny = cur.second + dy[i];
			if (nx < 0 || nx >= 12 || ny < 0 || ny >= 6)
				continue;
			if (visit[nx][ny])
				continue;
			if (board[nx][ny] == board[x][y]) {
				visit[nx][ny] = true;
				puyo.push(make_pair(nx, ny));
				delete_list.push(make_pair(nx, ny));
				cnt++;
			}
		}

	}
	if (cnt >= 4) {
		flag = true;
		while (!delete_list.empty()) {
			auto cur = delete_list.front();
			delete_list.pop();
			board[cur.first][cur.second] = '.';
		}
	}

}
void Solution() {
	//���� �߸���
	 //������
	//�ݺ�
	while (true) {
		memset(visit, 0, sizeof(visit));
		flag=false;
		for (int i = 0; i < 12; i++) { //���� �ۿ� 
			for (int j = 0; j < 6; j++) {
				if (visit[i][j] || board[i][j] == '.')
					continue;
				BFS(i, j);
			}
		}
		
	
		if (flag == true) {
			result++;
			for (int i = 1; i < 12; i++) { //�߷��� ������ �޾� ������
				for (int j = 0; j < 6; j++) {
					if (board[i][j] == '.')
						continue;
					for (int k = i - 1; k >= 0; k--) {
						if (board[k][j] == '.') {
							board[k][j] = board[k + 1][j];
							board[k + 1][j] = '.';
						}
					}
				}
			}
		}
		else
			break;
	}
	cout << result << endl;
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