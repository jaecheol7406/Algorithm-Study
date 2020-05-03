/*
BOJ 17281��: �߱�
���� ���� : �ùķ��̼�(DFS)


1. DFS�� �̿��� ������ �������� Ÿ���� ���Ѵ�.
	-> 2��~9�� Ÿ�ڸ� Ÿ���� �����ְ�, �� ���ϸ� 1�������� 4��Ÿ�ڿ� �־��ش�.
2. Ÿ���� ��������, N�̴��� �����ϰ� ������ ���� (play())
3. �� �翡 �ִ� ������ ru�迭�� ǥ���Ѵ�.
	-> Ÿ���� �ִ� ������ ����� ���� �� �翡�ִ� ������ ���� or Ȩ�� ��Ų��.
	-> Ÿ���� �ִ� ������ Ȩ���̶�� ������ �÷��ְ�, ��Ÿ��� �����Ŵ.
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
int N;
int board[51][10];
bool visit[10];
vector<int> v;
int arr[5] = { 1,2,3,4,5 };
int ru[4];
int score;
int result = 0;
void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= 9; j++) {
			cin >> board[i][j];
		}
	}
}
void go(int player, int ta) {
	for (int i = 3; i >= 1; i--) {
		if (ru[i] != 0) {
			if (i + ta >= 4) { //Ȩ��
				ru[i] = 0;
				score++;
			}
			else { //����
				ru[i + ta] = ru[i];
				ru[i] = 0;
			}
		}
	}
	if (ta == 4) {//Ȩ��
		score++;
	}
	else { //����
		ru[ta] = player;
	}
}
void Play() {
	score = 0;
	int idx = 0;
	int out_cnt;

	for (int i = 1; i <= N; i++) {//N�̴�
		memset(ru, 0, sizeof(ru));
		out_cnt = 0;
		while (out_cnt < 3) {
			int player = v[idx];
			if (board[i][player] == 0) {
				out_cnt++;
			}
			else {
				go(player, board[i][player]);
			}
			if (++idx == 9)
				idx = 0;
		}
	}
}
void DFS(int cnt) {
	if (cnt == 8) {
		v.insert(v.begin() + 3, 1); //1�������� 4��Ÿ�ڿ� �־���.
		Play();
		v.erase(v.begin() + 3); //����Ʈ ����
		result = max(result, score);
	}
	for (int i = 2; i <= 9; i++) {
		if (visit[i])
			continue;
		visit[i] = true;
		v.push_back(i);
		DFS(cnt + 1);
		v.pop_back();
		visit[i] = false;
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