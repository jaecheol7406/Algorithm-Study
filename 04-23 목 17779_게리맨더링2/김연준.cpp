/*
BOJ 17779번: 게리맨더링2
문제 유형 : 시뮬레이션
main() -> Solve() -> Input() -> Solution() -> divide() -> getBoundary()

1. 문제의 조건에 맞는 x,y,d1,d2 모든 경우의 수를 확인하여 정답을 도출한다.
2. 경계선을 구한다.
	(1) 1,4번 경계선은 (+1,-1)로 같은 규칙이고, 2,3번 경계선은 (+1,+1)로 같은 규칙이므로 같은 반복문 안에서 구한다.
3. 5번 선거구를 미리 정한다.
	(1) 경계선의 (x,y)와 (x+d1+d2,y-d1+d2) 두 점을 제외한 5번 선거구는 같은 규칙을 가짐.
	(2) 같은 행일때, 경계선과 만나는 지점부터 다시 만나는 지점까지가 5번 구역이므로 5번 선거구를 미리 정한다.
4. 전체 맵을 순회하면서, 5번구역이라면 5번 구역 인구수를 더하고, 아니라면 각 선거구 조건에 맞는 구역에 인구수를 더함.

*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int N;
int board[21][21];
int district[21][21];
int people_count[6];
int answer = 987654321;
void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}
}
void getBoundary(int x, int y, int d1, int d2) {
	for (int i = 0; i <= d1; i++) { //1,4번 경계
		district[x + i][y - i] = 5;
		district[x + d2 + i][y + d2 - i] = 5;
	}
	for (int i = 0; i <= d2; i++) { //2,3번 경계
		district[x + i][y + i] = 5;
		district[x + d1 + i][y - d1 + i] = 5;
	}
}
void divide(int x, int y, int d1, int d2) {
	//경계선 구하기.
	getBoundary(x,y,d1,d2);
	//5번 선거구 정하기
	for (int i = x + 1; i <= x + d1 + d2 - 1; i++) {
		bool flag = false;
		for (int j = y - d1; j <= y + d2; j++) {
			if (district[i][j] == 5 && !flag) {
				flag = true;
				continue;
			}
			else if (district[i][j] == 5 && flag)
				break;
			if (flag)
				district[i][j] = 5;
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (district[i][j] == 5)
				people_count[5] += board[i][j];
			else {
				if (i < x + d1 && j <= y)
					people_count[1] += board[i][j];
				else if (i <= x + d2 && y < j)
					people_count[2] += board[i][j];
				else if (x + d1 <= i && j < y - d1 + d2)
					people_count[3] += board[i][j];
				else if (x + d2 < i && y - d1 + d2 <= j)
					people_count[4] += board[i][j];
			}
		}
	}
	sort(people_count + 1, people_count + 6);
	answer = min(answer, people_count[5] - people_count[1]);
}
void Solution() {
	for (int x = 1; x <= N; x++) {
		for (int y = 2; y <= N; y++) {
			for (int d1 = 1; d1 <= N; d1++) {
				if (y-d1<1)
					break;
				for (int d2 = 1; y+d2 <= N; d2++) {
					if (x + d1 + d2 > N)
						break;
					memset(district, 0, sizeof(district));
					memset(people_count, 0, sizeof(people_count));
					divide(x, y, d1, d2);
				}
			}
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