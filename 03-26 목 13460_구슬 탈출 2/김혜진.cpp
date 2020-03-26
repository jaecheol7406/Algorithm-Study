/*
1. ����̴� �ڵ� �ϼ�
  function call: Input() -> Tilt(����)
2. ����̴� ���� Ž�� �����
*/
#include <iostream>
using namespace std;

int N, M;
char map[12][12];
int holeR, holeC;

void Input() {
	scanf("%d %d\n", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%1s", &map[i][j]);
			if (map[i][j] == 'O') {
				holeR = i;
				holeC = j;
			}
		}
	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%c", map[i][j]);
		}
		cout << endl;
	}
}

void Fallen(char color) {
	cout << color << "�� ������ �������ϴ�" << endl;
}

void Tilt(int dir) { // 0: ���� 1: ������ 2:���� 3:�Ʒ���

	if (dir == 0) {
		for (int i = 1; i < N - 1; i++) { // ��� �࿡ ���ؼ�
			int next = 1;
			for (int j = 1; j < M - 1; j++) { // �� ���ʺ���
				if (map[i][j] == 'R' || map[i][j] == 'B') { 
					next = j - 1;
					while (map[i][next] == '.' || map[i][next] == 'O') {
						next--;
					}
					next++;

					if (holeR == i && next <= holeC && holeC <= j) {
						Fallen(map[i][j]);
					}

					if (next != j) { // �� �ڸ��� ���� �ִ� �� �ƴ϶� �̵��� �Ѵٸ�
						map[i][next] = map[i][j];
						map[i][j] = '.';
					}
				}
			}

		}
	}
	else if (dir == 1) {
		for (int i = 1; i < N - 1; i++) {
			int next = 1;
			for (int j = M - 1; j > 0; j--) { // �� �����ʺ���
				if (map[i][j] == 'R' || map[i][j] == 'B') {
					next = j+1;
					while (map[i][next] == '.' || map[i][next] == 'O') {
						next++;
					}
					next--;

					if (holeR == i && j <= holeC && holeC <= next) {
						Fallen(map[i][j]);
					}

					if (next != j) { // �� �ڸ��� ���� �ִ� �� �ƴ϶� �̵��� �Ѵٸ�
						map[i][next] = map[i][j];
						map[i][j] = '.';
					}
				}

			}
		}
	}

	else if (dir == 2) { // ����
		for (int j = 1; j < M - 1; j++) { // ��� ���� ���ؼ�
			int next = 1;
			for (int i = 1; i < N - 1; i++) { // �� �� ����� �˻�
				if (map[i][j] == 'R' || map[i][j] == 'B') {
					
					next = i - 1;
					while (map[next][j] == '.' || map[next][j] == 'O') { // �� �� �ִ� �ڸ��� ã�Ƴ���
						next--;
					}
					next++;
					if (holeC == j && next <= holeR && holeR <= i) {
						Fallen(map[i][j]);
					}

					if (next != i) { // �� �ڸ��� ���� �ִ� �� �ƴ϶� �̵��� �Ѵٸ�
						map[next][j] = map[i][j];
						map[i][j] = '.';
					}
					
				}
			}
		}
	}
	else if (dir = 3) { // �Ʒ���
		for (int j = 1; j < M - 1; j++) { // ��� ���� ���ؼ�
			int next = 1;
			for (int i = N-1; i > 0; i--) { // �� �Ʒ� ����� �˻�
				if (map[i][j] == 'R' || map[i][j] == 'B') { // ������ ������
					next = i + 1;
					while (map[next][j] == '.' || map[next][j] == 'O') { // �� �� �ִ� �ڸ��� ã�Ƴ���
						next++;
					}
					next--;
					if (holeC == j && i <= holeR && holeR <= next) {
						Fallen(map[i][j]);
					}

					if (next != i) {
						map[next][j] = map[i][j];
						map[i][j] = '.';
					}
					

				}
			}
		}
	}
}

int main() {

	Input();
	Print();
	cout << endl;

	Tilt(3);
	Print();

	// 10�� �� ����.
	// 1�� �� �� ������ ������ ����� �� �Ķ� ������ ������ -1�� ����Ѵ�. ���� ������ ������ Ƚ���� ����Ѵ�.
	// 10�� �ʰ��ϸ� -1�� ����Ѵ�.

	

	return 0;
}