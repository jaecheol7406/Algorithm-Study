/*
1. 2���� �迭 circle[1005][10]�� 1�� ~ T�� ��Ϲ����� �� ���¸� ����д�.
2. i��° ��Ϲ����� ���ƾ� �Ѵٸ�,
      2 ~ i ��° ��Ϲ����� ���� <i�� ��Ϲ����� 6�� ���>�� <i-1�� ��Ϲ����� 2�� ���>�� ���� ���� ���� �����Ѵ�.
      i ~ T-1 ��° ��Ϲ����� ���� <i�� ��Ϲ����� 2�� ���>�� <i+1�� ��Ϲ����� 6�� ���>�� ���� ���� ���� �����Ѵ�.
3. �� ��Ϲ����� ���� ������ ���� ������ ������ ��, ������ ������ ������
*/
#include <iostream>
#include <string.h>
using namespace std;
#define LEFT 6
#define RIGHT 2

// ============ Input =============
int T, K;
int circle[1005][10]; // ��Ϲ��� ����
int roundCir[1005];   // ȸ���ϴ� ��Ϲ��� ��ȣ
int roundDir[1005];	  // ȸ�� ����

// ============ ���� ============
int evalRound[1005];  // �� �Ͽ���, ��Ϲ����� �� ���� (0: ���� �ʴ´�, 1: �ð�, -1: �ݽð�)

void Input() {
	scanf("%d\n", &T);
	for (int i = 1; i <= T; i++) {
		for (int j = 0; j < 8; j++) {
			scanf("%1d", &circle[i][j]);
		}
	}
	scanf("%d\n", &K);
	for (int i = 1; i <= K; i++) {
		scanf("%d %d\n", &roundCir[i], &roundDir[i]);
	}
}

void Print() {
	for (int i = 1; i <= T; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%1d", circle[i][j]);
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 1; i <= K; i++) { 
		printf("%d %d\n", roundCir[i], roundDir[i]);
	}
}

void Round(int idx, int dir) { // idx�� ��ϸ� dir �������� ������. 2.��Ϲ��� ������ ���� ȣ��Ǵ� �Լ�
	int tmp;
	if (dir == 1) { // �ð� ����
		tmp = circle[idx][7];
		for (int i = 7; i >=1; i--) {
			circle[idx][i] = circle[idx][i-1];
		}
		circle[idx][0] = tmp;
	}
	else if (dir == -1) { // �ݽð� ����
		tmp = circle[idx][0];
		for (int i = 0; i <= 6; i++) {
			circle[idx][i] = circle[idx][i+1];
		}
		circle[idx][7] = tmp;
	}

	
}

int main() {

	Input();
	// Print();

	for (int turn = 1; turn <= K; turn++) { // K�� ����

		// ============= 1.��Ϲ������� ���� ���� ��� =============
		for (int i = 1; i <= T; i++) {
			evalRound[i] = 0;
		}

		evalRound[roundCir[turn]] = roundDir[turn]; // �̹��� ����� �Ǿ� �ִ� ���

		for (int i = roundCir[turn]; i >= 2; i--) { // ����� �Ǿ� �ִ� ����� ���ʿ� ����
			if (evalRound[i] == 0) continue;
			if (circle[i][LEFT] == circle[i - 1][RIGHT]) continue;
			evalRound[i - 1] = (-1) * evalRound[i];
		}

		for (int i = roundCir[turn]; i <= T-1; i++) {
			if (evalRound[i] == 0) continue;
			if (circle[i][RIGHT] == circle[i + 1][LEFT]) continue;
			evalRound[i + 1] = (-1) * evalRound[i];
		}

		// ����� ���� ���
		/*for (int i = 1; i <= T; i++) {
			cout << evalRound[i] << " ";
		}
		cout << endl;*/


		// ============= 2.��Ϲ��� ������ =============
		for (int i = 1; i <= T; i++) {
			if (evalRound[i] != 0) {
				Round(i, evalRound[i]);
			}
		}

		// ȸ���� ���
		/*for (int i = 1; i <= T; i++) {
			for (int j = 0; j < 8; j++) {
				cout << circle[i][j];
			}
			cout << endl;
		}
		cout << endl;*/
	}

	int answer = 0;
	for (int i = 1; i <= T; i++) {
		if (circle[i][0] == 1) answer++;
	}
	cout << answer;

	return 0;
}