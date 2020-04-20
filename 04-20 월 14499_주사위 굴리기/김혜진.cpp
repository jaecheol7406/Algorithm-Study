/*
function call: main -> Input -> main

������
- �������� ���Ʒ� �� 2���� �ٲ�� ���� �ƴ϶�, �� 4���� ���� �ٲ�� �ȴ�
(�������� ����� ����غ���)

*/
#include <iostream>
using namespace std;

int N, M, x, y, K;
int map[30][30];
int cmd[1010];

int cube[7]; // ��������� 1:���� 2:�޸� 3:������ 4:���� 5:�ո� 6:�ٴڸ�
int dir[5][2] = { {0, 0},  {0, 1}, {0, -1}, {-1, 0}, {1, 0} }; // �ֻ����� ������ ��ġ ���

void Input() {
	scanf("%d %d %d %d %d\n", &N, &M, &x, &y, &K);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d ", &map[i][j]);
		}
	}

	for (int i = 0; i < K; i++) {
		scanf("%d ", &cmd[i]);
	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {

	Input();

	for (int k = 0; k < K; k++) {
		int tmpX = x + dir[cmd[k]][0];
		int tmpY = y + dir[cmd[k]][1];

		if (tmpX < 0 || tmpY < 0 || N <= tmpX || M <= tmpY) continue;

		x = tmpX;
		y = tmpY;
		int top = cube[1];

		if (cmd[k] == 1) { // ���� (��, �޸��� 2,5 ���� �ٲ��)
			cube[1] = cube[4];
			cube[4] = cube[6];
			cube[6] = cube[3];
			cube[3] = top;
		}
		else if (cmd[k] == 2) { // ���� (��, �޸��� 2,5 ���� �ٲ��)
			cube[1] = cube[3];
			cube[3] = cube[6];
			cube[6] = cube[4];
			cube[4] = top;
		}
		else if (cmd[k] == 3) { // ���� (��, �������� 3, 4���� �ٲ��)
			cube[1] = cube[5];
			cube[5] = cube[6];
			cube[6] = cube[2];
			cube[2] = top;
		}
		else if (cmd[k] == 4) { // ���� (��, �������� 3, 4���� �ٲ��)
			cube[1] = cube[2];
			cube[2] = cube[6];
			cube[6] = cube[5];
			cube[5] = top;
		}

		cout << cube[1] << endl;

		// �Ʒ���� ������ ��
		if (map[x][y] == 0) {
			map[x][y] = cube[6];
		}
		else {
			cube[6] = map[x][y];
			map[x][y] = 0;
		}
	}

	return 0;
}