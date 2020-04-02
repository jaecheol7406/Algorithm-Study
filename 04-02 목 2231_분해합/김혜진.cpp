/*
function call: main �Լ� �ϳ�

N�� �����ڴ� �׻� N���� �۴�.
�׸��� N�� �����ڰ� �� �� �ִ� ���ɼ��� �����鼭 ���� ���� ����
N - (9 * (N�� �ڸ���-1)) �������� ���ʷ� N�� �����ڰ� �� �� �ִ��� ������ Ȯ���Ѵ�.

N = 216�� ���� 216 - 18 �� 198 ���� ������ �ȵȴ�.
198���� ���� ���� �������� 216���� �۱� �����̴�.
*/
#include <iostream>
using namespace std;

int N;

int main() {

	scanf("%d", &N);

	int posNum = 0;
	int target = N;

	while (target / 10 >= 1) {
		posNum++;
		target /= 10;
	}

	int start = N - (9 * posNum);

	while (start < N) {
		int sum = start;
		// cout << start << "�� ����" << endl;

		target = start;
		while (target >= 1) {
			// cout << sum << " + " << target % 10 << endl;
			sum += target % 10;
			target /= 10;
		}

		if (sum == N) {
			cout << start;
			return 0;
		}

		start++;
	}

	cout << 0;

	return 0;
}