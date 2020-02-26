/*
BOJ 1691 : 양념 반 후라이드 반

치킨의 종류 : 양념, 후라이드, 반반(양념+후라이드)
치킨의 가격 :   A ,   B     ,  C
양념 최소 X, 후라이드 최소 Y

Case 1. 반반치킨을 구매하지 않고 양념 최소 구매, 후라이드 최소 구매
Case 2. 양념, 후라이드 중 최소값을 반반치킨으로 구매하고 남은 치킨 구매
Case 3. 양념, 후라이드 중 최대값을 전부 반반치킨으로 구매
*/
#include <iostream>
#include <algorithm>
using namespace std;
int A, B, C, X, Y;
void Input() {
	cin >> A >> B >> C >> X >> Y;
}
void Solution() {
	int case1 = A * X + B * Y;
	int case2;
	int case3;
	if (X > Y) {
		case2 = C * 2 * Y + A * (X - Y);
		case3 = X * C*2;
	}
	else {
		case2 = C * 2 * X + B * (Y - X);
		case3 = Y * C * 2;
	}

	cout << min(min(case1, case2), case3) << endl;
	

}
void Solve() {
	Input();
	Solution();
}
int main() {
	Solve();
	return 0;


}