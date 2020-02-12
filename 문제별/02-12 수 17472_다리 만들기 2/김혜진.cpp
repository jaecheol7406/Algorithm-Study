/*
�ٸ��� ������ ���ϴ� ��쿡 2¥���� ���������� ����
7 7
1 1 1 0 1 1 1
1 1 1 0 1 1 1
1 1 1 0 1 1 1
0 0 0 0 0 0 0
1 1 1 0 1 1 1
1 1 1 0 1 1 1
1 1 1 0 1 1 1
��: -1
7 8
0 0 0 0 0 0 1 1
1 1 0 0 0 0 1 1
1 1 0 0 0 0 0 0
1 1 0 0 0 1 1 0
0 0 0 0 0 1 1 0
0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1
��: 9
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
vector<Pos> IslandStartPos; // [1]���� 1�� ���� ������(���� ���� ��)

int Distance[10][10]; // [a]�� ������ [b]�� ������ �ǳʰ��� �ּ��� ��

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

void PickMin(int a, int b) { // dep ������ dest ���� ���� �ּ� �Ÿ�
	int tmpMin = 100;
	int dep, dest;

	// ���α�: ���� ���� ��, ���Ÿ��� �ּҰ�
		// �� ���ʿ� �ִ� ������ ����
	if (IslandStartPos[a].c > IslandStartPos[b].c) {
		dep = b;
		dest = a;
	}
	else {
		dep = a;
		dest = b;
	}
	cout << "���:" << dep << " ����:" << dest << endl;

	// dep������ ��� �࿡ ���Ͽ�
	for (int r = IslandStartPos[dep].r; island[r][IslandStartPos[dep].c] == dep; r++) {
		// cout << r << "�� ";
		int tmpCnt = 0;

		int startC = IslandStartPos[dep].c + 1;
		while (1) {
			cout << startC << "��:" << island[r][startC] << " ";
			if (island[r][startC] != dep) tmpCnt++;
			if (startC >= C) break;
			if (island[r][startC] == dest) {
				cout << " �Ÿ�: " << tmpCnt-1;
				if (tmpMin > tmpCnt - 1 && tmpCnt - 1 != 1) { // ����(����)
					tmpMin = tmpCnt - 1;
					break;
				}
			}

			startC++;
		}
		cout << endl;
	}

	// ���α�
		// �� ���ʿ� �ִ� ������ ����
	if (IslandStartPos[a].r > IslandStartPos[b].r) {
		dep = b;
		dest = a;
	}
	else {
		dep = a;
		dest = b;
	}
	// cout << "���:" << dep << " ����:" << dest << endl;

	// dep������ ��� ���� ���Ͽ�
	for (int c = IslandStartPos[dep].c; island[IslandStartPos[dep].r][c] == dep; c++) {
		// cout << c << "�� ";
		int tmpCnt = 0;

		int startR = IslandStartPos[dep].r + 1;
		while (1) {
			cout << startR << "��:" << island[startR][c] << " ";
			if (island[startR][c] != dep) tmpCnt++;
			if (startR >= R) break;
			if (island[startR][c] == dest) {
				cout << " �Ÿ�: " << tmpCnt - 1;
				if (tmpMin > tmpCnt - 1 && tmpCnt - 1 != 1) {  // ����(����)
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
	cout << "������===============" << endl;
	for (int i = 1; i < isCnt; i++) {
		cout << i << "�� ���� ������: " << IslandStartPos[i].r << ", " << IslandStartPos[i].c << endl;
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
	IslandStartPos.push_back(Pos{ 0,0 }); // �� id�� ��ġ��Ű�� ���� dummy data

	for (int i = 0; i < ones.size(); i++) { // island �迭 �����
		int thisR = ones[i].r;
		int thisC = ones[i].c;
		if (visited[thisR][thisC] == 0) {

			DFS(thisR, thisC);
			IslandStartPos.push_back(Pos{ thisR, thisC });
			isCnt++;
		}
	}

	Print(); // �� id ����Ʈ
	PrintStart(); // �� ���� ������ ����Ʈ

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
		cout << "�ٸ� ���� " << cands[i].len << " " << cands[i].r << "~" << cands[i].c << endl;
	}
	
	int answer = 0;
	for (int i = 0; i < cands.size(); i++) {
		cout << "i: " << i << endl;
		if (CheckVisited()) { // ��� �湮
			break;
		}
		answer += cands[i].len;
		visitedIsland[cands[i].r] = 1;
		visitedIsland[cands[i].c] = 1;
	}

	cout << "��: " << answer;



	return 0;
}