#include <iostream>
#include <vector>
using namespace std;

int N;
int map[25][25];

int num = 0;
void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
	num = -1;
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}

void StartAt(int x, int y);
int LengthIs(int x, int y, int d1, int d2);


int main() {

	int T;
	cin >> T;
	for (int t_case = 1; t_case <= T; t_case++) {
		printf("#%d ", t_case);

		Input();

		for (int i = 0; i < N - 1; i++) {
			for (int j = 1; j < N - 1; j++) {
				StartAt(i, j);
			}
		}
		printf("%d\n", num);

	}

	return 0;
}

void StartAt(int x, int y) {
	int tmp;
	for (int d1 = 1; d1 <= (N - 1) - y; d1++) {
		if (x + d1 > N - 2) continue;

		for (int d2 = 1; d2 <= (N - 1) - x - d1; d2++) {
			
			if (y + d1 - d2 < 0) continue;

			tmp = LengthIs(x, y, d1, d2);
			if (tmp == 1 && num < (d1+d2)*2 ) {
				num = (d1 + d2)*2;
			}
				
		}
	}
}

int dir[4][2] = { {1, 1}, {1, -1}, {-1, -1}, {-1, 1} };
int LengthIs(int x, int y, int d1, int d2) {

	int thisx = x; int thisy = y;
	int visited[110] = { 0, };
	int num[4] = {d1, d2, d1, d2-1};

	visited[map[thisx][thisy]] = 1;

	for (int d = 0; d < 4; d++) {
		for (int t = 0; t < num[d]; t++) {
			thisx += dir[d][0];
			thisy += dir[d][1];

			if (thisx < 0 || N <= thisx || thisy < 0 || N <= thisy || visited[map[thisx][thisy]] == 1) return 0;

			visited[map[thisx][thisy]] = 1;
		}
	}

	return 1;
}