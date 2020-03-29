/*
BOJ 10871: X보다 작은 수
function call : main

문제 풀이 : 입력받은 값과 X를 비교하여 작으면 출력.
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