/*
BOJ 10871: X���� ���� ��
function call : main

���� Ǯ�� : �Է¹��� ���� X�� ���Ͽ� ������ ���.
*/
#include <iostream>

using namespace std;

int main() {
	int N, X,num;
	cin >> N >> X;
	for (int i = 0; i < N; i++) {
		cin >> num;
		if (num < X) {
			cout << num << " ";
		}
	}
	return 0;
}