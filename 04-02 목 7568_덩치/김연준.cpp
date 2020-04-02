/*
BOJ 7568번: 덩치
문제 유형 : 브루트포스
문제 풀이 : N의 최대값이 50이므로 O(N^2)에 충분히 풀이 가능해서
			2중 반복문으로 키와 몸무게를 모두 비교한다.

FunctionCall : main()->Solve()->Input()->Solution();
*/
#include <iostream>
#include <vector>
using namespace std;
int N;
vector<pair<int, int>> info;
void Input() {
	cin >> N;
	int x, y;
	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		info.push_back(make_pair(x, y));
	}
}
void Solution() {
	int cnt;
	for (int i = 0; i < info.size(); i++) {
		cnt = 0;
		for (int j = 0; j < info.size(); j++) {
			if (i == j)
				continue;
			if ((info[i].first  < info[j].first) && (info[i].second < info[j].second))
				cnt++;
		}
		cout << cnt + 1 << " ";
	}
	
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