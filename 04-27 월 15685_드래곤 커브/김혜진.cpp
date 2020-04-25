#include <iostream>
using namespace std;

int N;
int c, r, d, g; // 시작열, 시작행, 시작방향, 세대
int map[120][120];
int visited[120][120];

int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
int dragonDir[4][2] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };

int oR;
int oC;

int answer = 0;

void Print() {
	for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 100; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

void Init() {
	for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 100; j++) {
			visited[i][j] = 0;
		}
	}
}

void NextGen(int n) { // 전 세대 드래곤커브가 끝난 점 & i만 따라하도록
	Init();
	// cout << "이번 세대 드래곤커브 시작점: " << oR << "," << oC << endl;

	int bR, bC; // 되짚어가고 있는 점
	int tmpR, tmpC; // 되짚어가는 중 tmp

	bool exist = false;

	visited[oR][oC] = 1;

	// 되짚어갈 최초 위치 설정
	bR = oR;
	bC = oC;

	while (1) {
		exist = false;

		for (int i = 0; i < 4; i++) {
			tmpR = bR + dir[i][0];
			tmpC = bC + dir[i][1];
			if (visited[tmpR][tmpC] == 1) continue;

			// cout << tmpR << "," << tmpC << "는 이전에 그린 점인가? (" << i << ")" << endl;

			if (map[tmpR][tmpC] == n) { // 이전에 그린 점을 찾아냄
				// cout << "yes" << endl;
				exist = true;
				// 되짚어가는 점 갱신
				bR = tmpR;
				bC = tmpC;
				visited[bR][bC] = 1;

				oR += dragonDir[i][0];
				oC += dragonDir[i][1];

				map[oR][oC] = n;
				// cout << oR << "," << oC << "를 새로 색칠" << endl;
				visited[oR][oC] = 1;
				break; // 방향 탐색 끝
			}

		}
		// 이전에 그린 드래곤커브가 없음
		if (!exist) {
			return;
		}
	}
}

int squareDir[4][2] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
void GetSquare(int r, int c) {
	cout << "getSquare(" << r << "," << c << ")" << endl;
	int tmpR, tmpC;
	for (int d = 0; d < 4; d++) {
		tmpR = r + squareDir[d][0];
		tmpC = c + squareDir[d][1];

		if (tmpR < 0 || 100 < tmpR || tmpC < 0 || 100 < tmpC) return;
		if (map[tmpR][tmpC] == 0) return;
	}
	cout << r << ", " << c << "에서 answer++" << endl;
	answer++;
}

int main() {

	scanf("%d\n", &N);
	for (int i = 1; i <= N; i++) {
		cout << i << "번 드래곤커브" << endl;
		scanf("%d %d %d %d\n", &c, &r, &d, &g);
		r++;
		c++;

		// 0세대 그리기
		oR = r + dir[d][0];
		oC = c + dir[d][1];

		map[r][c] = i; // i번째 드래곤 커브는 i로 적는다
		map[oR][oC] = i;

		for (int j = 0; j < g; j++) {
			NextGen(i);
		}

		
	}
	Print();
	// 4개 원소가 들어가는 정사각형
	int tmpI, tmpJ;

	
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if(map[i][j] != 0)
				GetSquare(i, j);
		}
	}

	cout << answer;

	return 0;
}