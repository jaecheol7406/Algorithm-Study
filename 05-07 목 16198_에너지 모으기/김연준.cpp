/*
BOJ 16198��: ������ ������
���� ���� : �ùķ��̼�(DFS)

DFS�� Ž��
-> �ش� ������ ���� vector erase�ؼ� �����
-> �� ������ ���� ��Ͱ� ������ �ٽ� vector�� insert ���ش�.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N;
vector<int> board;
int result=0;
void Input() {
	cin >> N;
	int val;
	for (int i = 0; i < N; i++) {
		cin >> val;
		board.push_back(val);
	}
}
void print(vector<int> board) {
	cout << "--------------" << endl;
	for (int i = 0; i < board.size(); i++) {
		cout << board[i] << " ";
	}
	cout << endl;
}
void DFS(int w) {
	if (board.size() == 2) {
		result = max(result, w);
		return;
	}
	for (int i = 1; i < board.size()-1; i++) {
		w += board[i - 1] * board[i + 1];
		int val = board[i];
		board.erase(board.begin() + i);
		DFS(w);
		board.insert(board.begin() + i, val);
		w -= board[i - 1] * board[i + 1];
	}


}
void Solution() {
	DFS(0);
	cout << result << endl;
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