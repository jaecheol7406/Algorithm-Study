/*
BOJ 1021��: ȸ���ϴ� ť
���� ���� : �ùķ��̼�
function call : main() -> Solve() -> Input() -> Solution()

���� Ǯ�� :  1. �̾ƾ� �Ǵ� ���� �ε����� ���Ѵ�.
			 2. �ε����� �� ���̶�� �̾Ƴ��� ���� �ݺ��� ����
			 3. �� ���� �ƴ϶�� 2�� ������ ������ 3�� ������ ������ ����Ѵ�.
			 4. �� ���� ������ ����.

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