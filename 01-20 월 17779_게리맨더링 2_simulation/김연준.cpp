#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int N;
int A[21][21];
int B[21][21];
int peoples[5];
const int INF = 987654321;
int answer = INF;
void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
		}
	}
}
/*int getOneWard(int r, int c, int d1, int d2) {
	for(int i=1; i<=)

}*/
void Solution() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if ((i == 1 && j == 1) || (i == 1 && j == N) || (i == N && j == 1) || (i == N && j == N)) //맵의 각 모서리는 대각선 형성 불가능
				continue;
			for (int k = 1; k <= N; k++) {
				if ((i + k > N) || (j - k < 1)) //x+d1>N , y -d1<1
					continue;
				for (int l = 1; l <= N; l++) {
					if (j + l > N) //y+d2<=N
						continue;
					if (k + l > N-i)    //d1+d2<=N
						continue;
					//여기서 살아남은 d1,d2로 돌려야함
					memset(peoples, 0, sizeof(peoples)); //각 케이스마다 Initialize
					memset(B, 0, sizeof(B));
					//대각선구하기
					for (int r = 0; r <= k; r++) { //1,4번 조건 대각선
						B[i + r][j - r] = 5;
						B[i + l + r][j + l - r] = 5;

					}
					for (int r = 0; r <= l; r++) { //2,3번 조건 대각선
						B[i + r][j + r] = 5;
						B[i + k + r][j - k + r] = 5;
					}


					//1~5번구역 정하기
					for (int r = 1; r <= N; r++) {
						for (int c = 1; c <= N; c++) {
							if (B[r][c] == 5) { //5번 대각선 경계선 진입
								peoples[4] += A[r][c];
								if ((r == i && c == j) || (r == i + k + l && c == j - k + l)) {
									continue;
								}
								while (c != N && (B[r][++c] != 5)) { //그 다음 5번 경계선 만날떄 까지는 5번 구역.

									peoples[4] += A[r][c];
									B[r][c] = 5;
								}

								peoples[4] += A[r][c]; //오른쪽 대각선 경계선 계산
							}
							
							else {
								if (r < i + k && c <= j) { //1번구역
	
									peoples[0] += A[r][c];
								}
								else if (r <= i + l && c > j) { //2번구역

									peoples[1] += A[r][c];
								}
								else if (i + k <= r && c < j - k + l) { //3번구역

									peoples[2] += A[r][c];
								}
								else if (i + l < r && j - k + l <= c) { //4번구역

									peoples[3] += A[r][c];
								}
							}
						}
					}
					sort(peoples, peoples+5);
					if (answer > peoples[4] - peoples[0]) {
						answer = peoples[4] - peoples[0];
					}
					
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