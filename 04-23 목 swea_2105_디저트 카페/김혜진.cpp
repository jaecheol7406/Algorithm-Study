/*
function call: main -> (Input -> Start -> Check) -> main

1. ���������� '������' '���� �Ʒ�'�� '�� �Ʒ�' ������ ���� �� �ִ� ������ ���Ѵ�
2. �� ������ ���� �� �� �� ���� ���� ���Ѵ�(rightN, leftN)
3. �� ������ rightN�� leftN ������ ������ �׸��� �̹� ���� ����Ʈ ���� visited �� ǥ���Ѵ�.
4. ����Ʈ ���� ������ ��ġ�� ������, (leftN + rightN)*2 ��ŭ ����Ʈ�� ���� ���̴�. �� ���� ���� ū ���� ����Ѵ�

�ǹ���
43�� �ٿ� ���
*/
#include <iostream>
using namespace std;

int N;
int map[25][25];
int visited[120];
int visitedSupport[120];
int maxAnswer = 0;
int tmpAnswer = 0;

int tmpR1, tmpC1, tmpR2, tmpC2;

void Input() {
	maxAnswer = 0;

	scanf("%d\n", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
}

void Init() {
	for (int i = 1; i <= 100; i++) {
		visited[i] = 0;
	}
}

void Check(int r, int c, int rightN, int leftN) {
	Init();
	// visited[map[r][c]] = 1; �긦 �츮�� 59���� leftN-1 ������ �ϸ� 49���� �´´ٰ� �����µ� ������ �𸣰���.

	for (int i = 0; i < rightN; i++) {
		r++;
		c--;

		if (visited[map[r][c]] == 1) return;
		visited[map[r][c]] = 1;
	}

	for (int i = 0; i < leftN; i++) {
		r++;
		c++;

		if (visited[map[r][c]] == 1) return;
		visited[map[r][c]] = 1;
	}

	for (int i = 0; i < rightN; i++) {
		r--;
		c++;

		if (visited[map[r][c]] == 1) return;
		visited[map[r][c]] = 1;
	}

	for (int i = 0; i < leftN; i++) {
		r--;
		c--;

		if (visited[map[r][c]] == 1) return;
		visited[map[r][c]] = 1;
	}
	
	tmpAnswer = (rightN + leftN) * 2;
	// cout << tmpAnswer << endl;
	if (tmpAnswer > maxAnswer) maxAnswer = tmpAnswer;
}

void Start(int r, int c) {
	// cout << "������: " << r << "," << c << endl;
	tmpR1 = r;
	tmpC1 = c;

	while (1) {
		
		visited[map[r][c]] = 1;

		// ���� �Ʒ��� ���鼭 ��1�� ���Ѵ�
		tmpR1++;
		tmpC1--;

		if (tmpR1 > N - 2 || tmpC1 < 0) break;
		
		// cout << " ������: " << tmpR1 << "," << tmpC1 << endl;

		// ������ �Ʒ��� ���鼭 ��2�� ���Ѵ�
		tmpR2 = tmpR1;
		tmpC2 = tmpC1;

		while (1) {
			tmpR2++;
			tmpC2++;

			if (tmpR2 > N - 1 || tmpC2 > N - 2) break;
			// cout << "  �Ʒ�����: " << tmpR2 << "," << tmpC2 << endl;

			Check(r, c, (tmpR1 - r), (tmpR2 - tmpR1));

		}
	}
	
}

int main() {

	int T;
	scanf("%d\n", &T);

	for (int t = 1; t <= T; t++) {
		Input();

		for (int i = 0; i < N - 2; i++) {
			for (int j = 1; j < N - 1; j++) {
				Start(i, j);
			}
		}

		if (maxAnswer == 0) cout << "#" << t << " " << -1 << endl;
		else cout << "#" << t << " " << maxAnswer << endl;
	}

	

	return 0;
}