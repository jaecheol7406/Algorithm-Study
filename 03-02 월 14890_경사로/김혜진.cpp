/*
int map[110][110];		���� �迭
int visited[110][110];	���θ� ���Ҵ��� ����

1. ��� �� ����
��� ���� ���Ͽ�
  �̹� ���ΰ� �����Ǿ� �ִ� ���, ���� ���� ����
  �̹����� != �������� �� ���
    1) �̹����� > ���������� ������ �������� ���� L���� ���Ͽ� ����
	   ���� ���� 1����, ������ ����� �ʴ���, �̹� ���ΰ� �������� ������
	   => ������ �����ϴ� ���, ���� ����
	2) �̹����� < ���������� ������ �̹����� ���� L���� ���Ͽ� ����
	   ���� ���� 1����, ������ ����� �ʴ���, �̹� ���ΰ� �������� ������
	   => ������ �����ϴ� ���, ���� ����

������ ������ ���縦 ������ ���, ī���͸� �ϳ� ���Ѵ�.

2. ���� �迭�� �ʱ�ȭ
3. ��� �� ����: 1���� �����ϰ� ����
*/
#include <iostream>
#include <stdlib.h>
using namespace std;

int map[110][110];
int visited[110][110];
int N,L;

int cnt = 0;	// �� �� �ִ� ���� ����
int before;		// ������ ����

void Input() {
	scanf("%d %d\n", &N, &L);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", map[i][j]);
		}
		cout << endl;
	}
}


void SearchRow() {
	for (int i = 0; i < N; i++) {
		before = map[i][0];								// ������ ���� �ʱ�ȭ
		for (int j = 0; j < N; j++) {
			if (visited[i][j] == 1) {			// ���θ� ����� �� ��(���� ��� ������ �̹� ������)
				if (j == N - 1) {				// ������ ��ġ�� ���θ� ������ ��� cnt++ �� ��ġ�� ���ϴ� ���� ����
					cnt++;
				}
				continue;
			}
			if (map[i][j] != before) {					// ���̰� �ٸ���
				if (abs(before - map[i][j]) != 1)break;	// ���̰� 1�� �ƴϸ� ���� ����
				if (map[i][j] > before) {				// ��������. (��: 2 2 3)
					if (j - L < 0) break;					// ���ΰ� ������ ����� ��� �� ���� ����
					int breakFlag = 0;
					for (int t = j - L; t < j; t++) {
						if (map[i][t] != before) breakFlag = 1;		// ���̰� �޶� ���θ� ���� �� ���� ��� �� ���� ����
						if (visited[i][t] != 0) breakFlag = 1;		// �̹� �ش� ��ġ�� ���θ� ���� ��� �� ���� ����
					}
					if (breakFlag == 1) break;
					for (int t = j - L; t < j; t++) {		// ���θ� ���´�
						visited[i][t] = 1;
					}
				}
				else if (map[i][j] < before) {			// �������� (��: 3 2 2)
					if (j + L > N) break;					// ���ΰ� ������ ����� ��� �� ���� ����
					
					int breakFlag = 0;
					for (int t = j; t < j + L; t++) {
						if (map[i][t] != map[i][j]) breakFlag=1;	// ���̰� �޶� ���θ� ���� �� ���� ��� �� ���� ����
						if (visited[i][t] != 0) breakFlag=1;		// �̹� �ش� ��ġ�� ���θ� ���� ��� �� ���� ����
					}
					if (breakFlag == 1) break;
					for (int t = j; t < j + L; t++) {		// ���θ� ���´�
						visited[i][t] = 1;
					}
				}
			}
			before = map[i][j];
			if (j == N - 1) {
				cnt++;
			}
		}
	}
}

void SearchColumn() {
	for (int j = 0; j < N; j++) {
		before = map[0][j];								// ������ ���� �ʱ�ȭ
		for (int i = 0; i < N; i++) {
			if (visited[i][j] == 1) {			// ���θ� ����� �� ��(���� ��� ������ �̹� ������)
				if (i == N - 1) {				// ������ ��ġ�� ���θ� ������ ��� cnt++ �� ��ġ�� ���ϴ� ���� ����
					cnt++;
					
				}
				continue;
			}
			if (map[i][j] != before) {
				if (abs(before - map[i][j]) != 1)break;	// ���̰� 1�� �ƴϸ� ���� ����
				if (map[i][j] > before) {				// ��������. (��: 2 2 3)
					if (i - L < 0) break;					// ���ΰ� ������ ����� ��� �� ���� ����
					int breakFlag = 0;
					for (int t = i - L; t < i; t++) {
						if (map[t][j] != before) breakFlag=1;		// ���̰� �޶� ���θ� ���� �� ���� ��� �� ���� ����
						if (visited[t][j] != 0) breakFlag=1;		// �̹� �ش� ��ġ�� ���θ� ���� ��� �� ���� ����
					}
					if (breakFlag == 1) break;
					for (int t = i - L; t < i; t++) {
						visited[t][j] = 1;
					}
				}
				else if (map[i][j] < before) {				// �������� (��: 3 2 2)
					if (i + L > N) break;					// ���ΰ� ������ ����� ��� �� ���� ����
					int breakFlag = 0;
					for (int t = i; t < i + L; t++) {
						if (map[t][j] != map[i][j]) breakFlag = 1;	// ���̰� �޶� ���θ� ���� �� ���� ��� �� ���� ����
						if (visited[t][j] != 0) breakFlag = 1;		// �̹� �ش� ��ġ�� ���θ� ���� ��� �� ���� ����
					}
					if (breakFlag == 1) break;
					for (int t = i; t < i + L; t++) {
						visited[t][j] = 1;
					}
				}
			}
			before = map[i][j];
			if (i == N - 1) {
				cnt++;
			}
		}
	}
}

int main(){

	Input();

	SearchRow();

	// ���θ� ���� ��ġ ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[i][j] = 0;
		}
	}

	SearchColumn();

	cout << cnt;
	return 0;
}