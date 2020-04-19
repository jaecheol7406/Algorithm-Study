/*
�������
function call: main -> Input -> (DFS -> Throw -> Cross -> Count) -> main

DFS�� ����߸� ���� �̴´�.
*/
#include <iostream>
using namespace std;

int N, W, H; // N�� ����, W�� �÷���, H�� �ο��
int map[20][20];
int backup[20][20];
int visited[20][20];

void Input() {
	scanf("%d %d %d\n", &N, &W, &H);
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			scanf("%d ", &map[i][j]);
			backup[i][j] = map[i][j];
		}
	}
}

void Print() {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			printf("%d ", map[i][j]);
		}
		cout << endl;
	}
}

int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
void Cross(int r, int c, int boundary) {
	cout << r << "," << c << " ���� " << boundary << "��ŭ ����" << endl;
	map[r][c] = 0;
	// visited[r][c] = 1;
	int tmpR, tmpC;

	for (int i = 0; i < 4; i++) {
		tmpR = r;
		tmpC = c;
		for (int t = 0; t < boundary - 1; t++) {
			tmpR += dir[i][0];
			tmpC += dir[i][1];

			if (tmpR < 0 || tmpC < 0 || H <= tmpR || W <= tmpC) continue;
			if (map[tmpR][tmpC] == 0) continue;
			
			if (map[tmpR][tmpC] == 1) {
				map[tmpR][tmpC] = 0;
			}
			else {
				Cross(tmpR, tmpC, map[tmpR][tmpC]);
				map[tmpR][tmpC] = 0;
			}

			/*Cross(tmpR, tmpC, map[tmpR][tmpC]);
			map[tmpR][tmpC] = 0;*/
			
		}
	}
	// cout << "����� ��====" << endl;
	// Print();

	// ����� �� �ִ� �ֵ� �����
	for (int j = 0; j < W; j++) {
		int startRow = -1;
		for (int i = 0; i < H; i++) {
			if (map[i][j] != 0 && startRow == -1) startRow = i;
			if (map[i][j] == 0 && startRow >= 0) { // ������ ������� �ϴ� ���
				// cout << i << " " << j << " ������� ��, startRow: " << startRow << endl;
				for (int k = i; k > startRow; k--) {
					map[k][j] = map[k - 1][j];
				}
				map[startRow][j] = 0;
				startRow++;
			}
		}
	}
	// cout << "���� ��====" << endl;
	// Print();
}

void Throw(int c) {
	// 0����� Ž���ؼ� ���� ���� ������ ���� ����
	for (int i = 0; i < H; i++) {
		if (map[i][c] != 0) { // ���� ���� ���� ��
			// cout << "i: " << i << " c: " << c  << " =" << map[i][c]<< endl;
			Cross(i, c, map[i][c]); // map[i][c]���� �ݰ�(map[i][c])��ŭ ���ش�

			return;
		}
	}
}

void Init() {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			map[i][j] = backup[i][j];
			visited[i][j] = 0;
		}
	}
}

int Count() {
	int answer = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (map[i][j] != 0) answer++;
		}
	}
	return answer;
}

int minAnswer = 400;
int picked[5];
void DFS(int cnt) {
	if (cnt >= N) {
		Init();

		for (int i = 0; i < cnt; i++) {
			cout << picked[i] << " ";
		}
		cout << endl;

		for (int i = 0; i < cnt; i++) {
			Throw(picked[i]);
			Print();
		}

		// ���� �� ����
		int tmp = Count();
		
		cout << "���� ��: " << tmp << endl;
		if (tmp < minAnswer) minAnswer = tmp;
		return;
	}

	for (int i = 0; i < W; i++) {
		picked[cnt] = i;
		DFS(cnt + 1);
	}
}

int main() {

	Input();
	// Print();
	

	// 0�� �÷����� ���� ����߷�����
	// Throw(1);

	// 0~(W-1)�� ���� �߿� N���� ����. �ߺ� �����ϰ� ���� �ǹ� �ִ�.
	DFS(0);

	cout << minAnswer;

	return 0;
}