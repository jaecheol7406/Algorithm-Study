/*
�򰥸��� �κ�
1. DFS Ž���Ϸ�� ���������Ű�� (�������� answer Ȱ��)
2. ��ٸ� ��ġ�� �� ��, ������ �ƴ϶� �������� �̾ƾ� ��.
   1,3 ��ȸ �� (1,3) & (3, 3) �� �̾Ƴ���, 
   3, 3 ��ȸ���� �� (3, 3) & (1,3)�� ������ �ð��ʰ�
*/
#include <iostream>
#include <vector>
using namespace std;

int N, M, H;
int map[35][15];

int limit;
int answer = -1;

void Input() {
	cin >> N >> M >> H;
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		map[a][b] = 1;
	}
}

void Print() {
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

bool Test() {
	for (int j = 1; j <= N; j++) { // j������ ���
		int pos = j; // ���� ��� �ִ���
		for (int i = 1; i <= H; i++) {
			if (pos+1 <= N && map[i][pos] == 1) {
				pos++;
			}
			else if (pos - 1 >= 1 && map[i][pos - 1] == 1) {
				pos--;
			}
		}
		if (pos != j) return false;
	}
	return true;
}

void DFS(int pre, int cnt) {
	if (answer != -1) return; // ������ 1. ���� �̹� ������, DFS�� �߰��� �����Ű�� ���

	if (cnt >= limit) {

		if (Test()) {
			answer = limit;
		}
		//cout << endl;
		//Print();
		return;
	}

	for (int i = 1; i <= H; i++) {
		for (int j = pre; j < N; j++) {
			if (map[i][j] ) continue;
			if (j - 1 >= 1 && map[i][j - 1] == 1) continue;
			if (j + 1 < N && map[i][j + 1] == 1) continue;

			map[i][j] = 1;
			//cout << cnt << "��° ����: " << "(" << i << "," << j << ") ";
			DFS(pre + 1, cnt + 1); // 2. ��ٸ� ��ġ�� �� ��, ������ �ƴ϶� �������� �̾ƾ� ��.
			if (answer != -1) break;  // ������ 1. ���� �̹� ������, DFS�� �߰��� �����Ű�� ���
			map[i][j] = 0;
		}
	}

}

int main() {

	Input();
	// Print();

	for (int i = 0; i < 4; i++) {
		limit = i;

		DFS(1, 0); // 2. ��ٸ� ��ġ�� �� ��, ������ �ƴ϶� �������� �̾ƾ� ��.
		if (answer != -1) break;  // ������ 1. ���� �̹� ������, DFS�� �߰��� �����Ű�� ���
	}

	cout << answer;

	return 0;
}