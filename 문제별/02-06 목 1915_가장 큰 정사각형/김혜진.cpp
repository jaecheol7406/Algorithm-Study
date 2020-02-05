#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Pos {
	int r;
	int c;
};

int R, C;
int map[1005][1005];
int maxSize[1005][1005];
vector<Pos> cands;

int MAX = 0;

void Input() {
	scanf("%d %d\n", &R, &C);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf("%1d", &map[i][j]);
			if (map[i][j] == 1) {
				maxSize[i][j] = min(R - i, C - j);
				cands.push_back(Pos{ i, j });
				MAX = 1;
			}
			

		}
	}
}

void Print() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			printf("%d ", maxSize[i][j]);
		}
		cout << endl;
	}

	for (int i = 0; i < cands.size(); i++) {
		cout << cands[i].r << ", " << cands[i].c << endl;
	}
}

bool CanDo(int thisR, int thisC, int size) {
	int stdR = thisR + (size - 1);
	int stdC = thisC + (size - 1);
	// cout << "size: " << size << "일 때 기준좌표: " << stdR << "," << stdC << endl;

	if (R <= stdR || C <= stdC) return false;

	for (int i = thisR; i <= stdR; i++) {
		for (int j = thisC; j <= stdC; j++) {
			if (map[i][j] != 1) {
				return false;
			}
		}
	}

	return true;
}

void DFS(int n) {
	int thisR = cands[n].r;
	int thisC = cands[n].c;
	// cout << "이번좌표: " << thisR << "," << thisC << endl;

	for (int size = maxSize[thisR][thisC]; size > MAX; size--) {
		// 정사각형을 만들 수 있는지 확인

		if (CanDo(thisR, thisC, size)) {
			if (MAX < size) {
				MAX = size;
			}
		}

		
	}
}

int main() {

	Input();
	// Print();

	for (int i = 0; i < cands.size(); i++) {
		if (maxSize[cands[i].r][cands[i].c] <= MAX) continue;
		DFS(i);
	}

	cout << MAX*MAX;

	return 0;
}