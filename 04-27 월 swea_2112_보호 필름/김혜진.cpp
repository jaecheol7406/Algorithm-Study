/*
function call: main -> Input -> (DFS -> Check) -> main

1. �� �ึ�� 0 �Ǵ� 1 �Ǵ� 2�� �ߺ� �ְ� ������ �̴´� (��: W=4�� 0000, 0001 ...)
2. �̴� �Ͱ� `���ÿ�` �ش� �࿡ �๰�� �װ� tmpAnswer++ ��Ų��.
3. minAnswer���� tmpAnswer�� ���� ������, �� ���� �࿡�� �๰�� �̾ƺ���.
4. ��� ���� �� �̰� �� �� tmpAnswer�� minAnswer�� ���Ѵ�.
5. ���� �� öȸ�� �� `���ÿ�` ������ ���� ������Ų��

������: �ð��ʰ�
*/
#include <iostream>
using namespace std;

int D, W, K;
int map[15][25];
int backup[15][25];

int minAnswer = 20;
int picked[15]; // 0:��ǰ����x   1:��ǰ A(0)����   2:��ǰ B(1)����
int tmpAnswer;

void Input() {
	minAnswer = 20;
	tmpAnswer = 0;
	scanf("%d %d %d\n", &D, &W, &K);
	for (int i = 0; i < D; i++) {
		for (int j = 0; j < W; j++) {
			scanf("%d ", &map[i][j]);
			backup[i][j] = map[i][j];
		}
	}
}

void Print() {
	for (int i = 0; i < D; i++) {
		for (int j = 0; j < W; j++) {
			printf("%d ", map[i][j]);
		}
		cout << endl;
	}
}

bool Check() {
	for (int j = 0; j < W; j++) {
		int lastStatus = map[0][j];
		int num = 1;

		for (int i = 1; i < D; i++) {
			if (lastStatus == map[i][j]) {
				num++;
				if (num >= K) break; // �̹��� �Ǵ°� Ȯ�������� �������� �Ѿ��
			}
			else {
				lastStatus = map[i][j];
				num = 1;
			}
		}

		// �̹� j������ ������ �� �� ���
		if (num < K) return false;
	}

	return true;
}

void DFS(int cnt) {
	if (cnt >= D) {

		/*cout << endl;
		Print();
		cout << endl;*/

		if (Check()) { // �̹��� ��
			if (tmpAnswer < minAnswer) minAnswer = tmpAnswer;
		}

		return;
	}

	for (int i = 0; i < 3; i++) {
		// cout << i;
		if (i != 0) { // �ð� ���̱� 1: ���� �̾Ƴ��� �Ź� �� �ٲ㺸�� �� �ƴ϶�, �����ϸ鼭 ���ÿ� �ٲٱ�
			for (int j = 0; j < W; j++) {
				map[cnt][j] = i - 1;
			}
			tmpAnswer++;
		}
		
		if (tmpAnswer < minAnswer) { // �ð� ���̱� 2: �̹� ���̽��� ������ �ּҰ� �ȵ� �� �������� �׸��ϱ�
			DFS(cnt + 1);
		}

		if (i != 0) { // �ð� ���̱� 1: ���� �̾Ƴ��� �Ź� �� �ٲ㺸�� �� �ƴ϶�, �����ϸ鼭 ���ÿ� �ٲٱ�
			for (int j = 0; j < W; j++) {
				map[cnt][j] = backup[cnt][j];
			}
			tmpAnswer--;
		}
		
	}
}

int main() {

	int test;
	scanf("%d\n", &test);
	for (int testCase = 1; testCase <= test; testCase++) {
		Input();

		cout << "#" << testCase << " ";

		if (Check()) { // ó������ ���� ������ ���
			cout << 0 << endl;
		}
		else {
			DFS(0);
			cout << minAnswer << endl;
		}
	}

	return 0;
}