// Input을 잘 못 받아오고 있음

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int R, C, T;
int map[1000][1000]; // 원래 있냐 없냐에 필요
int newMap[1000][1000]; // 최대크기 계산 필요
int bojeong = 500;

struct Cell {
	int r;
	int c;
	int hpFix;
	int hpNow = 0;
};

vector<Cell> cellList;
vector<Cell> addedCell;

void Init() {
	cellList.clear();
	addedCell.clear();
	
	for (int i = 0; i < bojeong; i++) {
		memset(map[i], 0, sizeof(int) * bojeong);
	}
}

void InitNewMap() {
	for (int j = 0; j < bojeong; j++) {
		memset(newMap[j], 0, sizeof(int) * bojeong);
	}
}

void Input() {
	Init();
	InitNewMap();

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
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			printf("%d ", map[i+500][j+500]);
		}
		printf("\n");
	}

	for (int i = 0; i < cellList.size(); i++) {
		Cell thisCell = cellList[i];
		printf("줄기세포 x:%d y:%d 생명력:%d 현재생명력:%d\n", thisCell.r - bojeong, thisCell.c - bojeong, thisCell.hpFix, thisCell.hpNow);
	}
}

int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
void Grow(int r, int c) {
	int rtmp, ctmp;
	for (int i = 0; i < 4; i++) {
		rtmp = r + dir[i][0];
		ctmp = c + dir[i][1];

		if (map[rtmp][ctmp] == -1 || map[rtmp][ctmp] != 0) continue; // 죽은 애가 있는 자리는 pass

		if (newMap[rtmp][ctmp] == 0) {
			addedCell.push_back(Cell{ rtmp, ctmp, map[r][c], 0 });
			map[rtmp][ctmp] = map[r][c];
			newMap[rtmp][ctmp] = map[r][c];
		}
		else if (newMap[rtmp][ctmp] < map[r][c]) { // 죽은 애인지를 검증해야 한다.
			// 기존 애를 새로운 애로 대체하는 코드
			// 벡터리스트 수정
			for (int s = 0; s < cellList.size(); s++) {
				if (cellList[s].r == rtmp && cellList[s].c == ctmp) {
					cellList[s].hpFix = map[r][c];
					cellList[s].hpNow = 0;
					break;
				}
			}
			// map 수정
			map[rtmp][ctmp] = map[r][c];
			newMap[rtmp][ctmp] = map[r][c];
		}
	}
}

int main() {
	int test_case;
	scanf("%d\n", &test_case);
	for (int t = 0; t < test_case; t++) {
		//printf("%d ======================\n", t);
		Input();
		InitNewMap();
		//Print();

		for (int i = 1; i <= T; i++) {
			vector<int> deleteCell;

			InitNewMap();

			for (int j = 0; j < cellList.size(); j++) {
				Cell thisCell = cellList[j];
				
				if (thisCell.hpFix > thisCell.hpNow) {
					cellList[j].hpNow++;
				}
				else if (thisCell.hpFix == thisCell.hpNow) {
					Grow(thisCell.r, thisCell.c);
					cellList[j].hpNow++;
				}
				else {
					cellList[j].hpNow++;
				}

				if (cellList[j].hpFix * 2 <= cellList[j].hpNow) { // 죽는지 검사
					deleteCell.push_back(j);
				}

			}
			// 죽이기
			sort(deleteCell.begin(), deleteCell.end(), greater<int>());
			int delSize = deleteCell.size();
			for (int j = 0; j < delSize; j++) {
				int idx = deleteCell[j];
				map[cellList[idx].r][cellList[idx].c] = -1; // 죽은 애는 -1로 표현
				cellList.erase(cellList.begin() + idx);
			}

			for (int j = 0; j < addedCell.size(); j++) {
				cellList.push_back(addedCell[j]);
			}
			addedCell.clear();
		}

		cout << cellList.size() << endl;

	}

	return 0;
}