//#include <iostream>
//#include <algorithm>
//using namespace std;
//
//int board[10][10];
//int paper[5] = { 5,5,5,5,5 };
//const int INF = 987654321;
//int res = INF;
//void Input() {
//	for (int i = 0; i < 10; i++) {
//		for (int j = 0; j < 10; j++) {
//			cin >> board[i][j];
//		}
//	}
//
//}
//bool IsRange(int x,int y) {
//	return x >= 0 && x <= 10 && y >= 0 && y <= 10;
//}
//void DFS(int x,int y, int cnt) {
//	//종료 조건 명시
//	if (y == 10) {
//		DFS(x + 1, 0, cnt);
//		return;
//	}
//	if (x == 10) {
//		res = min(res, cnt);
//		return;
//	}
//	if (board[x][y] == 0) {
//		DFS(x, y + 1, cnt);
//		return;
//	}
//	int n = 0;
//	while ((++n) <= 5) {
//		if (!IsRange(x + n, y + n))
//			continue;
//		if (paper[n - 1] == 0)
//			continue;
//		bool check = false;
//		for (int i = x; i < x + n; i++) {
//			for (int j = y; j < y + n; j++) {
//				if (board[i][j] == 0) {
//					check = true;
//					break;
//				}
//			}
//			if (check)
//				break;
//		}
//		if (check)
//			continue;
//		for (int i = x; i < x + n; i++) {
//			for (int j = y; j < y + n; j++) {
//				board[i][j] = 0;
//			}
//		}
//		cnt++;
//		paper[n - 1]--;
//		DFS(x, y + n, cnt);
//		cnt--;
//		paper[n - 1]++;
//		for (int i = x; i < x + n; i++) {
//			for (int j = y; j < y + n; j++) {
//				board[i][j] = 1;
//			}
//		}
//	}
//}
//void Solve() {
//	Input();
//	DFS(0,0,0);
//	if (res == INF)
//		cout << "-1" << endl;
//	else
//		cout << res << endl;
//}
//int main() {
//	ios::sync_with_stdio(false);
//	cin.tie(NULL);
//	cout.tie(NULL);
//	Solve();
//
//	return 0;
//}