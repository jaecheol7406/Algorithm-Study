/*
BOJ 17822번: 원판 돌리기
문제 유형 : 시뮬레이션

문제 풀이 : 1. 원판을 돌린다. (이때, 입력받은 x의 배수에 포함하는 원판 모두 돌려야함)
            2. 인접한 수가 있는지 찾는다.
			   -> 예외사항) 각 원판의 첫번째 값, 마지막 값,  첫번째 원판, 마지막 원판이 예외사항이므로 따로 처리한다.
			   ->인접한 수 라면 tmp배열(임시 저장 배열)에 0(지워진 값을 의미)을 저장, 아니라면 그 값 그대로 저장 (flag변수로 인접한 경우가 있는지 체크)
			   ->만약, 인접한 수가 아예 없는 경우라면 강제 형변환(소숫점이 있는 경우가 있으므로)을 통해 평균 값을 구한다.
			   ->recovery_map()함수에서 tmp배열에 있던 업데이트 된 원판을 기존 원판으로 덮어쓴다.
*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
struct command {
	int x; //원판 번호
	int d; // 방향(0이면 시계, 1이면 반시계)
	int k; // 몇칸 회전
};
int N, M, T;
int board[51][51];
int tmp[51][51];
vector<command>  command_list;
void Input() {
	cin >> N >> M >> T;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 0; i < T; i++) {
		command cmd;
		cin >> cmd.x >> cmd.d >> cmd.k;
		command_list.push_back(cmd);
	}
}
void rotate(int x,int d,int k) {
	for (int i = 0; i < k; i++) { //k번 돌림
		if (d == 0) { //시계방향
			int tmp = board[x][M - 1];
			for (int j = M - 1; j >= 1; j--) {
				board[x][j] = board[x][j - 1];
			}
			board[x][0] = tmp;
		}
		else { //반시계방향
			int tmp = board[x][0];
			for (int j = 0; j < M-1; j++) {
				board[x][j] = board[x][j + 1];
			}
			board[x][M - 1] = tmp;
		}
	}
}
void check_adj() { //인접한 수 찾기
	memset(tmp, 0, sizeof(tmp));
	bool flag = false;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == 0) { //0이면 지워진 값 이므로 인접한 수 찾기 안해도된다.
				tmp[i][j] = 0;
				continue;
			}
			if (j == 0) { //각 원판의 첫번째 값
				if (board[i][j] == board[i][M - 1] || board[i][j] == board[i][1]) { //두번째값과 마지막 값과 비교해야함
					tmp[i][j] = 0;
					flag = true;
					continue;
				}
			}
			else if (j == M - 1) { //각 원판의 마지막 값
				if (board[i][j] == board[i][0] || board[i][j] == board[i][M - 2]) { //첫번째값과 마지막 전 값과 비교해야함
					tmp[i][j] = 0;
					flag = true;
					continue;
				}
			}
			else {
				if (board[i][j] == board[i][j - 1] || board[i][j] == board[i][j + 1]) { //아니면 -1,+1값과 비교
					tmp[i][j] = 0;
					flag = true;
					continue;
				}
			}
			if (i == 1) { //첫번째 원판인 경우
				if (board[i][j] == board[i + 1][j]) { //두번쨰 원판의 인접한 수와 비교
					tmp[i][j] = 0;
					flag = true;
					continue;
				}
			}
			else if (i == N) {
				if (board[i][j] == board[i - 1][j]) { //마지막 원판인 경우 마지막 전 원판과의 인접한 수와 비교
					tmp[i][j] = 0;
					flag = true;
					continue;
				}
			}
			else {
				if (board[i][j] == board[i + 1][j] || board[i][j] == board[i - 1][j]) { //아니라면 전 원판, 다음 원판과 비교
					tmp[i][j] = 0;
					flag = true;
					continue;
				}
			}
			tmp[i][j] = board[i][j];
		}
	}
	int sum = 0;
	int cnt = 0;
	if (!flag) { //인접한 수가 없다면
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < M; j++) {
				if (tmp[i][j] == 0)
					continue;
				sum += tmp[i][j];
				cnt++;
			}
		}
		float avg = (float)sum / cnt; //평균값
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < M; j++) {
				if (tmp[i][j] == 0)
					continue;
				if (tmp[i][j] > avg)
					tmp[i][j]--;
				else if(tmp[i][j]<avg)
					tmp[i][j]++;
			}
		}
	}
}
void recovery_map() { //원판 업데이트
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			board[i][j] = tmp[i][j];
		}
	}
}
void Print() {
	int sum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			sum += board[i][j];
		}
	}
	cout << sum << endl;
}
void Solution() {
	for (int i = 0; i < command_list.size(); i++) {
		
		int x = command_list[i].x;
		int d = command_list[i].d;
		int k = command_list[i].k;
		for (int j = x; j <= N; j += x) {//x의 배수 원판 돌리고
			rotate(j, d, k);
		}
		check_adj(); //인접한 목록 확인하기
		recovery_map(); //원판 업데이트
	}
	Print();
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