/*
BOJ 15685번: 드래곤 커브
문제 유형 : 시뮬레이션

1. K세대 드래곤 커브의 방향은( K-1세대 드래곤 커브가 진행한 방향 + 그 방향들의 역순에 (+1%4)연산을 해준 값 이 되는 규칙을 가진다.  (블로그 참고..)
2. 먼저 0세대를 그리고 0세대의 끝점을 기준으로 다음 세대의 드래곤 커브를 구함.
3. 각 세대의 드래곤 커브의 점을 visit배열에 체크하고, 모든 드래곤커브를 구하고,  100x100 배열을 순회하면서 정답을 구한다.

문제 이해 조차 어려웠던 어려운문제

다시 한번 풀어보기
*/
#include <iostream>
#include <vector>
using namespace std;
struct curve {
	int x;
	int y;
	int dir;
	int gen;
};
int N;
int board[100][100];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,-1,0,1 };
bool visit[101][101];
vector<curve> curve_list;
vector<int> dir_list;
int x, y;
void Input() {
	cin >> N;
	curve input;
	for (int i = 0; i < N; i++) {
		cin >> input.x >> input.y >> input.dir >> input.gen;
		curve_list.push_back(input);
	}
}
void nextCurve() {
	int size = dir_list.size();
	for (int i = size-1; i >= 0; i--) {
		int nd = dir_list[i];
		nd = (nd + 1) % 4;
		x += dx[nd];
		y += dy[nd];
		visit[y][x] = true;
		dir_list.push_back(nd);
	}
}
int getAnswer() {
	int result = 0;
	for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 100; j++) {
			if (visit[i][j] && visit[i][j + 1] && visit[i + 1][j] && visit[i + 1][j + 1])
				result++;
		}
	}
	return result;
}
void Solution() {
	for (int i = 0; i < N; i++) {
		dir_list.clear();
		//0세대
		x = curve_list[i].x;
		y = curve_list[i].y;
		visit[y][x] = true;
		x = x + dx[curve_list[i].dir];
		y = y + dy[curve_list[i].dir];
		visit[y][x] = true;
		dir_list.push_back(curve_list[i].dir);
		for (int j = 0; j < curve_list[i].gen; j++) {
			//다음 세대 그리기
			nextCurve();
		}
	}
	cout << getAnswer() << endl;
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