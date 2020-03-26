/*
BOJ 1018번 : 체스판 다시 칠하기
문제 유형 : 시뮬레이션
문제 풀이 : 1. 8x8로 잘라야 하므로 반복문을 0 <= N-8 , 0 <= M-8 로 반복한다
			2. 왼쪽 위가 흰색인 경우 다시 칠해야 하는 정사각형의 개수를 구한다
			3. 왼쪽 위가 검은색 인 경우 다시 칠해야 하는 정사각의 개수를 구한다.
			4. 2,3의 결과중 최소값을 결과값에 갱신.
*/
#include <iostream>
#include <string>
using namespace std;

char board[50][50];
int N, M;
int answer = 987654321;
void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		string input;
		cin >> input;
		for (int j = 0; j < M; j++) {
			board[i][j] = input[j];
		}
	}
}
void getWhite(int x, int y) {
	int cnt = 0;
	for (int i = x; i < x + 8; i++) {
		for (int j = y; j < y + 8; j++) {
			if ((i + j) % 2 == 0) {
				if (board[i][j] != 'W')
					cnt++;
			}
			else {
				if (board[i][j] != 'B')
					cnt++;
			}
		}
	}
	if (answer > cnt)
		answer = cnt;
}
void getBlack(int x, int y) {
	int cnt = 0;
	for (int i = x; i < x + 8; i++) {
		for (int j = y; j < y + 8; j++) {
			if ((i + j) % 2 == 0) {
				if (board[i][j] != 'B')
					cnt++;
			}
			else {
				if (board[i][j] != 'W')
					cnt++;
			}
		}
	}
	if (answer > cnt)
		answer = cnt;
}
void Solution() {
	for (int i = 0; i <= N - 8; i++) {
		for (int j = 0; j <= M - 8; j++) {
			//cout << i << " " << j << endl;
			getWhite(i,j);
			getBlack(i,j);
		}
	}
	cout << answer << endl;
}
void Solve() {
	Input();
	Solution();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	Solve();
	return 0;
}