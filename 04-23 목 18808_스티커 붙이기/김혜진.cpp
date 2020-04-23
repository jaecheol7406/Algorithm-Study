/*
예제는 pass, 제출시 틀렸습니다

1. 스티커별로 모든 출발점에서 가능성을 따진다
2. 0도에서 붙일 수 있는지 보고, 안 되면 90도 돌리는 식으로 270도까지 확인한다.
  (배열을 돌려서 확인하는 부분을 너무 어렵게 짜서 시간이 오래 걸림)
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
				/*cout << "sticker[" << n - 1 - i << "][" << j << "=" << sticker[n - 1 - i][j] << endl;
				cout << "map[" << r + i << "][" << c + j << "]=" << map[r + i][c + j] << endl;*/
				if (sticker[n-1-i][m-1-j] == 1 && map[r + i][c + j] == 1) return false;
				if (r + i < 0 || c + j < 0 || N <= r + i || M <= c + j) return false;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (sticker[n - 1 - i][m - 1 - j] == 1) map[r + i][c + j] = 1;
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

	// Print();
	int answer = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 1) answer++;
		}
	}

	cout << answer;
	return 0;
}