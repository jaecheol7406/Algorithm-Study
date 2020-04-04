/*
function call: main �Լ� �ϳ�

��� ã�ƾ� �ϴ� ���ڿ� ����, (����: ���� ��ġ�� 2�̰�, 4�� ã�ư��� �Ѵٸ�)
1. 2�� �������� ���ڸ� ã�ư��� ��� => step: 3
�ۡܡܡܡ� 
2. 3�� �������� ���ڸ� ã�ư��� ��� => step: 4
�ܡܡۡܡ�
�� �� ��� �� step ���� �� ���� ���� ����

���ǻ���
1. �̹� ã�Ƴ��� ť���� ����� ���Ҹ� �� ����ϱ�
2. ���Ҹ� ã�Ƴ� �� �� �����ʿ� �ִ� ���ҿ��� ���� round�� ���۵�
*/
#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int targets[60]; // ã�ƾ� �ϴ� ��
int found[60]; // �̹� ã�� ������ ��:1

int main() {

	scanf("%d %d\n", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d ", &targets[i]);
	}

	int nowNum = 1;
	int targetNum = 0;

	int sum1 = 0;
	int sum2 = 0;

	int startNum = 1;
	int endNum = 1;

	int answer = 0;

	for (int i = 0; i < M; i++) {
		targetNum = targets[i];
		sum1 = 0;
		sum2 = 0;

		// 2�� ����
		if (nowNum < targetNum) { // ���� ��ġ�� target ��ġ�� ��� ��
			startNum = nowNum;
			endNum = targetNum;
		}
		else {
			startNum = targetNum;
			endNum = nowNum;
		}

		sum1 = endNum - startNum;

		for (int j = startNum + 1; j < endNum; j++) { // �̹� ã�Ƴ��� ����� ���Ҵ� step���� ����
			if (found[j] == 1) {
				sum1--;
			}
		}

		// 3�� ����
		if (nowNum < targetNum) { // ���� ��ġ�� target ��ġ�� ��� ��
			startNum = targetNum;
			endNum = nowNum;
		}
		else {
			startNum = nowNum;
			endNum = targetNum;
		}
		
		sum2 = endNum + (N - startNum);
		for (int j = 1; j < endNum; j++) { // �̹� ã�Ƴ��� ����� ���Ҵ� step���� ����
			if (found[j] == 1) {
				sum2--;
			}
		}
		for (int j = startNum + 1; j <= N; j++) {
			if (found[j] == 1) {
				sum2--;
			}
		}

		// cout << "���� " << nowNum << " ��ǥ: " << targetNum << " sum1: " << sum1 << " sum2: " << sum2 << endl;
		if (sum1 <= sum2) {
			answer += sum1;
		}
		else {
			answer += sum2;
		}
		found[targetNum] = 1;

		for (int j = 1; j <= N; j++) { // ���� ���� ��ġ ���� (targetNum ���� �����ʿ� �ִ� ������� �ʰ� ���� �ִ� ����)
			if (found[(targetNum + j) % (N + 1)] != 1 && (targetNum + j) % (N + 1) != 0) {
				nowNum = (targetNum + j) % (N + 1);
				break;
			}
		}
		// cout << "nowNum: " << nowNum << endl;

	}

	cout << answer;

	return 0;
}