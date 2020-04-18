/*
BOJ 1107 : 리모컨


Step1. 0~1000000 의 채널을 완전탐색한다.(N의 최대값이 500000이지만, 499999의 경우 9,8와 0이 고장났으면 477777에서 +버튼을 누르는 것(22222)보다 511111에서 -버튼을 누르는게(11111) 빠르기 때문
Step2. 각 채널에 대해서 해당 번호로 바로 이동 가능하다면 번호를 눌러서 이동한 횟수와, 100에서 +-를 눌러서 이동한 횟수를 비교하여 min값을 구한다.
Step3. 해당 채널에서 목표채널까지 차이를 Step2의 결과와 더한다.
Step4. 완전탐색을 하면서 최소값이 정답!!
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N, M;
vector<int> broken;
vector<int>::iterator iter;
const int INF = 987654321;
int result = INF;
void Input() {
	cin >> N >> M;
	int num;
	for (int i = 0; i < M; i++) {
		cin >> num;
		broken.push_back(num);
	}
}
int IsPossiblePress(int num) { 
	if (num == 0) {
		iter = find(broken.begin(), broken.end(), 0);
		if (iter == broken.end()) {
			return 1;
		}
		else {
			return -1;
		}
	}
	int cnt = 0;
	while (num != 0) {
		cnt++;
		iter = find(broken.begin(), broken.end(), num%10);
		if (iter != broken.end()) { //고장난 버튼이 이라면.
			return -1;
		}
		num /= 10;
	}
	return cnt;
}
int getChannel(int num) {
	int cnt = IsPossiblePress(num);
	if (cnt == -1) { //고장난 버튼이 포함되어있으므로 무조건 +-로만 가야함.
		return abs(num - 100);
	}
	else { //고장난 버튼이 포함되어있지않으므로 채널번호를 눌러서 가는것과 +-로 가는것을 비교.
		return min(cnt, abs(num - 100));
	}
}
void Solution() {
	for (int i = 0; i <= 1000000; i++) {
		int move = getChannel(i) + abs(i - N);
		if (result > move)
			result = move;
	}
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