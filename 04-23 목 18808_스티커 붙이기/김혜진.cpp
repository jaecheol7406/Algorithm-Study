/*
function call: main -> (Select -> PasteAt -> Tilt) -> main

- 스티커별로 모든 출발점에서 0도에서의 가능성을 따진다
- 안 되면 모든 출발점에서 90도에서의 가능성을 따진다.. 식으로 270도까지
- 도중에 붙으면 그 다음 스티커로 넘어간다. 안 붙으면 그냥 버린다.

주의점
1. 스티커 돌리는 것을 너무 어렵게 구현해서 시간이 오래걸림
2. 0,0에서 0, 90, 180, 270도를 확인하는 게 아니라 90도에서 모든 점을 확인하고 안 되면 돌리는 것임
3. Select에서 시작점을 고를 때는 값이 0인 좌표가 아니라 모든 좌표에서 시작해보아야 함
(스티커 영역에는 해당되는데 붙일 필요는 없는 점이 있기 때문에)
*/
#include <iostream>
using namespace std;

int N, M, K;
int map[50][50];

int sticker[15][15];
int tmpSticker[15][15];
int n, m;

bool Tilt(int r, int c, int gakdo) {
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
	}
	else if (gakdo == 180) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (sticker[n-1-i][m-1-j] == 1 && map[r + i][c + j] == 1) return false;
				if (r + i < 0 || c + j < 0 || N <= r + i || M <= c + j) return false;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (sticker[n - 1 - i][m - 1 - j] == 1) map[r + i][c + j] = 1;
			}
		}
		return true;
	}
	else if (gakdo == 270) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
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
	}

	// 못 붙이면 그냥 버린다
	return false;
}

bool PasteAt(int r, int c, int gakdo) {
	bool success = false;

	success = Tilt(r, c, gakdo);
	
	if (success) return true;

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
	for (int t = 0; t < 360; t += 90) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				// 주의점: 1이 아니어야 시작하면 안된다
				if (PasteAt(i, j, t)) return true; // 붙이는 데 성공
			}
		}
	}
	
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

		Select();
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