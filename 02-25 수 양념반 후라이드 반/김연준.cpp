/*
BOJ 1691 : ��� �� �Ķ��̵� ��

ġŲ�� ���� : ���, �Ķ��̵�, �ݹ�(���+�Ķ��̵�)
ġŲ�� ���� :   A ,   B     ,  C
��� �ּ� X, �Ķ��̵� �ּ� Y

Case 1. �ݹ�ġŲ�� �������� �ʰ� ��� �ּ� ����, �Ķ��̵� �ּ� ����
Case 2. ���, �Ķ��̵� �� �ּҰ��� �ݹ�ġŲ���� �����ϰ� ���� ġŲ ����
Case 3. ���, �Ķ��̵� �� �ִ밪�� ���� �ݹ�ġŲ���� ����
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