#include <iostream>
#include <vector>
using namespace std;

int R, C, T;
int map[1000][1000]; // 최대크기 계산 필요
int bojeong = 500;

struct Cell{
	int r;
	int c;
	int hpFix;
	int hpNow = 0;
};

vector<Cell> cellList;

void Init() {
	cellList.clear();
	for (int i = 0; i < R; i++) {
		memset(map[i], 0, sizeof(int) * C);
	}
}

void Input() {
	Init();

	scanf("%d %d %d\n", &R, &C, &T);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			int hpFix;
			scanf("%d ", &hpFix);
			if (hpFix != 0) {
				map[i + bojeong][j + bojeong] = hpFix;
				cellList.push_back(Cell{ i + bojeong, j + bojeong, hpFix, 0 });
			}
			
		}
	}
}

void Print() {
	/*for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}*/

	for (int i = 0; i < cellList.size(); i++) {
		Cell thisCell = cellList[i];
		printf("줄기세포 x:%d y:%d 생명력:%d 현재생명력:%d\n", thisCell.r - bojeong, thisCell.c - bojeong, thisCell.hpFix, thisCell.hpNow);
	}
}

int main() {
	int test_case;
	scanf("%d\n", &test_case);
	for (int t = 0; t < test_case; t++) {
		printf("%d ======================\n", t);
		Input();
		Print();

	}
	
	return 0;
}