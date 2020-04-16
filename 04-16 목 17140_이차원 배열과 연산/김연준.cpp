/*
BOJ 17140번: 이차원 배열과 연산


1. R연산
	(1)배열의 각 행에 대하여 숫자와 등장 횟수를 vector<pair<int,int>>에 저장한다.
	(2)행을 반복하면서 열의 최대 사이즈를 갱신.
	(3)각 행들을 문제의 조건에 따라 정렬하고, 이중벡터에 저장하여 기존의 맵에 덮어 쓸 데이터를 만든다.
	(4)이중벡터를 기존의 맵에 복사할 때, 열의 사이즈가 맥스보다 작으면 0을 채운다.

2. C연산은 위의 R연산에서  행->열 , 열->행으로 바꿔서 수행
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int arr[100][100];
int row_len = 3, col_len = 3;
int R, C, K;
int answer = -1;
void Input() {
	cin >> R >> C >> K;
	int input;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> arr[i][j];
		}
	}
}
bool cmp(pair<int,int>& a, pair<int,int>& b) {
	if (a.second == b.second) {
		return a.first < b.first;
	}
	return a.second < b.second;
}
void rCalc() {
	vector<vector<pair<int,int>>> arr_list;
	int max_col = 0;
	for (int i = 0; i < row_len; i++) {
		vector<pair<int,int>> list;
		for (int j = 0; j < col_len; j++) {
			if (arr[i][j] == 0)
				continue;
			bool flag = false;
			for (int k = 0; k < list.size(); k++) {
				if (list[k].first == arr[i][j]) {
					flag = true;
					list[k].second++;
					break;
				}
			}
			if (!flag) {
				list.push_back({ arr[i][j],1 });
			}
		}
		sort(list.begin(), list.end(), cmp);
		arr_list.push_back(list);
		max_col = max(max_col, (int)list.size());
	}
	if (max_col > 50)
		max_col = 50;
	for (int i = 0; i < arr_list.size(); i++) {
		for (int j = 0; j < arr_list[i].size(); j++) {
			arr[i][j * 2] = arr_list[i][j].first;
			arr[i][j * 2 + 1] = arr_list[i][j].second;
		}
		for (int j = arr_list[i].size() * 2; j < max_col * 2; j++) {
			arr[i][j] = 0;
		}
	}
	col_len = max_col * 2;
}
void cCalc() {
	vector<vector<pair<int, int>>> arr_list;
	int max_row = 0;
	for (int i = 0; i < col_len; i++) {
		vector<pair<int, int>> list;
		for (int j = 0; j < row_len; j++) {
			if (arr[j][i] == 0)
				continue;
			bool flag = false;
			for (int k = 0; k < list.size(); k++) {
				if (list[k].first == arr[j][i]) {
					flag = true;
					list[k].second++;
					break;
				}
			}
			if (!flag) {
				list.push_back({ arr[j][i],1 });
			}
		}
		sort(list.begin(), list.end(), cmp);
		arr_list.push_back(list);
		max_row = max(max_row, (int)list.size());
	}
	if (max_row > 50)
		max_row = 50;
	for (int i = 0; i < arr_list.size(); i++) {
		for (int j = 0; j < arr_list[i].size(); j++) {
			arr[j * 2][i] = arr_list[i][j].first;
			arr[j * 2 + 1][i] = arr_list[i][j].second;
		}
		for (int j = arr_list[i].size() * 2; j < max_row * 2; j++) {
			arr[j][i] = 0;
		}
	}
	row_len = max_row * 2;
}
void Solution() {
	int time = 0;
	while (time <= 100) {
		if (arr[R-1][C-1] == K) {
			answer = time;
			break;
		}
		if (row_len >= col_len) {
			rCalc();
		}
		else {
			cCalc();
		}

		time++;
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
