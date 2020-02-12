// ���� pass, Ʋ�Ƚ��ϴ�
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

void PickMin(int a, int b) { // dep ������ dest ���� ���� �ּ� �Ÿ�
	int tmpMin = 100; // �״�� 100�̸� '�� ����'�� ��
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
	// cout << "==================���:" << dep << " ����:" << dest << "===============" << endl;
	
	// cout << dep << "������ ��� �࿡ ���ؼ�====" << endl;
	for (int r = IslandStartPos[dep].r; CheckCol(dep, r); r++) {
		// cout << r << "�� " << endl;
		int tmpCnt = 0;

		int startC = IslandStartPos[dep].c + 1;
		
		while (1) {
			
			if (island[r][startC] != dep) tmpCnt++;
			if (startC >= C) {
				startC++;
				break;
			}
			if (island[r][startC] != dep && island[r][startC] != dest && island[r][startC] != 0) { // �߰��� �ٸ� ���� ��ġ�� �ȵ�(�߰�)
				startC++;
				break;
			}
			if (island[r][startC] == dest) {
				if (tmpCnt - 1 == 1) {
					startC++; // �߰�
					break;
				}
				if (tmpMin > tmpCnt - 1) {
					tmpMin = tmpCnt - 1;
					// cout << dest << "������ " << tmpCnt -1 << endl;
					break;
				}
			}

			startC++;
		}
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

	// cout << dep << "������ ��� ���� ���ؼ�====" << endl;
	for (int c = IslandStartPos[dep].c; CheckRow(dep, c); c++) {
		// cout << c << "�� " << endl;
		int tmpCnt = 0;

		int startR = IslandStartPos[dep].r + 1;
		while (1) {
			if (island[startR][c] != dep) tmpCnt++;
			if (startR >= R) {
				startR++;
				break;
			}
			if (island[startR][c] != dep && island[startR][c] != dest && island[startR][c] != 0) { // �߰��� �ٸ� ���� ��ġ�� �ȵ�(�߰�)
				startR++;
				break;
			}
			if (island[startR][c] == dest) {
				if (tmpCnt - 1 == 1) {
					startR++; // �߰�
					break;
				}
				if (tmpMin > tmpCnt - 1 ) {
					tmpMin = tmpCnt - 1;
					// cout << dest << "������ " << tmpCnt - 1 << endl;
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
	// PrintStart(); // �� ���� ������ ����Ʈ

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
		cout << "�ٸ� ���� " << cands[i].len << " " << cands[i].r << "~" << cands[i].c << endl;
	}

	int answer = 0;
	for (int i = 0; i < cands.size(); i++) {
		// cout << "i: " << i << endl;
		if (CheckVisited()) { // ��� �湮
			break;
		}
		if (cands[i].len == 100) break;
		answer += cands[i].len;
		visitedIsland[cands[i].r] = 1;
		visitedIsland[cands[i].c] = 1;
	}

	if (answer == 0) cout << "-1";
	else cout << answer;



	return 0;
}