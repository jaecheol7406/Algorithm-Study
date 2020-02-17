#include <iostream>

using namespace std;
int N;
int result = 0;
void Input() {
	cin >> N;
}
void Solution() {	
	for (int i = 1; i < N; i++) {
		int sum = i;
		int tmp = i;
		while (tmp != 0) {
			sum += tmp % 10;
			tmp = tmp / 10;
		}
		if (sum == N) {
			result = i;
			return;
		}
	}
}
void Solve() {
	Input();
	Solution();
	cout << result << endl;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}