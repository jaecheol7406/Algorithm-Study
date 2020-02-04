/*
 * cands.size() 갑자기 변화하여 종료가 제대로 되지 않음
*/
#include <iostream>
#include <vector>
using namespace std;

struct Pos {
	int r;
	int c;
};

int map[10][10];
int visited[10][10];
vector<Pos> cands;

void Input() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			scanf("%d ", &map[i][j]);
			if (map[i][j] == 1) {
				cands.push_back(Pos{ i, j });
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

	for (int i = 0; i < cands.size(); i++) {
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
	for (int i = 0; i < cands.size(); i++) {
		if (visited[cands[i].r][cands[i].c] == 1) return false;
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
			cout << "i: " << i << " j: " << j << endl;
			visited[i][j] = 1;
		}
	}
	return true;
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

int papers[6] = {0, 5, 5, 5, 5, 5};
int Min = -1;
void DFS(int n) {
	cout << "dfs n: " << n << " max: " << cands.size() <<  endl;

	if (n >= cands.size()) {
		cout << "종료조건" << endl;
		/*if (isDone()) {
			int used = 25;
			for (int i = 1; i < 6; i++) {
				used -= papers[i];
			}
			cout << used << endl;
			if (used > 0 && Min > used) {
				Min = used;
			}
		}*/
		return;
	}

	int thisR = cands[n].r;
	int thisC = cands[n].c;

	if (visited[thisR][thisC] == 1) {
		DFS(n + 1);
		return;
	}

	for (int size = 5; size >= 1; size--) {
		cout << "size: " << size << endl;
		if (Paste(thisR, thisC, size)) {
			papers[size]--;

			if (papers[size] < 0) { // 백트래킹
				papers[size]++;
				return;
			}

			DFS(n + 1);

			UndoVisit(thisR, thisC, size);
			papers[size]++;
			
		}
		else{
			UndoVisit(thisR, thisC, size);
		}
		PrintVisited();
	}
}

int main() {
	Input();
	
	DFS(0);
	cout << Min << endl;
	
	return 0;
}