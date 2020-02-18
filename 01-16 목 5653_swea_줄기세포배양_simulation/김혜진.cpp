// �ʱ�ȭ�� 1000��ŭ �ؾ��ϴµ� R,C��ŭ -> 500 ��ŭ���� ��� �Ǽ���
// SWEA�� Cell{} �� ������ �������� �ʾ� ����

#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

int R, C, T;
int map[1000][1000]; // ���� �ֳ� ���Ŀ� �ʿ�
int newMap[1000][1000]; // �ִ�ũ�� ��� �ʿ�
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
	
	for (int i = 0; i < 1000; i++) {
		memset(map[i], 0, sizeof(int) * 1000);
	}
}

void InitNewMap() {
	for (int j = 0; j < 1000; j++) {
		memset(newMap[j], 0, sizeof(int) * 1000);
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
				Cell newCell;
				newCell.r = i + bojeong;
				newCell.c = j + bojeong;
				newCell.hpFix = hpFix;
				newCell.hpNow = 0;
				cellList.push_back(newCell);
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
		printf("�ٱ⼼�� x:%d y:%d �����:%d ��������:%d\n", thisCell.r - bojeong, thisCell.c - bojeong, thisCell.hpFix, thisCell.hpNow);
	}
}

int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
void Grow(int r, int c) {
	int rtmp, ctmp;
	for (int i = 0; i < 4; i++) {
		rtmp = r + dir[i][0];
		ctmp = c + dir[i][1];

		if (map[rtmp][ctmp] == -1 || map[rtmp][ctmp] != 0) continue; // ���� �ְ� �ִ� �ڸ��� pass

		if (newMap[rtmp][ctmp] == 0) {
			Cell newCell;
			newCell.r = rtmp; newCell.c = ctmp;
			newCell.hpFix = map[r][c]; newCell.hpNow = 0;
			addedCell.push_back(newCell);
			map[rtmp][ctmp] = map[r][c];
			newMap[rtmp][ctmp] = map[r][c];
		}
		else if (newMap[rtmp][ctmp] < map[r][c]) { // ���� �������� �����ؾ� �Ѵ�.
			// ���� �ָ� ���ο� �ַ� ��ü�ϴ� �ڵ�
			// ���͸���Ʈ ����
			for (int s = 0; s < cellList.size(); s++) {
				if (cellList[s].r == rtmp && cellList[s].c == ctmp) {
					cellList[s].hpFix = map[r][c];
					cellList[s].hpNow = 0;
					break;
				}
			}
			// map ����
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

				if (cellList[j].hpFix * 2 <= cellList[j].hpNow) { // �״��� �˻�
					deleteCell.push_back(j);
				}

			}
			// ���̱�
			sort(deleteCell.begin(), deleteCell.end(), greater<int>());
			int delSize = deleteCell.size();
			for (int j = 0; j < delSize; j++) {
				int idx = deleteCell[j];
				map[cellList[idx].r][cellList[idx].c] = -1; // ���� �ִ� -1�� ǥ��
				cellList.erase(cellList.begin() + idx);
			}

			for (int j = 0; j < addedCell.size(); j++) {
				cellList.push_back(addedCell[j]);
			}
			addedCell.clear();
		}

		
		printf("#%d %d\n", t+1, cellList.size());

	}

	return 0;
}