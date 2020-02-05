#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Pos {
	int r;
	int c;
	int max;
};

int R, C;
int map[1005][1005];
int sumMap[1005][1005];
vector<Pos> cands;

int MAX = 0;

void Input() {
	scanf("%d %d\n", &R, &C);
	for (int i = 0; i < R; i++) {
		int sum = 0;
		for (int j = 0; j < C; j++) {
			scanf("%1d", &map[i][j]);
			if (map[i][j] == 1) {

				cands.push_back(Pos{ i, j, min(R - i, C - j) });
				MAX = 1;
			}

			sum += map[i][j];
			sumMap[i][j] = sum;

		}
	}
}

void Print() {

	for (int i = 0; i < cands.size(); i++) {
		cout << cands[i].r << ", " << cands[i].c << " , " << cands[i].max << endl;
	}
}

bool CanDo(int thisR, int thisC, int size) {
	int stdR = thisR + (size - 1);
	int stdC = thisC + (size - 1);
	// cout << "size: " << size << "일 때 기준좌표: " << stdR << "," << stdC << endl;

	if (R <= stdR || C <= stdC) return false;

	for (int i = thisR; i <= stdR; i++) {
		if (sumMap[i][stdC] - sumMap[i][thisC-1] != (size)) return false;
	}

	/*for (int i = thisR; i <= stdR; i++) {
		for (int j = thisC; j <= stdC; j++) {
			if (map[i][j] == 0) return false;
		}
	}*/

	return true;
}

bool Check(int n) {
	int thisR = cands[n].r;
	int thisC = cands[n].c;
	int thisMax = cands[n].max;
	// cout << "이번좌표: " << thisR << "," << thisC << " max: " << thisMax << endl;

	for (int size = thisMax; size > MAX; size--) {
		// 정사각형을 만들 수 있는지 확인

		if (CanDo(thisR, thisC, size)) {
			// cout << "현재 MAX: " << MAX << "이번 정사각형: " << size << "짜리" << endl;
			if (MAX < size) {
				MAX = size;
			}
			return true; // 어차피 size는 점점 작아지므로 먼저 발견됐으면 뒤 비교 할 필요 없음
		}


	}
	return false;
}

bool cmp(Pos posA, Pos posB) {
	if (posA.max == posB.max && posA.r == posB.r) {
		return posA.c < posB.c;
	}
	if (posA.max == posB.max) {
		return posA.r < posB.r;
	}
	return posA.max > posB.max;
}

int main() {

	Input();

	// max 기준으로 내림차순 정렬
	sort(cands.begin(), cands.end(), cmp);

	// Print();

	for (int i = 0; i < cands.size(); i++) {
		if(cands[i].max > MAX)
			Check(i);
	}

	cout << MAX * MAX;

	return 0;
}