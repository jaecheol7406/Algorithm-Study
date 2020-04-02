/*
function call: main 함수 하나

N의 생성자는 항상 N보다 작다.
그리고 N의 생성자가 될 수 있는 가능성이 있으면서 가장 작은 수인
N - (9 * (N의 자리수-1)) 에서부터 차례로 N의 생성자가 될 수 있는지 조건을 확인한다.

N = 216일 때는 216 - 18 인 198 보다 작으면 안된다.
198보다 작은 수의 분해합은 216보다 작기 때문이다.
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
		// cout << start << "를 검증" << endl;

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