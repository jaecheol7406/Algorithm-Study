/*
BOJ 2164번: 카드2
문제 유형 : 시뮬레이션(Deque)

문제 풀이 : Deque에 주어진 수에 대하여 역순으로 저장.
            ->dq.pop_back()으로 맨위 카드를 버린다.
			->그 다음 맨위 카드를 맨 아래에 옮김.
			->옮겼지만 dq상에는 남아있으므로 pop해줘야함.
			->이를 dq의 사이즈가 2가 될때까지 while 반복(사이즈가 2일때 while문 안에서 1이됨)
*/
#include <iostream>
#include <deque>
using namespace std;
int N;
deque<int> dq;
void Input() {
	cin >> N;
	for (int i = N; i >= 1; i--) {
		dq.push_back(i);
	}
}
void Solution() {
	while (dq.size() > 1) {
		dq.pop_back(); //맨 위 카드 버림
		dq.push_front(dq.back()); //그 다음,제일 위에 카드를 제일 아래에 옮긴다.
		dq.pop_back(); //아래에 카드를 옮겼으니 제거해줘야함
	}
	cout << dq.front() << endl;
}
void Solve() {
	Input();
	Solution();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();

	return 0;
}