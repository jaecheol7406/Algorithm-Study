#include <iostream>
#include <vector>
using namespace std;

struct Pos {
	int r;
	int c;
};

int R, C;
int map[15][15];
int island[15][15];
int visited[15][15];
vector<Pos> ones;

void Input() {
	scanf("%d %d\n", &R, &C);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf("%d ", &map[i][j]);
			if (map[i][j] == 1) {
				ones.push_back(Pos{ i, j });
			}
		}
	}
}

void Print() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			printf("%d ", island[i][j]);
		}
		cout << endl;
	}
}

int Width[10][20][2]; // [섬번호][행번호][0: 시작점 1:끝점], 특정 행에서 섬의 열번호를 기록한다
int Height[10][20][2];

int isCnt = 1;
int dir[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
void DFS(int thisR, int thisC) {

	visited[thisR][thisC] = 1;
	island[thisR][thisC] = isCnt;

	int tmpR, tmpC;
	for (int i = 0; i < 4; i++) {
		tmpR = thisR + dir[i][0];
		tmpC = thisC + dir[i][1];

		if (tmpR < 0 || R <= tmpR || tmpC < 0 || C <= tmpC) continue;
		if (map[tmpR][tmpC] == 1 && visited[tmpR][tmpC] == 0) {

			/*if (tmpC > Width[isCnt][thisR][1]) {
				Width[isCnt][thisR][1] = tmpC;
			}
			if (tmpC < Width[isCnt][thisR][0]) {
				Width[isCnt][thisR][0] = tmpC;
			}
			if (tmpR > Height[isCnt][thisC][1]) {
				Height[isCnt][thisC][1] = tmpR;
			}
			if (tmpR < Height[isCnt][thisC][0]) {
				Height[isCnt][thisC][0] = tmpR;
			}*/

			DFS(tmpR, tmpC);
			island[tmpR][tmpC] = isCnt;
			visited[tmpR][tmpC] = 1;
		}
	}
}

int PickMin(int dep, int des) { // 출발지, 도착지
	// 가로 탐색

	// 세로 탐색

	return 0;
}

vector<int> V;
int Selected[10];
void Pick(int cnt) {
	if (cnt >= isCnt - 1) { // 종료 조건
		cout << "순서: ";
		for (int i = 1; i < V.size(); i++) {
			cout << V[i-1] << "->" << V[i] << " ";
		}
		cout << endl;
	}

	for (int i = 1; i < isCnt; i++) {
		if (Selected[i] == 0) {
			Selected[i] = 1;
			V.push_back(i);
			
			Pick(cnt + 1);

			V.pop_back();
			Selected[i] = 0;
		}
	}
}

int main() {

	Input();

	for (int i = 0; i < ones.size(); i++) { // island 배열 만들기
		int thisR = ones[i].r;
		int thisC = ones[i].c;
		if (visited[thisR][thisC] == 0) {
			// 초기화
			/*Width[isCnt][thisR][0] = thisC;
			Width[isCnt][thisR][1] = thisC;
			Height[isCnt][thisC][0] = thisR;
			Height[isCnt][thisC][1] = thisR;*/

			DFS(thisR, thisC);
			isCnt++;
		}
	}

	Print();

	// 섬 id로 순열 뽑기
	Pick(0);
	

	return 0;
 }