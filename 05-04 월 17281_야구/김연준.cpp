/*
BOJ 17281번: 야구
문제 유형 : 시뮬레이션(DFS)


1. DFS를 이용한 순열로 선수들의 타순을 정한다.
	-> 2번~9번 타자만 타순을 정해주고, 다 정하면 1번선수를 4번타자에 넣어준다.
2. 타순이 정해지면, N이닝을 진행하고 점수를 구함 (play())
3. 각 루에 있는 선수를 ru배열에 표시한다.
	-> 타석에 있는 선수의 결과에 따라 각 루에있는 선수를 진루 or 홈인 시킨다.
	-> 타석에 있는 선수가 홈런이라면 점수만 올려주고, 안타라면 진루시킴.
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
			if (i + ta >= 4) { //홈인
				ru[i] = 0;
				score++;
			}
			else { //진루
				ru[i + ta] = ru[i];
				ru[i] = 0;
			}
		}
	}
	if (ta == 4) {//홈런
		score++;
	}
	else { //진루
		ru[ta] = player;
	}
}
void Play() {
	score = 0;
	int idx = 0;
	int out_cnt;

	for (int i = 1; i <= N; i++) {//N이닝
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
		v.insert(v.begin() + 3, 1); //1번선수를 4번타자에 넣어줌.
		Play();
		v.erase(v.begin() + 3); //리스트 복원
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