/*
BOJ 2231번: 분해합
문제 유형 : 브루트포스
문제 풀이 : 분해합 계산 시, 분해합 계산해야하는 값을 string으로 변환하고 각 자리수를 더해준다.
			
			하지만, int자료형을 유지하고 계산하는 것 보다 훨씬 느리다.
*/
#include <iostream>
#include <string>
using namespace std;
int N;
int answer = 0;
int main() {
	cin >> N;
	string tmp;
	int val;
	for (int i = 1; i < N; i++) {
		val = i;
		tmp = to_string(i);
		for (int j = 0; j < tmp.size(); j++) {
			val += tmp[j] - '0';
		}
		if (val == N) {
			answer = i;
			break;
		}


	}
	cout << answer << endl;
	return 0;
}