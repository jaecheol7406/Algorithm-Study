#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

struct Pos {
	int r;
	int c;
};

int N;
int map[110][110];
vector<Pos> ones;

int islandMap[110][110];
int islandNum = 1;
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

vector<vector<Pos>> points; // points의 인덱스(=섬의 개수), vector<Pos>(그 섬 안의 포인트)

void Input() {
	scanf("%d\n", & N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &map[i][j]);
			if (map[i][j] == 1) {
				ones.push_back(Pos{ i, j });
			}
		}
	}
}

void Print() {
	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", map[i][j]);
		}
		cout << endl;
	}*/

	/*for (int i = 0; i < ones.size(); i++) {
		cout << ones[i].r << ones[i].c << endl;
	}*/

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", islandMap[i][j]);
		}
		cout << endl;
	}

	for (int i = 0; i < points.size(); i++) {
		cout << i + 1 << "번 섬의 요소========" << endl;
		for (int j = 0; j < points[i].size(); j++) {
			cout << points[i][j].r << points[i][j].c << endl;
		}
	}
}

vector<Pos> tmp;
void PickIsland(int thisR, int thisC) {

	islandMap[thisR][thisC] = islandNum;
	tmp.push_back(Pos{ thisR, thisC });

	int tmpR, tmpC;
	for (int i = 0; i < 4; i++) {
		tmpR = thisR + dir[i][0];
		tmpC = thisC + dir[i][1];

		if (tmpR < 0 || N <= tmpR || tmpC < 0 || N <= tmpC) continue;
		if (map[tmpR][tmpC] == 1 && islandMap[tmpR][tmpC] == 0) {
			PickIsland(tmpR, tmpC);
		}
	}
}

int MIN = 99999999;
vector<int> V;
int Selected[10010];
void Comb(int cnt) {
	if (cnt >= 2) { // 종료 조건
		// V[0]번 섬의 모든 점에서 V[1]번 섬의 모든 점으로 가는 최솟값을 구한다
		/*for (int i = 0; i < V.size(); i++) {
			cout << V[i] << " ";
		}
		cout << endl;*/
		
		vector<Pos> from = points[V[0] - 1];
		vector<Pos> to = points[V[1] - 1];
		int dist;

		for (int i = 0; i < from.size(); i++) {
			// cout << from[i].r << from[i].c << endl;
			for (int j = 0; j < to.size(); j++) {
				dist = abs(from[i].r - to[j].r) + abs(from[i].c - to[j].c) - 1;
				if (MIN > dist) MIN = dist;
			}
		}

		return;
	}

	for (int i = cnt+1; i < islandNum; i++) {
		if (Selected[i] == 0) {
			Selected[i] = 1;
			V.push_back(i);

			Comb(cnt + 1);

			V.pop_back();
			Selected[i] = 0;
		}
	}
}

int main() {

	Input();
	

	for (int i = 0; i < ones.size(); i++) {
		if (islandMap[ones[i].r][ones[i].c] == 0) {
			PickIsland(ones[i].r, ones[i].c);
			islandNum++;
			points.push_back(tmp);
			tmp.clear();
		}
	}

	// Print();

	Comb(0);

	if (MIN == 99999999)
		cout << 0;
	else
		cout << MIN;
	

	return 0;
}