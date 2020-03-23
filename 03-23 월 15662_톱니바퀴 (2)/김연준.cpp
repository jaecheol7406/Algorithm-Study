/*
BOJ 15662번: 톱니바퀴(2)
문제 유형 : 시뮬레이션

<문제 풀이>
1. 회전시키는 톱니바퀴를 기준으로, 오른쪽에 있는 톱니바퀴들의 방향을 구하여 dir배열에 저장
2. 회전시키는 톱니바퀴를 기준으로, 왼쪽에 있는 톱니바퀴들의 방향을 구하여 dir 배열에 저장
3. 1,2번 도중에 회전하지 않는 톱니바퀴를 발견하면 return하여 방향을 구하지 않는다.(기존에 0으로 세팅)
4. 톱니바퀴를 회전 시킨다. dir이 0이면 회전하지 않고 1이면 시계, -1이면 반시계
5. 결과 도출.
*/
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
int T,K;
int gear[1001][8];
int dir[1001];
vector<pair<int, int>> cmd;
void Input() {
	cin >> T;
	for (int i = 1; i <= T; i++) {
		string input;
		cin >> input;
		for (int j = 0; j < input.size(); j++) {
			gear[i][j] = input[j]-'0';
		}
	}
	cin >> K;
	for (int i = 0; i < K; i++) {
		int num, dir;
		cin >> num >> dir;
		cmd.push_back(make_pair(num, dir));
	}
}
void rotateRightGear(int nowGear, int nowDir) {
	for (int i = nowGear; i < T; i++) {
		if (gear[i][2] != gear[i + 1][6]) {
			dir[i + 1] = nowDir * -1;
		}
		else
			return;
		nowDir = nowDir * -1;
	}
}
void rotateLeftGear(int nowGear, int nowDir) {
	for (int i = nowGear; i > 1; i--) {
		if (gear[i][6] != gear[i - 1][2]) {
			dir[i - 1] = nowDir * -1;
		}
		else
			return;
		nowDir = nowDir * -1;
	}
}
void rotate() {
	for (int i = 1; i <= T; i++) {
		if (dir[i] == 0)
			continue;
		else if (dir[i] == 1) { //시계방향
			int tmp = gear[i][7];
			for (int j = 7; j >= 1; j--) {
				gear[i][j] = gear[i][j - 1];
			}
			gear[i][0] = tmp;
		}
		else { //반시계방향
			int tmp = gear[i][0];
			for (int j = 0; j <= 6; j++) {
				gear[i][j] = gear[i][j + 1];
			}
			gear[i][7] = tmp;
		}
	}
}
void getAnswer() {
	int answer = 0;
	for (int i = 1; i <= T; i++) {
		if (gear[i][0] == 1)
			answer++;
	}
	cout << answer << endl;
}
void print() {
	
	for (int i = 1; i <= T; i++) {
		cout << "회전방향 : " << dir[i] << endl;
		for (int j = 0; j < 8; j++) {
			cout << gear[i][j] << " ";
		}
		cout << endl;
	}
}
void Solution() {
	for (int i = 0; i < cmd.size(); i++) {
		int nowGear = cmd[i].first;
		int nowDir = cmd[i].second;
		dir[nowGear] = nowDir;
		//오른쪽 회전 방향 구하기
		rotateRightGear(nowGear,nowDir); //1번
		//왼쪽 회전 방향 구하기
		rotateLeftGear(nowGear,nowDir); //2번
		//회전하기 
		rotate();//4번

		//print();
		//디렉션 초기화
		memset(dir, 0, sizeof(dir));
	}
	getAnswer(); //5번
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