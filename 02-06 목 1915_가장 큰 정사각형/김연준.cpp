#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M;
int result = 0;
int board[1002][1002];
int dp[1002][1002];
int min_val(int a, int b, int c) {
	return a > b ? (b > c ? c : b) : (a > c ? c : a);
}
void Input() {

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		string temp;
		cin >> temp;
		for (int j = 1; j <= M; j++) {
			board[i][j] = temp[j-1] - '0';
		}
	}

}
//처음 푼 방법 -> 시간 초과
/*void Solution() { 
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == 1) {
				int n = 0;
				while (true) {
					n++;
					bool flag = false;
					for (int k = i; k<i+n; k++) {
						for (int l = j; l < j + n; l++) {
							if (board[k][l] == 0 || k >= N || l >= N) {
								flag = true;
								break;
							}
						}
						if (flag)
							break;
					}
					if (flag)
						break;
					else {
						if (result < n)
							result = n;
					}
				}
			}
		}
	}
}*/

//인터넷에서 DP 풀이법 본 후 
//Solve
void Solution2() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (board[i][j] == 1) {
				dp[i][j] = min_val(dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]) + 1;
				result = max(dp[i][j], result);
				
			}
			
		}
	}
}
void Solve() {
	Input();
	memset(dp, 0, sizeof(dp));
	Solution2();
	cout << result * result << endl;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}