/*
다리를 세우지 못하는 경우에 2짜리를 세워버리는 문제
7 7
1 1 1 0 1 1 1
1 1 1 0 1 1 1
1 1 1 0 1 1 1
0 0 0 0 0 0 0
1 1 1 0 1 1 1
1 1 1 0 1 1 1
1 1 1 0 1 1 1
답: -1
7 8
0 0 0 0 0 0 1 1
1 1 0 0 0 0 1 1
1 1 0 0 0 0 0 0
1 1 0 0 0 1 1 0
0 0 0 0 0 1 1 0
0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1
답: 9
*/
#include <iostream>
#include <vector>
#include <algorithm>
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
vector<Pos> IslandStartPos; // [1]번은 1번 섬의 시작점(가장 왼쪽 위)

int Distance[10][10]; // [a]번 섬에서 [b]번 섬으로 건너가는 최소의 수

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


			DFS(tmpR, tmpC);
			island[tmpR][tmpC] = isCnt;
			visited[tmpR][tmpC] = 1;
		}
	}
}

struct Cands {
	int r;
	int c;
	int len;
};
vector<Cands> cands;

void PickMin(int a, int b) { // dep 섬에서 dest 섬을 가는 최소 거리
	int tmpMin = 100;
	int dep, dest;

	// 가로길: 행이 같을 때, 열거리의 최소값
		// 더 왼쪽에 있는 구역을 결정
	if (IslandStartPos[a].c > IslandStartPos[b].c) {
		dep = b;
		dest = a;
	}
	else {
		dep = a;
		dest = b;
	}
	cout << "출발:" << dep << " 도착:" << dest << endl;

	// dep구역의 모든 행에 대하여
	for (int r = IslandStartPos[dep].r; island[r][IslandStartPos[dep].c] == dep; r++) {
		// cout << r << "행 ";
		int tmpCnt = 0;

		int startC = IslandStartPos[dep].c + 1;
		while (1) {
			cout << startC << "열:" << island[r][startC] << " ";
			if (island[r][startC] != dep) tmpCnt++;
			if (startC >= C) break;
			if (island[r][startC] == dest) {
				cout << " 거리: " << tmpCnt-1;
				if (tmpMin > tmpCnt - 1 && tmpCnt - 1 != 1) { // 문제(예상)
					tmpMin = tmpCnt - 1;
					break;
				}
			}

			startC++;
		}
		cout << endl;
	}

	// 세로길
		// 더 위쪽에 있는 구역을 결정
	if (IslandStartPos[a].r > IslandStartPos[b].r) {
		dep = b;
		dest = a;
	}
	else {
		dep = a;
		dest = b;
	}
	// cout << "출발:" << dep << " 도착:" << dest << endl;

	// dep구역의 모든 열에 대하여
	for (int c = IslandStartPos[dep].c; island[IslandStartPos[dep].r][c] == dep; c++) {
		// cout << c << "열 ";
		int tmpCnt = 0;

		int startR = IslandStartPos[dep].r + 1;
		while (1) {
			cout << startR << "행:" << island[startR][c] << " ";
			if (island[startR][c] != dep) tmpCnt++;
			if (startR >= R) break;
			if (island[startR][c] == dest) {
				cout << " 거리: " << tmpCnt - 1;
				if (tmpMin > tmpCnt - 1 && tmpCnt - 1 != 1) {  // 문제(예상)
					tmpMin = tmpCnt - 1;
					break;
				}
			}
			cout << endl;

			startR++;
		}
		// cout << endl;
	}

	Distance[a][b] = tmpMin;
	Distance[b][a] = tmpMin;

	cands.push_back(Cands{ a, b, tmpMin });

}

void PrintStart() {
	cout << "시작점===============" << endl;
	for (int i = 1; i < isCnt; i++) {
		cout << i << "번 섬의 시작점: " << IslandStartPos[i].r << ", " << IslandStartPos[i].c << endl;
	}
	cout << endl;
}

bool cmp(Cands a, Cands b) {
	if (a.len == b.len)
		return a.r < b.r;

	if (a.len == b.len && a.r == a.c)
		return a.c < b.c;

	return a.len < b.len;
}

int visitedIsland[10];
bool CheckVisited() {
	for (int i = 1; i < isCnt; i++) {
		if (visitedIsland[i] == 0)
			return false;
	}
	return true;
}

int main() {

	Input();
	IslandStartPos.push_back(Pos{ 0,0 }); // 섬 id와 일치시키기 위한 dummy data

	for (int i = 0; i < ones.size(); i++) { // island 배열 만들기
		int thisR = ones[i].r;
		int thisC = ones[i].c;
		if (visited[thisR][thisC] == 0) {

			DFS(thisR, thisC);
			IslandStartPos.push_back(Pos{ thisR, thisC });
			isCnt++;
		}
	}

	Print(); // 섬 id 프린트
	PrintStart(); // 각 섬의 시작점 프린트

	for (int i = 1; i < isCnt; i++) {
		for (int j = i + 1; j < isCnt; j++) {
			if (Distance[i][j] == 0) {
				PickMin(i, j);
			}
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << Distance[i][j] << " ";
		}
		cout << endl;
	}

	sort(cands.begin(), cands.end(), cmp);

	for (int i = 0; i < cands.size(); i++) {
		cout << "다리 길이 " << cands[i].len << " " << cands[i].r << "~" << cands[i].c << endl;
	}
	
	int answer = 0;
	for (int i = 0; i < cands.size(); i++) {
		cout << "i: " << i << endl;
		if (CheckVisited()) { // 모두 방문
			break;
		}
		answer += cands[i].len;
		visitedIsland[cands[i].r] = 1;
		visitedIsland[cands[i].c] = 1;
	}

	cout << "답: " << answer;



	return 0;
}