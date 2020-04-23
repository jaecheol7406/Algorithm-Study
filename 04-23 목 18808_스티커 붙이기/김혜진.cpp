/*
������ pass, ����� Ʋ�Ƚ��ϴ�

1. ��ƼĿ���� ��� ��������� ���ɼ��� ������
2. 0������ ���� �� �ִ��� ����, �� �Ǹ� 90�� ������ ������ 270������ Ȯ���Ѵ�.
  (�迭�� ������ Ȯ���ϴ� �κ��� �ʹ� ��ư� ¥�� �ð��� ���� �ɸ�)
*/
#include <iostream>
using namespace std;

int N, M, K;
int map[50][50];

int sticker[15][15];
int tmpSticker[15][15];
int n, m;

bool Tilt(int r, int c, int gakdo) {
	// cout << "Tilt(" << r << "," << c << "," << gakdo << ")" << endl;
	// cout << "����: " << gakdo << endl;
	bool success = true;

	if (gakdo == 0) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (sticker[i][j] == 1 && map[r + i][c + j] == 1) return false;
				if (r + i < 0 || c + j < 0 || N <= r + i || M <= c + j) return false;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if(sticker[i][j] == 1)
					map[r + i][c + j] = 1;
			}
		}
		return true;
	}

	else if (gakdo == 90) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				// tmpSticker[i][j] = sticker[n - 1 - j][i];
				if (sticker[n-1-j][i] == 1 && map[r + i][c + j] == 1) return false;
				if (r + i < 0 || c + j < 0 || N <= r + i || M <= c + j) return false;
			}
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (sticker[n - 1 - j][i] == 1) map[r + i][c + j] = 1;
			}
		}
		return true;

		/*for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout << tmpSticker[i][j] << " ";
			}
			cout << endl;
		}*/
	}
	else if (gakdo == 180) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				// tmpSticker[i][j] = sticker[(n - 1) - i][j];
				/*cout << "sticker[" << n - 1 - i << "][" << j << "=" << sticker[n - 1 - i][j] << endl;
				cout << "map[" << r + i << "][" << c + j << "]=" << map[r + i][c + j] << endl;*/
				if (sticker[n-1-i][m-1-j] == 1 && map[r + i][c + j] == 1) return false;
				if (r + i < 0 || c + j < 0 || N <= r + i || M <= c + j) return false;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (sticker[n - 1 - i][m - 1 - j] == 1) map[r + i][c + j] = 1;
			}
		}

		/*for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << tmpSticker[i][j] << " ";
			}
			cout << endl;
		}*/
	}
	else if (gakdo == 270) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				// tmpSticker[i][j] = sticker[j][m-1-i];
				if (sticker[j][m-1-i] == 1 && map[r + i][c + j] == 1) return false;
				if (r + i < 0 || c + j < 0 || N <= r + i || M <= c + j) return false;
			}
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (sticker[j][m - 1 - i] == 1) map[r + i][c + j] = 1;
			}
		}
		return true;
		/*for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout << tmpSticker[i][j] << " ";
			}
			cout << endl;
		}*/
	}

	// �� ���̸� �׳� ������
	return false;
}

bool PasteAt(int r, int c) {
	bool success = false;

	for (int i = 0; i < 360; i += 90) {
		success = Tilt(r, c, i);
		// cout << i << "�� ���: " << success << endl;
		if (success) return true;
	}
	return false;
}



void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}

bool Select() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			// cout << "������: " << i << "," << j << endl;
			// ������: 1�� �ƴϾ�� �����ϸ� �ȵȴ�
			if (PasteAt(i, j)) return true; // ���̴� �� ����
		}
	}
	// cout << "�� �ٿ��� �׳� ����" << endl;
	return false; // �� �ٿ��� �׳� ����
}

int main() {

	scanf("%d %d %d\n", &N, &M, &K);

	for (int input = 0; input < K; input++) {
		// �̹��� ���� ��ƼĿ ����
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d ", &sticker[i][j]);
			}
		}

		/*cout << "=======" << endl;
		cout << "�̹� ��ƼĿ" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << sticker[i][j] << " ";
			}
			cout << endl;
		}
		cout << "=========" << endl;*/

		Select();

		// Print();
	}

	// Print();
	int answer = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 1) answer++;
		}
	}

	cout << answer;
	return 0;
}