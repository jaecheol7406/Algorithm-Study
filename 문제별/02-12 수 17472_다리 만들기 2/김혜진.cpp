/*
10 5
0 1 0 0 0
1 1 1 0 0
1 0 1 1 1
0 1 1 1 0
1 0 0 0 1
1 1 1 0 1
0 0 0 0 1
0 0 0 1 0
0 0 0 1 1
0 0 0 0 0
답: -1

10 6
0 0 0 1 0 0
0 0 0 1 0 0
0 1 0 0 0 1
0 0 0 0 0 0
1 1 0 1 1 0
1 0 0 0 1 0
1 1 0 0 1 0
0 0 0 0 1 1
0 0 0 0 0 0
0 1 0 0 0 0
답: 13
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

bool CheckRow(int num, int c) {
	for (int i = 0; i < R; i++) {
		if (island[i][c] == num)
			return true;
	}
	return false;
}

bool CheckCol(int num, int r) {
	for (int i = 0; i < C; i++) {
		if (island[r][i] == num)
			return true;
	}
	return false;
}

void PickMin(int a, int b) { // dep 섬에서 dest 섬을 가는 최소 거리
	int tmpMin = 100; // 그대로 100이면 '못 간다'는 뜻
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
	// cout << "==================출발:" << dep << " 도착:" << dest << "===============" << endl;
	
	// cout << dep << "구역의 모든 행에 대해서====" << endl;
	for (int r = IslandStartPos[dep].r; CheckCol(dep, r); r++) {
		// cout << r << "행 " << endl;
		int tmpCnt = 0;

		int startC = IslandStartPos[dep].c + 1;
		
		while (1) {
			
			if (island[r][startC] != dep) tmpCnt++;
			if (startC >= C) {
				startC++;
				break;
			}
			if (island[r][startC] != dep && island[r][startC] != dest && island[r][startC] != 0) { // 중간에 다른 섬이 걸치면 안됨(추가)
				startC++;
				break;
			}
			if (island[r][startC] == dest) {
				if (tmpCnt - 1 == 1) {
					startC++; // 추가
					break;
				}
				if (tmpMin > tmpCnt - 1) {
					tmpMin = tmpCnt - 1;
					// cout << dest << "섬까지 " << tmpCnt -1 << endl;
					break;
				}
			}

			startC++;
		}
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

	// cout << dep << "구역의 모든 열에 대해서====" << endl;
	for (int c = IslandStartPos[dep].c; CheckRow(dep, c); c++) {
		// cout << c << "열 " << endl;
		int tmpCnt = 0;

		int startR = IslandStartPos[dep].r + 1;
		while (1) {
			if (island[startR][c] != dep) tmpCnt++;
			if (startR >= R) {
				startR++;
				break;
			}
			if (island[startR][c] != dep && island[startR][c] != dest && island[startR][c] != 0) { // 중간에 다른 섬이 걸치면 안됨(추가)
				startR++;
				break;
			}
			if (island[startR][c] == dest) {
				if (tmpCnt - 1 == 1) {
					startR++; // 추가
					break;
				}
				if (tmpMin > tmpCnt - 1 ) {
					tmpMin = tmpCnt - 1;
					// cout << dest << "섬까지 " << tmpCnt - 1 << endl;
					break;
				}
			}

			startR++;
		}
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
		if (visitedIsland[i] != 1)
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
	// PrintStart(); // 각 섬의 시작점 프린트

	for (int i = 1; i < isCnt; i++) {
		for (int j = i + 1; j < isCnt; j++) {
			if (Distance[i][j] == 0) {
				PickMin(i, j);
			}
		}
	}

	/*for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << Distance[i][j] << " ";
		}
		cout << endl;
	}*/

	sort(cands.begin(), cands.end(), cmp);

	for (int i = 0; i < cands.size(); i++) {
		cout << "다리 길이 " << cands[i].len << " " << cands[i].r << "~" << cands[i].c << endl;
	}

	int tmpArea = 2;

	int answer = 0;
	visitedIsland[cands[0].r] = 1;
	for (int i = 0; i < cands.size(); i++) {
		// cout << "i: " << i << endl;
		if (CheckVisited()) { // 모두 방문
			break;
		}
		if (cands[i].len == 100) {
			answer = 0;
			break;
		}

		if (visitedIsland[cands[i].r] == 1 && visitedIsland[cands[i].c] == 1) continue;
		answer += cands[i].len;

		// 집계하되, 서로 연결된 섬을 표시한다.
		if (visitedIsland[cands[i].r] == 1 && visitedIsland[cands[i].c] != 1) {
			if (visitedIsland[cands[i].c] != 0) {
				for(int t=1; t<isCnt; t++) {
					if (visitedIsland[t] == visitedIsland[cands[i].c])
						visitedIsland[t] = 1;
				}
			}
			visitedIsland[cands[i].c] = 1;
		}
		else if (visitedIsland[cands[i].c] == 1 && visitedIsland[cands[i].r] != 1) {
			if (visitedIsland[cands[i].r] != 0) {
				for (int t = 1; t < isCnt; t++) {
					if (visitedIsland[t] == visitedIsland[cands[i].r])
						visitedIsland[t] = 1;
				}
			}
			visitedIsland[cands[i].r] = 1;
		}
		else if (visitedIsland[cands[i].c] != 0) {
			visitedIsland[cands[i].r] = visitedIsland[cands[i].c];
		}
		else { // 둘 다 처음임
			visitedIsland[cands[i].r] = tmpArea;
			visitedIsland[cands[i].c] = tmpArea;
			tmpArea++;
		}
	}

	cout << "visit 현황" << endl;
	for (int i = 1; i < isCnt; i++) {
		cout << visitedIsland[i] << " ";
	}
	cout << endl;

	if (answer == 0) cout << "-1";
	else cout << answer;



	return 0;
}