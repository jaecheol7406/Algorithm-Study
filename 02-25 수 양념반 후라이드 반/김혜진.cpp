/*
case 1: �ݹ��� �ʹ� ��μ� ��� �Ķ��̵� ���� ��� �� ���� ���
case 2: �ݹ��� ������ �� ���� ���
        1) ���, �Ķ��̵� ���԰��� �� �� ���� ������ŭ�� �ݹ����� ��� �������� ��ǰ ����
		2) �� �� ������ �ݹ����� ����
*/
#include <iostream>
#include <algorithm>
using namespace std;

int A, B, C, X, Y;

void Input() {
	scanf("%d %d %d %d %d", &A, &B, &C, &X, &Y);
}

int main() {

	Input();

	int MIN = 9900000000;
	int half = 0;
	int amount = 0;
	
	if (A + B < 2 * C) { // �ݹ�ġŲ�� ���
		amount = A * X + B * Y;
		if (MIN > amount) MIN = amount;
	}
	else { // �ݹ�ġŲ�� ���� ���� ���� ����

		// �� ���� ������ŭ�� �Ķ��̵�� ��� �������� ��ǰ ����
		half = min(X, Y) * 2;
		amount = (X - half/2) * A + (Y - half/2) * B + half * C;
		if (MIN > amount) MIN = amount;

		// �� �� ������ �ݹ����� ����
		/*half = max(X, Y) * 2;
		amount = half * C;
		if (MIN > amount) MIN = amount;*/
	}

	/* �ð��ʰ�for (int x = X; x >= 0; x--) {
		for (int y = Y; y >= 0; y--) {
			half += max(X - x, Y - y);
			amount = (A * x) + (B * y) + (C * half) * 2;

			if (MIN > amount) {
				MIN = amount;
			}

			amount = 0;
		}
	}*/ 

	cout << MIN;

	return 0;
}