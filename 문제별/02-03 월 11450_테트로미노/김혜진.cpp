#include <iostream>
using namespace std;

int N, M;
int map[550][550];
int MAX;

void Input() {
	scanf("%d %d\n", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}

bool AreaTest(int rtmp, int ctmp) {
	return (rtmp < 0 || N <= rtmp || ctmp < 0 || M <= ctmp);
}

int HorizontalBar(int r, int c, int num) {
	int sum = 0;
	for (int i = c; i < c + num; i++) { // 가로막대기 탐색
		if (i < 0 || M <= i) {
			sum = 0;
			break;
		}
		sum += map[r][i];
	}
	return sum;
}

int VerticalBar(int r, int c, int num) {
	int sum = 0;
	for (int i = r; i < r + num; i++) { // 세로막대기 탐색
		if (i < 0 || N <= i) {
			sum = 0;
			break;
		}
		sum += map[i][c];
	}
	return sum;
}

void TypeOne(int r, int c) {
	int sum = HorizontalBar(r, c, 4);
	if (MAX < sum) MAX = sum;

	sum = VerticalBar(r, c, 4);
	if (MAX < sum) MAX = sum;
}

int dirTwo[3][2] = { {1, 0}, {0, 1}, {1, 1} };
void TypeTwo(int r, int c) {
	int sum = map[r][c];
	int rtmp, ctmp;
	for (int i = 0; i < 3; i++) {
		rtmp = r + dirTwo[i][0];
		ctmp = c + dirTwo[i][1];

		if (AreaTest(rtmp, ctmp)) {
			sum = 0;
			break;
		}
		sum += map[rtmp][ctmp];
	}
	if (MAX < sum) MAX = sum;
}

int dirThreeHor[4][2] = { {-1, 0}, {1, 0}, {-1, 2}, {1, 2} };
int dirThreeVer[4][2] = { {0, -1}, {0, 1}, {2, -1}, {2, 1} };
void TypeThree(int r, int c) {
	int sum = 0;
	int rtmp, ctmp;

	sum = VerticalBar(r, c, 3); // 세로줄기
	if (sum != 0) {
		for (int i = 0; i < 4; i++) {
			rtmp = r + dirThreeVer[i][0];
			ctmp = c + dirThreeVer[i][1];

			if (AreaTest(rtmp, ctmp)) continue;
			int tmp = sum + map[rtmp][ctmp];
			if (MAX < tmp) MAX = tmp;
		}
	}

	sum = HorizontalBar(r, c, 3); // 가로줄기
	if (sum != 0) {
		for (int i = 0; i < 4; i++) {
			rtmp = r + dirThreeHor[i][0];
			ctmp = c + dirThreeHor[i][1];

			if (AreaTest(rtmp, ctmp)) continue;
			int tmp = sum + map[rtmp][ctmp];
			if (MAX < tmp) MAX = tmp;
		}
	}
}

int dirFourVer[4][2] = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
int dirFourHor[4][2] = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
void TypeFour(int r, int c) {
	int sum = 0;
	int rtmp, ctmp;

	// 세로방향
	sum = VerticalBar(r, c, 2);
	if (sum != 0) {
		for (int i = 0; i < 4; i++) {
			// 새롭게 더해질 부분의 시작점
			rtmp = r + dirFourVer[i][0];
			ctmp = c + dirFourVer[i][1];

			if (AreaTest(rtmp, ctmp)) continue;
			int tail = VerticalBar(rtmp, ctmp, 2);
			// if (tail == 0) continue;
			int tmp = sum + tail;
			if (MAX < tmp) MAX = tmp;
		}
	}

	// 가로방향
	sum = HorizontalBar(r, c, 2);
	if (sum != 0) {
		for (int i = 0; i < 4; i++) {
			rtmp = r + dirFourHor[i][0];
			ctmp = c + dirFourHor[i][1];

			if (AreaTest(rtmp, ctmp)) continue;
			int tail = HorizontalBar(rtmp, ctmp, 2);
			// if (tail == 0) continue;
			int tmp = sum + tail;
			if (MAX < tmp) MAX = tmp;
		}
	}
}

int dirFiveVer[2][2] = { {1, -1}, {1, 1} };
int dirFiveHor[2][2] = { {-1, 1}, {1, 1} };
void TypeFive(int r, int c) {
	int sum = 0;
	int rtmp, ctmp;

	// 세로방향
	sum = VerticalBar(r, c, 3);
	if (sum != 0) {
		for (int i = 0; i < 2; i++) {
			rtmp = r + dirFiveVer[i][0];
			ctmp = c + dirFiveVer[i][1];

			if (AreaTest(rtmp, ctmp)) continue;
			int tmp = sum + map[rtmp][ctmp];
			if (MAX < tmp) MAX = tmp;
		}
	}

	// 가로방향
	sum = HorizontalBar(r, c, 3);
	if (sum != 0) {
		for (int i = 0; i < 2; i++) {
			rtmp = r + dirFiveHor[i][0];
			ctmp = c + dirFiveHor[i][1];

			if (AreaTest(rtmp, ctmp)) continue;
			int tmp = sum + map[rtmp][ctmp];
			if (MAX < tmp) MAX = tmp;
		}
	}
}

void StartAt(int r, int c) {
	
	// 1번 유형에 대해 구하기
	TypeOne(r, c);
	TypeTwo(r, c);
	TypeThree(r, c);
	TypeFour(r, c);
	TypeFive(r, c);
}

int main() {

	Input();
	
	// StartAt(0, 0);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			StartAt(i, j);
		}
	}
	cout << MAX << endl;

	return 0;
}