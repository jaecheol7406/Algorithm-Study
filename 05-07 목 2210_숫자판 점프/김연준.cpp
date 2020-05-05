/*
BOJ 2210번: 숫자판 점프

숫자판의 숫자를 string으로 관리하여, DFS로 탐색하면서 string add한다.
숫자를 다 선택했으면, HashSet에 넣어서 중복 방지.
*/
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;
int arr[5][5];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
string str;
unordered_set<string> s;
void DFS(int x, int y, int cnt,string str) {
	if (cnt == 5) {
		s.insert(str);
		return;
	}
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5)
			continue;
		DFS(nx, ny, cnt + 1, str+to_string(arr[nx][ny]));
	}
}
int main() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			DFS(i, j, 0, to_string(arr[i][j]));
		}
	}
	cout << s.size() << endl;
}