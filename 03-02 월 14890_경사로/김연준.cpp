/*
BOJ 14890번: 경사로
문제 유형 : 시뮬레이션
문제 풀이 : 맵 저장 시, 입력 받은 배열의 행과 열을 바꿔서 board [N~2N]까지 저장해준다.
            [다음 칸의 높이가 작은 경우]
				--> 다음 칸부터 L길이만큼의 길이가 연속된지 확인
			[다음 칸의 높이가 큰 경우]
			   --> 반복문을 통해 연속된 길이를 카운트한 cnt변수가 L보다 크다면 경사로를 놓을 수 있다.
			[다음 칸의 높이가 같은 경우]
			   -->연속된 경우니까 카운팅한다.
*/
#include <iostream>
#include <algorithm>
using namespace std;
int N, L;
int board[200][105];
void Input() {
	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = N; i < N * 2; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = board[j][i - N];
		}

	}
}
bool Check_Runway(int x, int y) {
	int val = board[x][y + 1];
	for (int i = y + 2; i < y + L+1; i++) {
		if (y > N) {
			return false;
		}
		if (board[x][i] != val) {
			return false;
		}
	}
	return true;
}
void Solution() {
	int answer = 0;
	for (int i = 0; i < 2*N; i++) {
		bool flag = true;
		int cnt = 1;
		for (int j = 0; j < N-1; j++) {
			if (abs(board[i][j] - board[i][j + 1]) > 1) { //차이가 1보다 크면 연결 실패.
				flag = false;
				break;
			}
			if (board[i][j] == board[i][j + 1]) { //길이 같은 경우 카운팅
				cnt++;
				continue;
			}
			if (board[i][j + 1] > board[i][j]) {
				if (cnt >= L) {
					cnt = 1;
					//continue;
				}
				else {
					flag = false;
					break;
				}
			}
			else {
				if (Check_Runway(i, j)==true) {
					cnt = 0;
					j = j + L-1;
					continue;
					
				}
				else {
					flag = false;
					break;
				}

			}
		}
		if (flag == true) {
			//cout << "HI : " << i << endl;
			answer++;
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
	cout.tie(NULL);
	Solve();
	return 0;
}