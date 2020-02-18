#include <iostream>
using namespace std;

int main() {
	int target;
	scanf("%d", &target);

	if (target <= 99) {
		printf("%d", target);
	}
	else {
		int cnt = 99;

		int num1, num2, num3;
		for (int i = 100; i <= target; i++) {
			num1 = i / 100;
			num2 = (i - num1*100) / 10;
			num3 = (i - num1*100) % 10;

			if ((num1 - num2) == (num2 - num3)) {
				cnt++;
			}
		}
		printf("%d", cnt);
	}

	return 0;
}