/*
function call: main -> Input -> (DFS -> Init -> Look -> Count ) -> main

1. DFS�� �� ī�޶� ������ ������ �̴´�.
�� ī�޶� ��ȣ���� ���� �� �ִ� ������ �ٸ���. (DFS�Լ� �ȿ��� ����)
2. ī�޶� ��ȣ�� ī�޶� ���� ������ ������ ���� ������ ������ ǥ���Ѵ�.

*/
#include <iostream>
#include <vector>
using namespace std;

struct Pos {
	int r;
	int c;
	int n;
};

int N, M;
int map[10][10];
int backup[10][10];
vector<Pos> cctvList;

// ���� 1 ~ 5�� ī�޶� ������ �� �ִ� ������ �迭�� ����
int dir1[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} }; // �� 4�� ����
int dir2[2][2][2] = { { {1, 0}, {-1, 0} }, { {0, 1}, {0, -1} } }; // �� 2�� ����, ���� �ϳ��� 2���� ����
int dir3[4][2][2] = { {{-1, 0}, {0, 1}}, {{0, 1}, {1, 0}}, {{1, 0}, {0, -1}}, {{0, -1}, {-1, 0}} }; // �� 4�� ����, ���� �ϳ��� 2���� ����
int dir4[4][3][2] = { {{-1, 0}, {0, 1}, {0, -1}}, {{1, 0}, {0, 1}, {0, -1}}, {{1, 0}, {-1, 0}, {0, -1}}, {{1, 0}, {-1, 0}, {0, 1}} }; // �� 4�� ����, ���� �ϳ��� 3���� ����
int dir5[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} }; // �� 1�� ����, ���� �ϳ��� 4���� ����

int minAnswer = 100;

void Input() {
	scanf("%d %d\n", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d ", &map[i][j]);
			backup[i][j] = map[i][j];

			if (map[i][j] > 0 && map[i][j] < 6) {
				cctvList.push_back(Pos{ i, j, map[i][j] });
			}
		}
	}
}

void Look(int idx, int dir) {
	int tmpR, tmpC;

	if (cctvList[idx].n == 1) { // 1�� ī�޶�
		tmpR = cctvList[idx].r;
		tmpC = cctvList[idx].c;

		while (1) {
			tmpR += dir1[dir][0];
			tmpC += dir1[dir][1];

			if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) break;
			if (map[tmpR][tmpC] == 6) break;

			map[tmpR][tmpC] = -1; // ���ð����� ������ -1�� ǥ��
		}
	}
	else if (cctvList[idx].n == 2) {
		for (int i = 0; i < 2; i++) {
			tmpR = cctvList[idx].r;
			tmpC = cctvList[idx].c;

			while (1) {
				tmpR += dir2[dir][i][0];
				tmpC += dir2[dir][i][1];

				if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) break;
				if (map[tmpR][tmpC] == 6) break;

				map[tmpR][tmpC] = -1; // ���ð����� ������ -1�� ǥ��
			}
		}
	}
	else if (cctvList[idx].n == 3) {
		for (int i = 0; i < 2; i++) {
			tmpR = cctvList[idx].r;
			tmpC = cctvList[idx].c;

			while (1) {
				tmpR += dir3[dir][i][0];
				tmpC += dir3[dir][i][1];

				if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) break;
				if (map[tmpR][tmpC] == 6) break;

				map[tmpR][tmpC] = -1; // ���ð����� ������ -1�� ǥ��
			}
		}
	}
	else if (cctvList[idx].n == 4) {
		for (int i = 0; i < 3; i++) {
			tmpR = cctvList[idx].r;
			tmpC = cctvList[idx].c;

			while (1) {
				tmpR += dir4[dir][i][0];
				tmpC += dir4[dir][i][1];

				if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) break;
				if (map[tmpR][tmpC] == 6) break;

				map[tmpR][tmpC] = -1; // ���ð����� ������ -1�� ǥ��
			}
		}
	}
	else if (cctvList[idx].n == 5) {
		for (int i = 0; i < 4; i++) {
			tmpR = cctvList[idx].r;
			tmpC = cctvList[idx].c;

			while (1) {
				tmpR += dir5[i][0];
				tmpC += dir5[i][1];

				if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) break;
				if (map[tmpR][tmpC] == 6) break;

				map[tmpR][tmpC] = -1; // ���ð����� ������ -1�� ǥ��
			}
		}
	}
}

void Init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			map[i][j] = backup[i][j];
		}
	}
}

void Count() {
	int minTmp = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 0) {
				minTmp++;
			}
		}
	}
	if (minTmp < minAnswer) minAnswer = minTmp;
}

vector<int> picked;
void DFS(int cnt) {
	if (cnt >= cctvList.size()) {
		/*for (int i = 0; i < picked.size(); i++) { // �� ���� ����
			cout << picked[i] << " ";
		}
		cout << endl;*/
		Init();

		for (int i = 0; i < picked.size(); i++) {
			Look(i, picked[i]); // i�� cctv�� picked[i] ������ ���ٴ� ���¿��� ���õǴ� ������ ǥ���Ѵ�.
		}

		Count();

		return;
	}

	if (cctvList[cnt].n == 2) { // 0 ~ 1 �߿��� �ϳ� ����
		for (int i = 0; i < 2; i++) {
			picked.push_back(i);
			DFS(cnt + 1);
			picked.pop_back();
		}
	}
	else if (cctvList[cnt].n == 5) { // ������ 0�� ��´�
		picked.push_back(0);
		DFS(cnt + 1);
		picked.pop_back();
	}
	else { // 0 ~ 3 �߿��� �ϳ� ����
		for (int i = 0; i < 4; i++) {
			picked.push_back(i);
			DFS(cnt + 1);
			picked.pop_back();
		}
	}
}

int main() {

	Input();

	DFS(0); // CCTV ���� ���ϱ�

	cout << minAnswer;

	return 0;
}