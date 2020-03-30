/*
BOJ 2839번: 설탕 배달
function call : main()
문제 풀이 : 1. 5의 배수인지 확인
			2. 5의 배수가 아니면 입력받은 값에서 3을 빼면서 반복.
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