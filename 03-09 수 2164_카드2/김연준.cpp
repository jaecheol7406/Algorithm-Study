/*
BOJ 2164��: ī��2
���� ���� : �ùķ��̼�(Deque)

���� Ǯ�� : Deque�� �־��� ���� ���Ͽ� �������� ����.
            ->dq.pop_back()���� ���� ī�带 ������.
			->�� ���� ���� ī�带 �� �Ʒ��� �ű�.
			->�Ű����� dq�󿡴� ���������Ƿ� pop�������.
			->�̸� dq�� ����� 2�� �ɶ����� while �ݺ�(����� 2�϶� while�� �ȿ��� 1�̵�)
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
		dq.pop_back(); //�� �� ī�� ����
		dq.push_front(dq.back()); //�� ����,���� ���� ī�带 ���� �Ʒ��� �ű��.
		dq.pop_back(); //�Ʒ��� ī�带 �Ű����� �����������
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