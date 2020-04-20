/*
function call: main -> Input -> (DFS -> Throw -> Cross -> Pull Count) -> main

DFS�� ����߸� ���� �̰�(��������, �ߺ�����) ���ʷ� �ش� ���� ���� ����߸���

������
1. Pull �Լ��� ���� ��ġ
=> ���� ������ Ÿ�̹��� ��� ����. �� ����� ������ �� �Ʒ��� �������� ���� ��� �Ͷ߸� ���Ŀ� �ؾ� �Ѵ�.
2. boundaryTmp�� ����� map[r][c]=0 �� ���� ��ġ
=> 3¥�� ���� ������ ���������� ���� �ָ� �� �Ͷ߸� ������ �� ó�� �����⸦ ������ �¸� 0���� �ٲ�� �Ѵ�.
*/
#include <iostream>
using namespace std;

int N, W, H; // N�� ����, W�� �÷���, H�� �ο��

int map[20][20];
int backup[20][20];

int minAnswer = 400;
int picked[5]; // DFS�� ���� ����߸� �÷� ��ȣ

void Input() {

	minAnswer = 400;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			map[i][j] = 0;
			backup[i][j] = 0;
		}
	}

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
	int tmpR, tmpC;

	for (int i = 0; i < 4; i++) {
		tmpR = r;
		tmpC = c;
		for (int t = 0; t < boundary - 1; t++) {
			tmpR += dir[i][0];
			tmpC += dir[i][1];

			if (tmpR < 0 || tmpC < 0 || H <= tmpR || W <= tmpC) continue;

			int boundaryTmp = map[tmpR][tmpC];
			map[tmpR][tmpC] = 0;

			if (boundaryTmp > 1) {
				Cross(tmpR, tmpC, boundaryTmp);
				
			}

		}
	}
}

void Pull() { // ����� �� �ִ� �ֵ� �����
	for (int j = 0; j < W; j++) {
		int startRow = -1;
		for (int i = 0; i < H; i++) {
			if (map[i][j] != 0 && startRow == -1) startRow = i;
			if (map[i][j] == 0 && startRow >= 0) { // ������ ������� �ϴ� ���
				for (int k = i; k > startRow; k--) {
					map[k][j] = map[k - 1][j];
				}
				map[startRow][j] = 0;
				startRow++;
			}
		}
	}
}

void Throw(int c) { // 0�� r������ Ž���ؼ� ���� ���� ������ ���� ����
	
	for (int i = 0; i < H; i++) {
		if (map[i][c] > 1) { // ���� ���� ���� ��
			int boundaryTmp = map[i][c];
			map[i][c] = 0;
			Cross(i, c, boundaryTmp); // map[i][c]���� �ݰ�(map[i][c])��ŭ ���ش�
			
			break;
		}
		else if (map[i][c] == 1) {
			map[i][c] = 0;
			break;
		}
	}
}

void Init() {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			map[i][j] = backup[i][j];
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


void DFS(int cnt) {
	if (cnt >= N) {
		Init();

		/*for (int i = 0; i < cnt; i++) {
			cout << picked[i] << " ";
		}
		cout << endl;*/

		for (int i = 0; i < cnt; i++) {
			Throw(picked[i]);
			Pull();
		}

		// ���� �� ����
		int tmp = Count();
		if (tmp < minAnswer) minAnswer = tmp;
		return;
	}

	for (int i = 0; i < W; i++) {
		picked[cnt] = i;
		DFS(cnt + 1);
	}
}

int main() {

	int T;
	scanf("%d", &T);

	for (int i = 1; i <= T; i++) {
		cout << "#" << i << " ";
		Input();

		// 0~(W-1)�� ���� �߿� N���� ����. �ߺ� �����ϰ� ���� �ǹ� �ִ�.
		DFS(0);

		cout << minAnswer << endl;
	}

	return 0;
}