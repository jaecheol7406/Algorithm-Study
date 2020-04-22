/*
function call: main -> (Input -> Start -> Check) -> main

1. 범위상으로 '시작점' '왼쪽 아래'와 '맨 아래' 점으로 삼을 수 있는 점들을 정한다
2. 각 점으로 가는 데 몇 번 가는 건지 구한다(rightN, leftN)
3. 각 점에서 rightN과 leftN 번으로 마름모를 그리며 이미 나온 디저트 수는 visited 에 표시한다.
4. 디저트 수가 끝까지 겹치지 않으면, (leftN + rightN)*2 만큼 디저트를 먹은 것이다. 이 수가 가장 큰 것을 출력한다

의문점
43번 줄에 써둠
*/
#include <iostream>
using namespace std;

int N;
int map[25][25];
int visited[120];
int visitedSupport[120];
int maxAnswer = 0;
int tmpAnswer = 0;

int tmpR1, tmpC1, tmpR2, tmpC2;

void Input() {
	maxAnswer = 0;

	scanf("%d\n", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
}

void Init() {
	for (int i = 1; i <= 100; i++) {
		visited[i] = 0;
	}
}

void Check(int r, int c, int rightN, int leftN) {
	Init();
	// visited[map[r][c]] = 1; 얘를 살리고 59줄을 leftN-1 까지로 하면 49개만 맞는다고 나오는데 이유를 모르겠음.

	for (int i = 0; i < rightN; i++) {
		r++;
		c--;

		if (visited[map[r][c]] == 1) return;
		visited[map[r][c]] = 1;
	}

	for (int i = 0; i < leftN; i++) {
		r++;
		c++;

		if (visited[map[r][c]] == 1) return;
		visited[map[r][c]] = 1;
	}

	for (int i = 0; i < rightN; i++) {
		r--;
		c++;

		if (visited[map[r][c]] == 1) return;
		visited[map[r][c]] = 1;
	}

	for (int i = 0; i < leftN; i++) {
		r--;
		c--;

		if (visited[map[r][c]] == 1) return;
		visited[map[r][c]] = 1;
	}
	
	tmpAnswer = (rightN + leftN) * 2;
	// cout << tmpAnswer << endl;
	if (tmpAnswer > maxAnswer) maxAnswer = tmpAnswer;
}

void Start(int r, int c) {
	// cout << "시작점: " << r << "," << c << endl;
	tmpR1 = r;
	tmpC1 = c;

	while (1) {
		
		visited[map[r][c]] = 1;

		// 왼쪽 아래로 가면서 점1을 정한다
		tmpR1++;
		tmpC1--;

		if (tmpR1 > N - 2 || tmpC1 < 0) break;
		
		// cout << " 왼쪽점: " << tmpR1 << "," << tmpC1 << endl;

		// 오른쪽 아래로 가면서 점2를 정한다
		tmpR2 = tmpR1;
		tmpC2 = tmpC1;

		while (1) {
			tmpR2++;
			tmpC2++;

			if (tmpR2 > N - 1 || tmpC2 > N - 2) break;
			// cout << "  아래쪽점: " << tmpR2 << "," << tmpC2 << endl;

			Check(r, c, (tmpR1 - r), (tmpR2 - tmpR1));

		}
	}
	
}

int main() {

	int T;
	scanf("%d\n", &T);

	for (int t = 1; t <= T; t++) {
		Input();

		for (int i = 0; i < N - 2; i++) {
			for (int j = 1; j < N - 1; j++) {
				Start(i, j);
			}
		}

		if (maxAnswer == 0) cout << "#" << t << " " << -1 << endl;
		else cout << "#" << t << " " << maxAnswer << endl;
	}

	

	return 0;
}