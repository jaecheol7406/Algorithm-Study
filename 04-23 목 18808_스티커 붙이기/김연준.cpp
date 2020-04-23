/*
BOJ 18808�� : ��ƼĿ ���̱�

1. �� ��ƼĿ���� ���� �� �ִ� ��� ����� ���� Ž���Ѵ�. (solution())
2. ��ƼĿ ���� 4���� ȸ���� �����ϰ�, (0,0)~(N,M)���� Ȯ�� (attatch())
	(1) ���������� Ȯ���ϴٰ� ���� �� ������ ���̰� ���� ��ƼĿ�� �Ѿ
	(2) �� ���̸� 90�� ȸ�� (rotate())

*/
#include <iostream>
#include <vector>
using namespace std;
int N, M, K;
int board[41][41];
int sticker[101][11][11];
vector<pair<int, int>> sticker_size;
void Input() {
	int R, C;
	cin >> N >> M >> K;
	for (int i = 0; i < K; i++) {
		cin >> R >> C;
		sticker_size.push_back({ R,C });
		for (int j = 0; j < R; j++) {
			for (int k = 0; k < C; k++) {
				cin >> sticker[i][j][k];
			}
		}
	}
}void print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}
bool attach(int idx, int x, int y) {
	int r = sticker_size[idx].first;
	int c = sticker_size[idx].second;
	if (x + r > N || y + c > M)
		return false;
	for (int i = x; i < x + r; i++) { //���ϼ��ֳ�?
		for (int j = y; j < y + c; j++) {
			if (sticker[idx][i - x][j - y] == 1 && board[i][j] == 1) {
				return false;
			}
		}
	}
	for (int i = x; i < x + r; i++) { //���̱�
		for (int j = y; j < y + c; j++) {
			if (sticker[idx][i - x][j - y] == 1)
				board[i][j] = 1;
		}
	}
	return true;
}
void rotate(int idx) {
	int tmp[10][10];
	int r = sticker_size[idx].first;
	int c = sticker_size[idx].second;
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < r; j++) {
			tmp[i][j] = sticker[idx][r-j-1][i];
			sticker[idx][r - j - 1][i] = 0;
		}
	}
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < r; j++) {
			sticker[idx][i][j] = tmp[i][j];
		}
	}
	sticker_size[idx].first = c;
	sticker_size[idx].second = r;
}

void Solution() {
	for (int i = 0; i < K; i++) { //��ƼĿ ��
		bool flag = false;
		for (int j = 0; j < 4; j++) { //�� ��ƼĿ�� 4���� ȸ��
			for (int k = 0; k < N; k++) { 
				for (int l = 0; l < M; l++) { //0,0������ ��ǥ
					if (attach(i, k, l)) {
						flag = true;
						break;
					}
				}
				if (flag)
					break;
			}
			if (flag)
				break;
			rotate(i);
		}
	}
}
void getAnswer() {
	int answer = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == 1)
				answer++;
		}
	}
	cout << answer << endl;
}
void Solve() {
	Input();
	Solution();
	getAnswer();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}

