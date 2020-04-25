#include <iostream>
using namespace std;

int N;
int c, r, d, g; // ���ۿ�, ������, ���۹���, ����
int map[120][120];
int visited[120][120];

int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
int dragonDir[4][2] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };

int oR;
int oC;

int answer = 0;

void Print() {
	for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 100; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

void Init() {
	for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 100; j++) {
			visited[i][j] = 0;
		}
	}
}

void NextGen(int n) { // �� ���� �巡��Ŀ�갡 ���� �� & i�� �����ϵ���
	Init();
	// cout << "�̹� ���� �巡��Ŀ�� ������: " << oR << "," << oC << endl;

	int bR, bC; // ��¤��� �ִ� ��
	int tmpR, tmpC; // ��¤��� �� tmp

	bool exist = false;

	visited[oR][oC] = 1;

	// ��¤� ���� ��ġ ����
	bR = oR;
	bC = oC;

	while (1) {
		exist = false;

		for (int i = 0; i < 4; i++) {
			tmpR = bR + dir[i][0];
			tmpC = bC + dir[i][1];
			if (visited[tmpR][tmpC] == 1) continue;

			// cout << tmpR << "," << tmpC << "�� ������ �׸� ���ΰ�? (" << i << ")" << endl;

			if (map[tmpR][tmpC] == n) { // ������ �׸� ���� ã�Ƴ�
				// cout << "yes" << endl;
				exist = true;
				// ��¤��� �� ����
				bR = tmpR;
				bC = tmpC;
				visited[bR][bC] = 1;

				oR += dragonDir[i][0];
				oC += dragonDir[i][1];

				map[oR][oC] = n;
				// cout << oR << "," << oC << "�� ���� ��ĥ" << endl;
				visited[oR][oC] = 1;
				break; // ���� Ž�� ��
			}

		}
		// ������ �׸� �巡��Ŀ�갡 ����
		if (!exist) {
			return;
		}
	}
}

int squareDir[4][2] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
void GetSquare(int r, int c) {
	cout << "getSquare(" << r << "," << c << ")" << endl;
	int tmpR, tmpC;
	for (int d = 0; d < 4; d++) {
		tmpR = r + squareDir[d][0];
		tmpC = c + squareDir[d][1];

		if (tmpR < 0 || 100 < tmpR || tmpC < 0 || 100 < tmpC) return;
		if (map[tmpR][tmpC] == 0) return;
	}
	cout << r << ", " << c << "���� answer++" << endl;
	answer++;
}

int main() {

	scanf("%d\n", &N);
	for (int i = 1; i <= N; i++) {
		cout << i << "�� �巡��Ŀ��" << endl;
		scanf("%d %d %d %d\n", &c, &r, &d, &g);
		r++;
		c++;

		// 0���� �׸���
		oR = r + dir[d][0];
		oC = c + dir[d][1];

		map[r][c] = i; // i��° �巡�� Ŀ��� i�� ���´�
		map[oR][oC] = i;

		for (int j = 0; j < g; j++) {
			NextGen(i);
		}

		
	}
	Print();
	// 4�� ���Ұ� ���� ���簢��
	int tmpI, tmpJ;

	
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if(map[i][j] != 0)
				GetSquare(i, j);
		}
	}

	cout << answer;

	return 0;
}