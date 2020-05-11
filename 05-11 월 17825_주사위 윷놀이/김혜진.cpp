/*
test case #3
5 1 2 3 4 5 5 3 2 4
answer: 214
result: 218
*/
#include <iostream>
#include <vector>

using namespace std;

int point = 0;
int answer = 0;
vector<int> cmd(10, 0);

struct Pos {
	int r;
	int c;
};

vector<vector<int>> board = {
	{2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40},
	{10, 13, 16, 19, 25},
	{20, 22, 24, 25},
	{30, 28, 27, 26, 25},
	{30, 32, 34, 36, 38, 40},
	{25, 30, 35, 40}
};

vector<vector<int>> position(6, vector<int>(20, -1));

vector<Pos> player(4, Pos{ 0, -1 });

void Input() {
	for (int i = 0; i < 10; i++) {
		cin >> cmd[i];
	}
}

Pos calNextPos(int idx, int cnt) {
	
	Pos nextPos = Pos{ 0, 0 };
	Pos thisPos = player[idx];
	int thisR = thisPos.r;
	int thisC = thisPos.c;

	// cout << "calNextPos(" << idx << "," << cnt << ")" << endl;
	if (thisR == 0) {
		if (thisC + cmd[cnt] == 4) {
			nextPos = Pos{ 1, 0 };
		}
		else if (thisC + cmd[cnt] == 9) {
			nextPos = Pos{ 2, 0 };
		}
		else if (thisC + cmd[cnt] == 14) {
			nextPos = Pos{ 3, 0 };
		}
		else if (thisC + cmd[cnt] <= 19) {
			nextPos = Pos{ thisR, thisC + cmd[cnt] };
		}
		else if (thisC + cmd[cnt] > 19) { // 도착
			nextPos = Pos{ thisR, 20 };
		}
	}
	else if (thisR >= 1 && thisR <= 4) {
		int lastIdx = board[thisR].size() - 1;
		if (thisC + cmd[cnt] > lastIdx) {
			int nextIdx = cmd[cnt] - (lastIdx - thisC);
			if (nextIdx > 3) {
				nextPos = Pos{ 0, 20 };
			}
			else {
				nextPos = Pos{ 5, nextIdx };
			}
		}
		else if (thisC + cmd[cnt] == lastIdx) {
			nextPos = Pos{ 5, 0 };
		}
		else {
			nextPos = { thisR, thisC + cmd[cnt] };
		}
	}
	else if (thisR == 5) {
		int lastIdx = board[thisR].size() - 1; // 3

		if (thisC + cmd[cnt] > lastIdx) {
			nextPos = Pos{ 0, 20 }; // 도착
		}
		else {
			nextPos = Pos{ thisR, thisC + cmd[cnt] };
		}
	}

	return nextPos;
}

//vector<int> picked;
void DFS(int cnt) {
	//cout << "DFS(" << cnt << ")" << endl;
	if (cnt >= 10) {
		/*for (int i = 0; i < picked.size(); i++) {
			cout << picked[i];
		}
		cout << "=====" << point << endl;
		cout <<"끝"<< endl;*/

		if (answer < point) answer = point;

		return;
	}

	for (int i = 0; i < 4; i++) {
		if (player[i].r == 0 && player[i].c == 20) continue; // 이미 '도착'한 말은 고를 수 없다
		
		Pos nextPos = calNextPos(i, cnt);
		if (nextPos.c != 20 && position[nextPos.r][nextPos.c] != -1) continue; // 이미 다른 말이 있으면 pass

		//cout << i << "번 선수: " << player[i].r << "," << player[i].c << "<= 현재 위치" << endl;
		//cout << nextPos.r << "," << nextPos.c << "<=다음 위치" << endl;
		
		int backupR = player[i].r;
		int backupC = player[i].c;
		
		// 이동시킨다
		if(player[i].c != -1) // 시작 위치일 때는 -1로 굳이 표시할 게 없음
			position[player[i].r][player[i].c] = -1;
		player[i].r = nextPos.r;
		player[i].c = nextPos.c;
		if (player[i].c != 20) { // 도착했을 경우 -1로 표시할 게 없음
			position[player[i].r][player[i].c] = i;
			point += board[player[i].r][player[i].c];
		}
		
		//picked.push_back(i);

		// cout << "picked player " << i;
		DFS(cnt + 1);
		
		// 원상복구
		if (player[i].c != 20) { // 도착했을 경우 -1로 표시할 게 없음
			position[player[i].r][player[i].c] = -1;
			point -= board[player[i].r][player[i].c];
		}
		
		player[i].r = backupR;
		player[i].c = backupC;
		if(player[i].c != -1)
			position[player[i].r][player[i].c] = i;

		//picked.pop_back();
	}
}

int main() {

	Input();

	DFS(0);

	cout << answer;

	return 0;
}