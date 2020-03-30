/*
BOJ 2839��: ���� ���
function call : main()
���� Ǯ�� : 1. 5�� ������� Ȯ��
			2. 5�� ����� �ƴϸ� �Է¹��� ������ 3�� ���鼭 �ݺ�.
*/

#include <iostream>
#include <algorithm>
using namespace std;
int main() {
	int N;
	cin >> N;
	int answer = 0;
	while (N > 0) {
		if (N % 5 == 0) {
			answer += N / 5;
			N %= 5;
			break;
		}
		N = N - 3;
		answer++;
	}
	if (N == 0) 
		cout << answer << endl;
	else
		cout << "-1" << endl;
	return 0;
}