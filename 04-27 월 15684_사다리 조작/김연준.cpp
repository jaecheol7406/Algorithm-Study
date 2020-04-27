/*
BOJ 15684��: ��ٸ� ����
���� ���� : �ùķ��̼�(DFS)

1. ���μ��� 0�� �߰��ϴ� ������ 3�� �߰��ϴ� ��츦 ���������� Ž��.
	-> i�� ���μ��� i���� ���´ٸ� ����
2. 1�� ��ٸ�(���μ�)�� 2�� ��ٸ�(���μ�)�� 3�� ���μ��� ���� ����Ǿ� �ִٸ� board[3][1]=true.
3. ���ο� ��ٸ��� �߰��� �� ���� ��ٸ�, �� ��ٸ�, �� ��ٸ��� ����Ǿ� ���� �ʴٸ� ���������.


*** ������ �� ***

ó������ ���μ��� 0�� �߰��ϴ� ������ 3�� �߰��ϴ� ��츦 ��� Ž���ߴ���,

�ð��� 2000ms�� �ʹ� �����ɷ���(������ ���),

0�� �߰����� �� i�� ���μ��� i���� ���´ٸ� 1�� ~3�� �߰��ϴ� ���� Ž������ �ʴ� ��������

�����Ͽ�����, �ð��� ���� ���ҵ�.

*/
#include <iostream>
#include <algorithm>
using namespace std;
bool board[31][11];
int N, M, H;//���μ�, ���μ�, ���μ����� ���μ��� ���� �� �ִ� ��ġ�� ����
int result = -1;
int limit;
void Input() {
	cin >> N >> M >> H;
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b; //H,N  , (b,b+1) ����.
		board[a][b] = true;
	}
}
bool check() {
	for (int i = 1; i <= N; i++) {
		int idx = i;
		for (int j = 1; j <= H; j++) {
			if (board[j][idx]) {
				idx++;
			}
			else if (board[j][idx - 1]) {
				idx--;
			}
		}
		if (idx != i)
			return false;
	}
	return true;
}
void DFS(int idx, int cnt) {
	if (result!=-1) {
		return;
	}
	if (cnt == limit) {
		if (check()) {
			result = cnt;
		}
		return;
	}
	for (int i = idx; i < N; i++) {
		for (int j = 1; j <= H; j++) {
			if (board[j][i] || board[j][i - 1] || board[j][i + 1])
				continue;
			board[j][i] = true;
			DFS(i, cnt + 1);
			board[j][i] = false;
		}
	}
}
void Solution() {
	for (int i = 0; i < 4; i++) {
		limit = i;
		DFS(1, 0);
		if (result != -1)
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
	Solve();
	return 0;
}