/*
Ʋ���ڵ�
��ٸ� 1���� �ǳ� Ȯ���غ���, �ȵǸ� 2��, �� �ȵǸ� 3���� �ؾߵǴµ�
�Ʒ� �ڵ�� (1, 1)�� ��ٸ��� ��ġ�ϰ� �̰� ���� �ƴϸ� �� ���¿��� �ϳ��� �߰��� 2���� ��ġ
�� ������ ���� üũ�ؼ� �°ԵǸ� �����ϴµ�, ���� �� �Ʒ��� ��ٸ� 1��¥���� ������ִ°��� ���������ִµ� �װ� Ž���� ��������ä�� 2�� �����ϱ� ������ ����
*/
#include <iostream>
#include <vector>
using namespace std;

int N, M, H;
int map[35][15];

void Input() {
	scanf("%d %d %d", &N, &M, &H);
	int a, b;
	for (int i = 0; i < M; i++) {
		scanf("%d %d\n", &a, &b);
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

int main() {

	Input();
	// Print();

	if (Test()) {
		cout << 0;
		return 0;
	}

	for (int j1 = 1; j1 < N; j1++) { // �� ��° ���� ���� ���ΰ� (j ~ j+1)
		for (int i1 = 1; i1 <= H; i1++) { // �� ���� �࿡ ���� ���ΰ�
			if (map[i1][j1] == 1) continue;

			map[i1][j1] = 1;
			// cout << "test: (" << i1 << "," << j1 << ")" << endl;
			// Print();

			if (Test()) {
				cout << 1;
				return 0;
			}

			// 2��°�� ��󺻴�
			for (int j2 = 1; j2 < N; j2++) {
				for (int i2 = 1; i2 <= H; i2++) {
					if (j1 == j2 && i1 == i2) continue;
					if (map[i2][j2] == 1) continue;

					map[i2][j2] = 1;
					// cout << "test: (" << i1 << "," << j1 << ") & (" << i2 << "," << j2 << ")" << endl;
					// Print();
					if (Test()) {
						cout << 2;
						return 0;
					}

					// 3��°�� ��󺻴�
					for (int j3 = 1; j3 < N; j3++) {
						for (int i3 = 1; i3 <= H; i3++) {
							if (j1 == j3 && i1 == i3) continue;
							if (j2 == j3 && i2 == i3) continue;
							if (map[i3][j3] == 1) continue;

							map[i3][j3] = 1;
							// cout << "test: (" << i1 << "," << j1 << ") & (" << i2 << "," << j2 << ") & (" << i3 << "," << j3 << ")" << endl;
							// Print();
							if (Test()) {
								cout << 3;
								return 0;
							}
							map[i3][j3] = 0;
						}
					}
					map[i2][j2] = 0;
				}
			}

			map[i1][j1] = 0;
		}
	}

	cout << -1;

	return 0;
}