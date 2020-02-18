#include <iostream>

using namespace std;
int N;
int T[16];
int P[16];
int result = 0;
void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> T[i];
		cin >> P[i];
	}

}

void DFS(int idx, int sum) {
	if (idx == N + 1) {
		if (result < sum)
			result = sum;
		return;
	}
	DFS(idx + 1, sum);
	if (idx + T[idx] <= N + 1) {
		DFS(idx + T[idx], sum + P[idx]);
	}
}
void Solution() {

	DFS(1, 0);
	cout << result << endl;
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
