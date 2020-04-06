/*
BOJ 1021번: 회전하는 큐
문제 유형 : 시뮬레이션
function call : main() -> Solve() -> Input() -> Solution()

문제 풀이 :  1. 뽑아야 되는 수의 인덱스를 구한다.
			 2. 인덱스가 맨 앞이라면 뽑아내고 다음 반복문 진행
			 3. 맨 앞이 아니라면 2번 연산이 빠른지 3번 연산이 빠른지 계산한다.
			 4. 더 빠른 연산을 실행.

*/
#include <iostream>
#include <deque>

using namespace std;
int N, M;
deque<int> deq;
int loc[51];
void Input() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		deq.push_back(i);
	}
	for (int i = 1; i <= M; i++) {
		cin >> loc[i];
	}
}
void Solution() {
	int answer = 0;
	for (int i = 1; i <= M; i++) {
		if (deq.front() == loc[i]) {
			deq.pop_front();
			continue;
		}
		int left_cur=0;
		int right_cur=0;
		for (int j = 0; j < deq.size(); j++) {
			if (deq[j] == loc[i]) {
				left_cur = j;
				break;
			}
		}
		right_cur = deq.size() - left_cur;
		if (left_cur < right_cur) { //
			for (int k = 0; k < left_cur; k++) {
				deq.push_back(deq.front());
				deq.pop_front();
				answer++;
;			}
			deq.pop_front();
		}
		else {
			for (int k = 0; k < right_cur; k++) {
				deq.push_front(deq.back());
				deq.pop_back();
				answer++;
			}
			deq.pop_front();
		}

	}

	cout << answer << endl;
}
void Solve() {
	Input();
	Solution();
}
int main() {
	Solve();
	return 0;

}