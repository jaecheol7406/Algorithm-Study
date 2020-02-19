#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
int T, N, K,answer;
string number[30];
vector<string> result;
queue<string> rot;
void Initialize() {
	//memset(number, 0, sizeof(number));  --> visual studio 상에서는 가능하지만 swea에서 런타임에러 일으킴
	for (int i = 0; i < N; i++) {
		number[i] = "";
	}
	
	result.clear();
	answer = 0;
}
void Input() {
	cin >> N >> K;
	string input;
	cin >> input;
	for (int i = 0; i < N; i++) {
		number[i] = input[i];
	}
}
void rotate() {

	for (int i = 0; i < N; i++) {
		rot.push(number[i]);
	}
	for (int i = 1; i < N; i++) {
		number[i] = (string)rot.front();
		rot.pop();
	}
	number[0] = (string)rot.front();
	rot.pop();


}
bool cmp(string a, string b) {
	return a > b;

}
int Change_Num(char str) {
	if (str == 'A') return 10;
	else if (str == 'B') return 11;
	else if (str == 'C') return 12;
	else if (str == 'D') return 13;
	else if (str == 'E') return 14;
	else if (str == 'F') return 15;
	else return str - '0';
}
void Solution() {
	for (int i = 0; i < N / 4; i++) { //회전 수
		for (int j = 0; j < 4; j++) { //각 변
			//int val = 0;
			//int cnt = 0;
			string val = "";
			for (int k = 0; k < N/4; k++) { //그 변의 숫자
				val.append(number[j*N / 4 + k]);
			}
			auto it = find(result.begin(), result.end(), val);

			if (it == result.end()) {
				result.push_back(val);
			}

		}
		rotate();
	}
	sort(result.begin(), result.end(),cmp);
	string tmp = result[K - 1];
	int cnt = 0;
	for (int i = tmp.size() - 1; i >= 0; i--) {
		
		answer += Change_Num(tmp[i])*pow(16, cnt++);
	}
}
void Solve() {
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Initialize();
		Input();
		Solution();
		cout << "#" << i << " " << answer << endl;
	}
}
int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}