/*
function call: main -> Input -> (Start -> Check) -> main

Brute Force
1. �� �� ������(������ r,c) �� ����
2. ������ ���ο��� d1, d2�� ����
3. �� ������, d1, d2 ������ ������ ��輱�� 5�� �׾��ش�
4. �� �������� �������� �޸��ϸ鼭 ������ ���� ���Ѵ�.
(��輱 5�� ������ ������ + Ư�� ���� ��������) �� ���ѻ������� �ش�.
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;
int map[25][25];
int visited[25][25];
// int numbers[6];
vector<int> numbers;
int r1, r2, r3, r4, c1, c2, c3, c4;
int allSum = 0;
int minAnswer = 99999999; // �ּڰ��� max�� 4000 (20*20)*100

void Input() {
	scanf("%d\n", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &map[i][j]);
			allSum += map[i][j];
		}
	}
}

void Init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[i][j] = 0;
		}
	}

	numbers.clear();
}

void Check(int r, int c, int d1, int d2) {
	Init();

	// ��� ǥ��
	for (int i = 1; i < d1; i++) {
		visited[r + i][c - i] = 5;
	}
	for (int i = 0; i <= d2-1; i++) {
		visited[r + d1 + i][c - d1 + i] = 5;
	}
	for (int i = 0; i <= d1-1; i++) {
		visited[r + d1 + d2 - i][c - d1 + d2 + i] = 5;
	}
	for (int i = 0; i <= d2; i++) {
		visited[r + d2 - i][c + d2 - i] = 5;
	}

	r1 = r;
	c1 = c;
	r2 = r + d1;
	c2 = c - d1;
	r3 = r2 + d2;
	c3 = c2 + d2;
	r4 = r3 - d1;
	c4 = c3 + d1;

	// ���ű� �� ���ϱ�
	int number = 0;
	// 1�� ���ű��� 0,0 �������� ã�´�
	for (int i = 0; i < N; i++) {
		if (i >= r2) break;

		for (int j = 0; j < N; j++) {
			if (j > c1) break;
			if (visited[i][j] != 0) break; // 5�� ǥ�õ� �ֵ��� ����
			number += map[i][j];
			// visited[i][j] = 1; // �信�� �ʿ� ������ ����뿡 ����
		}
	}
	numbers.push_back(number);

	// 2�� ���ű��� 0, N-1 �������� ã�´�
	number = 0;
	for (int i = 0; i < N; i++) {
		if (i > r4) break;
		for (int j = N - 1; j >= 0; j--) {
			if (j <= c1) break;
			if (visited[i][j] != 0) break;
			number += map[i][j];
			// visited[i][j] = 2;

		}
	}
	numbers.push_back(number);

	// 3�� ���ű��� (c2, 0)�������� ã�´�
	number = 0;
	for (int i = c2; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i][j] != 0) break;
			if (j >= c3) break;
			number += map[i][j];
			// visited[i][j] = 3;
		}
	}
	numbers.push_back(number);

	// 4�� ���ű��� (r4+1, N-1 �������� ã�´�)
	number = 0;
	for (int i = r4 + 1; i < N; i++) {
		for (int j = N - 1; j >= 0; j--) {
			if (visited[i][j] != 0) break;
			if (j < c3) break;
			number += map[i][j];
			// visited[i][j] = 4;
		}
	}
	numbers.push_back(number);

	// 5�� ���ű�
	number = allSum;
	for (int i = 0; i<numbers.size(); i++) {
		number -= numbers[i];
	}
	numbers.push_back(number);

	// �������� �� ���������� Ȯ�� ����
	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << visited[i][j] << " ";
		}
		cout << endl;
	}
	cout << "====================" << endl;*/

	// ������ ������ ��
	/*for (int i = 0; i < numbers.size(); i++) {
		cout << numbers[i] << " ";
	}
	cout << endl;*/

	// ����
	sort(numbers.begin(), numbers.end());

	int tmpMin = numbers[4] - numbers[0];
	// cout << "tmpMin: " << tmpMin << endl;
	if (tmpMin < minAnswer) minAnswer = tmpMin;
	
}

void Start(int r, int c) {
	int d1 = 1;
	while (r + d1 < N - 1 && c - d1 >= 0) {
		
		int d2 = 1;
		while (r + d1 + d2 < N && c - d1 + d2 < N - 1) {

			// d1, d2 ���� ������ ������ �� ���ϱ�
			Check(r, c, d1, d2);
			d2++;
		}

		d1++;
	}
}

int main() {

	Input();

	// ������ ���ϱ�
	for (int i = 0; i < N - 2; i++) {
		for (int j = 1; j < N - 1; j++) {
			Start(i, j);
		}
	}

	cout << minAnswer;

	return 0;
}