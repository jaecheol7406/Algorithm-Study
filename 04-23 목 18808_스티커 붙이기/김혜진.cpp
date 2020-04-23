/*
예제 7 오답
6 8 3
4 5
0 0 1 1 1
1 1 1 0 1
0 0 1 0 1
0 0 1 0 0
5 4
0 0 1 0
1 1 1 1
1 1 0 1
1 1 0 0
1 1 0 0
5 6
0 0 1 1 1 1
1 1 1 1 0 0
1 1 1 1 1 0
0 1 0 1 0 0
0 1 0 1 0 0
답: 22
출력: 10
*/
#include <iostream>
using namespace std;

int N, M, K;
int map[50][50];

int sticker[15][15];
int tmpSticker[15][15];
int n, m;

bool Tilt(int r, int c, int gakdo) {
	// cout << "Tilt(" << r << "," << c << "," << gakdo << ")" << endl;
	// cout << "각도: " << gakdo << endl;
	bool success = true;

	if (gakdo == 0) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (sticker[i][j] == 1 && map[r + i][c + j] == 1) return false;
				if (r + i < 0 || c + j < 0 || N <= r + i || M <= c + j) return false;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if(sticker[i][j] == 1)
					map[r + i][c + j] = 1;
			}
		}
		return true;
	}

	else if (gakdo == 90) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				// tmpSticker[i][j] = sticker[n - 1 - j][i];
				if (sticker[n-1-j][i] == 1 && map[r + i][c + j] == 1) return false;
				if (r + i < 0 || c + j < 0 || N <= r + i || M <= c + j) return false;
			}
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (sticker[n - 1 - j][i] == 1) map[r + i][c + j] = 1;
			}
		}
		return true;

		/*for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout << tmpSticker[i][j] << " ";
			}
			cout << endl;
		}*/
	}
	else if (gakdo == 180) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				// tmpSticker[i][j] = sticker[(n - 1) - i][j];
				if (sticker[(n - 1) - i][j] == 1 && map[r + i][c + j] == 1) return false;
				if (r + i < 0 || c + j < 0 || N <= r + i || M <= c + j) return false;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (sticker[n - 1 - i][j] == 1) map[r + i][c + j] = 1;
			}
		}

		/*for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << tmpSticker[i][j] << " ";
			}
			cout << endl;
		}*/
	}
	else if (gakdo == 270) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				// tmpSticker[i][j] = sticker[j][m-1-i];
				if (sticker[j][m-1-i] == 1 && map[r + i][c + j] == 1) return false;
				if (r + i < 0 || c + j < 0 || N <= r + i || M <= c + j) return false;
			}
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (sticker[j][m - 1 - i] == 1) map[r + i][c + j] = 1;
			}
		}
		return true;
		/*for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout << tmpSticker[i][j] << " ";
			}
			cout << endl;
		}*/
	}

	// 못 붙이면 그냥 버린다
	return false;
}

bool PasteAt(int r, int c) {
	bool success = false;

	for (int i = 0; i < 360; i += 90) {
		success = Tilt(r, c, i);
		// cout << i << "도 결과: " << success << endl;
		if (success) return true;
	}
	return false;
}



void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}

bool Select() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			// cout << "시작점: " << i << "," << j << endl;
			// 주의점: 1이 아니어야 시작하면 안된다
			if (PasteAt(i, j)) return true; // 붙이는 데 성공
		}
	}
	// cout << "못 붙여서 그냥 버림" << endl;
	return false; // 못 붙여서 그냥 버림
}

int main() {

	scanf("%d %d %d\n", &N, &M, &K);

	for (int input = 0; input < K; input++) {
		// 이번에 붙일 스티커 정보
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d ", &sticker[i][j]);
			}
		}

		/*cout << "=======" << endl;
		cout << "이번 스티커" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << sticker[i][j] << " ";
			}
			cout << endl;
		}
		cout << "=========" << endl;*/

		Select();

		// Print();
	}

	Print();
	int answer = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 1) answer++;
		}
	}

	cout << answer;
	return 0;
}