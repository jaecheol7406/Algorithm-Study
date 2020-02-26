/*
case 1: 반반이 너무 비싸서 양념 후라이드 따로 사는 게 나은 경우
case 2: 반반을 섞어사는 게 나은 경우
        1) 양념, 후라이드 구입개수 중 더 적은 개수만큼만 반반으로 사고 나머지는 단품 구매
		2) 둘 다 무조건 반반으로 구매
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
	
	if (A + B < 2 * C) { // 반반치킨이 비쌈
		amount = A * X + B * Y;
		if (MIN > amount) MIN = amount;
	}
	else { // 반반치킨을 섞어 쓰는 것이 좋음

		// 더 적은 개수만큼만 후라이드로 사고 나머지는 단품 구매
		half = min(X, Y) * 2;
		amount = (X - half/2) * A + (Y - half/2) * B + half * C;
		if (MIN > amount) MIN = amount;

		// 둘 다 무조건 반반으로 구매
		/*half = max(X, Y) * 2;
		amount = half * C;
		if (MIN > amount) MIN = amount;*/
	}

	/* 시간초과for (int x = X; x >= 0; x--) {
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