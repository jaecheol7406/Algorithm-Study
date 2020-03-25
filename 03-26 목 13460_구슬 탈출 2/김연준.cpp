/*
BOJ 13460번: 구슬 탈출2

21% 틀렸습니다....

펑션 콜 순서 : main() -> solve() -> input() -> solution()

*/
#include <iostream>
#include <string>
#include <queue>
using namespace std;
struct Dot {
	int x;
	int y;
};
int N, M;
char board[15][15];
Dot goal, red, blue;
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
void Input() {
	cin >> N >> M;
	string input;
	for (int i = 0; i < N; i++) {
		cin >> input;
		for (int j = 0; j < M; j++) {
			board[i][j] = input[j];
			if (board[i][j] == 'R') {
				board[i][j] = '.';
				red.x = i;
				red.y = j;
			}
			else if (board[i][j] == 'B') {
				board[i][j] = '.';
				blue.x = i;
				blue.y = j;
			}
			else if (board[i][j] == 'O') {
				goal.x = i;
				goal.y = j;
			}
		}
	}
}
void Solution() {
	queue<pair<Dot,int>> redList;
	queue<pair<Dot,int>> blueList;
	redList.push(make_pair(red, 0));
	blueList.push(make_pair(blue, 0));
	while (true) {
		if (redList.size() == 0 || blueList.size() == 0) {
			cout << -1 << endl;
			return;
		}
		auto redCur = redList.front();
		auto blueCur = blueList.front();
		if (redCur.second >= 10) {
			cout << "-1" << endl;
			return;
		}
		//cout << redCur.second << endl;
		//cout << "레드 볼 : " << redCur.first.x << " " << redCur.first.y << endl;
		//cout << "블루 볼 : " << blueCur.first.x << " " << blueCur.first.y << endl;
		redList.pop(); blueList.pop();
		for (int i = 0; i < 4; i++) {
			int redMove = 0;
			//int redNx = redCur.first.x;
			//int ny = redCur.first.y;
			Dot redDot;
			redDot.x = redCur.first.x;
			redDot.y = redCur.first.y;
			
			bool redFlag = false;
			while (true) {

				if (board[redDot.x+dx[i]][redDot.y+dy[i]] == '#') {
					break;
				}
				redDot.x = redDot.x + dx[i];
				redDot.y = redDot.y + dy[i];
				redMove++;
				if (board[redDot.x][redDot.y] == 'O') {
					redFlag = true;
					break;
				}
				
			}
			int blueMove = 0;
			Dot blueDot;
			blueDot.x = blueCur.first.x;
			blueDot.y = blueCur.first.y;
			bool blueFlag = false;
			while (true) {
				if (board[blueDot.x + dx[i]][blueDot.y + dy[i]] == '#')
					break;
				blueDot.x = blueDot.x + dx[i];
				blueDot.y = blueDot.y + dy[i];
				blueMove++;
				if (board[blueDot.x][blueDot.y] == 'O') {
					blueFlag = true;
					break;
					//cout << "-1" << endl;
					//return;
				}
			}
			if (redFlag == true) { //성공
				//값 갱신
				if (blueFlag == false) {
					cout << redCur.second + 1 << endl;

				}
				else
					cout << "-1" << endl;
				return;
				
			}
			if (blueFlag == true)
				continue;

			if (redMove == 0 && blueMove == 0)
				continue;
			if (redDot.x == blueDot.x && redDot.y == blueDot.y) {
				if (redMove < blueMove) {
					blueDot.x -= dx[i];
					blueDot.y -= dy[i];
				}
				else {
					redDot.x -= dx[i];
					redDot.y -= dy[i];
				}
			}

			redList.push(make_pair(redDot, redCur.second + 1));
			blueList.push(make_pair(blueDot, blueCur.second + 1));

		}
	}
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