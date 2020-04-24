/*
SWEA 2112�� : ��ȣ �ʸ�
�������� : �ùķ��̼�(DFS)

1. DFS �������� ���� �����ϰ�, ��ǰ A�� ������ B�� ������ ����.(DFS�� �ݺ���)
	(1) ���� ��ǰ�� ���������� �ش� ���� ��ǰ�� ������(Change(x,med,true))
	(2) ��Ͱ� return�Ǿ�����, �ش� ���� ���� ��Ŵ(Change(x,med,false))

2. ���ɰ˻�(Check())


<!-- ������ �� -->
D�� ������ �ִ� 13�̶�, �ð��ʰ� �߻�.

DFS���� ���� �����ϴ� ���� ������ Ƚ��(cnt)�� result���� Ŀ���� �ش� ��ʹ� �������.
(�ּҰ��� ���ϴ� �����̹Ƿ� �̹� ������ �� Ƚ������ �� ���� ���� ���� �����ϴ� ��ʹ� �� �ʿ� ����.)
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
int N, M, K, result;
int board[14][21];
int t_board[14][21];
bool visit[14];
vector<int> v;
void Input() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
			t_board[i][j] = board[i][j];
		}
	}

}
void Initialize() {
	memset(board, 0, sizeof(board));
	memset(t_board, 0, sizeof(t_board));
	result = 987654321;
}
bool Check() {
	for (int i = 0; i < M; i++) { //A�� 0, B�� 1
		int cnt = 1;
		bool flag = false;
		for (int j = 0; j < N - 1; j++) {
			if (board[j][i] == board[j + 1][i]) {
				cnt++;
			}
			else
				cnt = 1;
			if (cnt >= K) {
				flag = true;
				break;
			}
		}
		if (!flag) { //��� ����
			return false;
		}
	}
	return true;
}
void Change(int x, int med, bool f) {
	if (f) { //����
		for (int i = 0; i < M; i++) {
			board[x][i] = med;
		}
	}
	else {//����
		for (int i = 0; i < M; i++) {
			board[x][i] = t_board[x][i];
		}
	}
}
void DFS(int idx, int cnt) {
	if (cnt >= result)
		return;
	if (Check()) {
		result = min(result, cnt);
		return;
	}
	for (int i = idx; i < N; i++) { //�� ����
		if (visit[i])
			continue;
		visit[i] = true;
		for (int j = 0; j < 2; j++) { //�� ����
			//��ǰ����
			Change(i, j, true);
			DFS(i, cnt + 1);
			Change(i, j, false);
			//���󺹱�
		}
		visit[i] = false;
	}
}
void Solution() {
	DFS(0, 0);
}
void Solve() {
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Initialize();
		Input();
		Solution();
		cout << "#" << i << " " << result << endl;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}