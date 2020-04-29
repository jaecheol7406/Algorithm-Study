/*
틀린코드
사다리 1개로 되나 확인해보고, 안되면 2개, 또 안되면 3개를 해야되는데
아래 코드는 (1, 1)에 사다리를 설치하고 이게 답이 아니면 그 상태에서 하나를 추가해 2개를 설치
그 다음에 답을 체크해서 맞게되면 리턴하는데, 만약 더 아래에 사다리 1개짜리로 만들수있는것이 있을수도있는데 그건 탐색이 되지않은채로 2를 리턴하기 때문에 오답
*/
#include <iostream>
#include <vector>
using namespace std;

int N, M, H;
int map[35][15];

void Input() {
	scanf("%d %d %d", &N, &M, &H);
	int a, b;
	for (int i = 0; i < M; i++) {
		scanf("%d %d\n", &a, &b);
		map[a][b] = 1;
	}
}

void Print() {
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

bool Test() {
	for (int j = 1; j <= N; j++) { // j열에서 출발
		int pos = j; // 현재 몇열에 있는지
		for (int i = 1; i <= H; i++) {
			if (pos+1 <= N && map[i][pos] == 1) {
				pos++;
			}
			else if (pos - 1 >= 1 && map[i][pos - 1] == 1) {
				pos--;
			}
		}
		if (pos != j) return false;
	}
	return true;
}

int main() {

	Input();
	// Print();

	if (Test()) {
		cout << 0;
		return 0;
	}

	for (int j1 = 1; j1 < N; j1++) { // 몇 번째 열에 놓을 것인가 (j ~ j+1)
		for (int i1 = 1; i1 <= H; i1++) { // 몇 번에 행에 놓을 것인가
			if (map[i1][j1] == 1) continue;

			map[i1][j1] = 1;
			// cout << "test: (" << i1 << "," << j1 << ")" << endl;
			// Print();

			if (Test()) {
				cout << 1;
				return 0;
			}

			// 2번째거 골라본다
			for (int j2 = 1; j2 < N; j2++) {
				for (int i2 = 1; i2 <= H; i2++) {
					if (j1 == j2 && i1 == i2) continue;
					if (map[i2][j2] == 1) continue;

					map[i2][j2] = 1;
					// cout << "test: (" << i1 << "," << j1 << ") & (" << i2 << "," << j2 << ")" << endl;
					// Print();
					if (Test()) {
						cout << 2;
						return 0;
					}

					// 3번째거 골라본다
					for (int j3 = 1; j3 < N; j3++) {
						for (int i3 = 1; i3 <= H; i3++) {
							if (j1 == j3 && i1 == i3) continue;
							if (j2 == j3 && i2 == i3) continue;
							if (map[i3][j3] == 1) continue;

							map[i3][j3] = 1;
							// cout << "test: (" << i1 << "," << j1 << ") & (" << i2 << "," << j2 << ") & (" << i3 << "," << j3 << ")" << endl;
							// Print();
							if (Test()) {
								cout << 3;
								return 0;
							}
							map[i3][j3] = 0;
						}
					}
					map[i2][j2] = 0;
				}
			}

			map[i1][j1] = 0;
		}
	}

	cout << -1;

	return 0;
}