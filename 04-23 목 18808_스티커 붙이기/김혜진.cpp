/*
function call: main -> (Select -> PasteAt -> Tilt) -> main

- ��ƼĿ���� ��� ��������� 0�������� ���ɼ��� ������
- �� �Ǹ� ��� ��������� 90�������� ���ɼ��� ������.. ������ 270������
- ���߿� ������ �� ���� ��ƼĿ�� �Ѿ��. �� ������ �׳� ������.

������
1. ��ƼĿ ������ ���� �ʹ� ��ư� �����ؼ� �ð��� �����ɸ�
2. 0,0���� 0, 90, 180, 270���� Ȯ���ϴ� �� �ƴ϶� 90������ ��� ���� Ȯ���ϰ� �� �Ǹ� ������ ����
3. Select���� �������� �� ���� ���� 0�� ��ǥ�� �ƴ϶� ��� ��ǥ���� �����غ��ƾ� ��
(��ƼĿ �������� �ش�Ǵµ� ���� �ʿ�� ���� ���� �ֱ� ������)
*/
#include <iostream>
using namespace std;

int N, M, K;
int map[50][50];

int sticker[15][15];
int tmpSticker[15][15];
int n, m;

bool Tilt(int r, int c, int gakdo) {
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
	}
	else if (gakdo == 180) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (sticker[n-1-i][m-1-j] == 1 && map[r + i][c + j] == 1) return false;
				if (r + i < 0 || c + j < 0 || N <= r + i || M <= c + j) return false;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (sticker[n - 1 - i][m - 1 - j] == 1) map[r + i][c + j] = 1;
			}
		}
		return true;
	}
	else if (gakdo == 270) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
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
	}

	// �� ���̸� �׳� ������
	return false;
}

bool PasteAt(int r, int c, int gakdo) {
	bool success = false;

	success = Tilt(r, c, gakdo);
	
	if (success) return true;

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
	for (int t = 0; t < 360; t += 90) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				// ������: 1�� �ƴϾ�� �����ϸ� �ȵȴ�
				if (PasteAt(i, j, t)) return true; // ���̴� �� ����
			}
		}
	}
	
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

		Select();
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