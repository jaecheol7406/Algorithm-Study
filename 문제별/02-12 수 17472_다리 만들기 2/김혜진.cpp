/*
 7 8
1 0 0 1 1 1 0 0
0 0 1 0 0 0 1 1
0 0 1 0 0 0 1 1
0 0 1 1 1 0 0 0
0 0 0 0 0 0 0 0
0 1 1 1 0 0 0 0
1 1 1 1 1 1 0 0
답: 9
*/
#include <iostream>
#include <vector>
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
	// cout << "출발:" << dep << " 도착:" << dest << endl;

	// dep구역의 모든 행에 대하여
	for (int r = IslandStartPos[dep].r; island[r][IslandStartPos[dep].c] == dep; r++) {
		// cout << r << "행 ";
		int tmpCnt = 0;

		int startC = IslandStartPos[dep].c + 1;
		while (1) {
			// cout << startC << "열:" << island[r][startC] << " ";
			if (island[r][startC] != dep) tmpCnt++;
			if (startC >= C) break;
			if (island[r][startC] == dest) {
				// cout << " 거리: " << tmpCnt-1;
				if (tmpMin > tmpCnt-1) tmpMin = tmpCnt-1;
				break;
			}

			startC++;
		}
		// cout << endl;
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
			// cout << startC << "열:" << island[r][startC] << " ";
			if (island[startR][c] != dep) tmpCnt++;
			if (startR >= R) break;
			if (island[startR][c] == dest) {
				// cout << " 거리: " << tmpCnt - 1;
				if (tmpMin > tmpCnt - 1) tmpMin = tmpCnt - 1;
				break;
			}

			startR++;
		}
		// cout << endl;
	}

	Distance[a][b] = tmpMin;
	Distance[b][a] = tmpMin;
	
}

int MIN = 100;
vector<int> V;
int Selected[10];
void Pick(int cnt) {
	if (cnt >= isCnt - 1) { // 종료 조건
		int sum = 0;
		cout << "순서: ";
		for (int i = 1; i < V.size(); i++) {
			cout << V[i - 1] << "->" << V[i] << " ";
			if (Distance[V[i - 1]][V[i]] == 0) { 
				PickMin(V[i - 1], V[i]);
			}
			cout << "(" << Distance[V[i - 1]][V[i]] << ") ";
			if (Distance[V[i - 1]][V[i]] == 100 || Distance[V[i - 1]][V[i]] < 2) { // 못 간다
				return;
			}
			else {
				sum += Distance[V[i - 1]][V[i]];
			}
			
		}
		cout << endl;
		cout << "sum: " << sum << endl;
		if (sum != 0 && sum < MIN) MIN = sum;
		return;
	}

	for (int i = 1; i < isCnt; i++) {
		if (Selected[i] == 0) {
			Selected[i] = 1;
			V.push_back(i);

			Pick(cnt + 1);

			V.pop_back();
			Selected[i] = 0;
		}
	}
}

void PrintStart() {
	cout << "시작점===============" << endl;
	for (int i = 1; i < isCnt; i++) {
		cout << i << "번 섬의 시작점: " << IslandStartPos[i].r << ", " << IslandStartPos[i].c << endl;
	}
	cout << endl;
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

	// 섬 id로 순열 뽑기
	Pick(0);

	cout << endl;
	if (MIN == 100) {
		cout << "-1";
	}
	else {
		cout << MIN;
	}
	


	return 0;
}