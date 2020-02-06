/*
0 0 0 0 0 0 0 0 0 0
0 1 1 0 0 0 0 0 0 0
0 1 1 1 0 0 0 0 0 0
0 0 1 1 1 1 1 0 0 0
0 0 0 1 1 1 1 0 0 0
0 0 0 0 1 1 1 0 0 0
0 0 1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
답: 7
dfs(7)에서 고른 visited 유지가 잘 되지 않고 있음
*/
#include <iostream>
#include <vector>
using namespace std;

struct Pos {
	int r;
	int c;
};

int map[15][15];
int visited[15][15];
vector<Pos> cands;
int candsNum;

void Input() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			scanf("%d ", &map[i][j]);
			if (map[i][j] == 1) {
				cands.push_back(Pos{ i, j });
				candsNum++;
			}
		}
	}
}

void Print() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%d ", map[i][j]);
		}
		cout << endl;
	}

	for (int i = 0; i < candsNum; i++) {
		cout << cands[i].r << ", " << cands[i].c << endl;
	}
}

void PrintVisited() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%d ", visited[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

bool isDone() {
	for (int i = 0; i < candsNum; i++) {
		if (visited[cands[i].r][cands[i].c] == 0) return false;
	}
	return true;
}

bool Paste(int r, int c, int size) {
	int stdR = r + (size - 1);
	int stdC = c + (size - 1);

	if (10 <= stdR || 10 <= stdC) return false;

	for (int i = r; i <= stdR; i++) {
		for (int j = c; j <= stdC; j++) {
			if (map[i][j] != 1 || visited[i][j] == 1) {
				return false;
			}
		}
	}
	return true;
}

void DoVisit(int r, int c, int size) {
	int stdR = r + (size - 1);
	int stdC = c + (size - 1);

	for (int i = r; i <= stdR; i++) {
		for (int j = c; j <= stdC; j++) {
			visited[i][j] = 1;
		}
	}
}

void UndoVisit(int r, int c, int size) {
	int stdR = r + (size - 1);
	int stdC = c + (size - 1);

	for (int i = r; i <= stdR; i++) {
		for (int j = c; j <= stdC; j++) {
			visited[i][j] = 0;
		}
	}
}

int papers[6] = { 0, 5, 5, 5, 5, 5 };
int Min = 999999;
void DFS(int n) {
	// cout << "======================================" << endl;
	// cout << "DFS(" << n << ") max: " << candsNum << endl;

	if (n >= candsNum) { // 종료조건
		if (isDone()) {
			int used = 25;
			for (int i = 1; i < 6; i++) {
				used -= papers[i];
			}
			// cout << "used: " << used << endl;
			if (Min > used) {
				Min = used;
			}
		}
		return;
	}

	int thisR = cands[n].r;
	int thisC = cands[n].c;

	if (visited[thisR][thisC] == 1) {
		DFS(n + 1);
		// return;
	}

	for (int size = 5; size >= 1; size--) {
		// cout << "size: " << size << endl;
		if (Paste(thisR, thisC, size)) {
			papers[size]--;

			if (papers[size] < 0) { // 백트래킹
				// cout << "backtracking!!" << endl;
				papers[size]++;
				return;
			}

			DoVisit(thisR, thisC, size);

			// cout << "pick  " << size << "  for dfs(" << n << ")" << endl;
			// PrintVisited();

			DFS(n + 1);

			UndoVisit(thisR, thisC, size);
			papers[size]++;

		}
		/*else {
			UndoVisit(thisR, thisC, size);
		}*/
	}
}

int main() {
	Input();

	DFS(0);

	if (Min == 999999) {
		cout << "-1";
	}
	else {
		cout << Min << endl;
	}


	return 0;
}