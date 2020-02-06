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
vector<Pos> IslandStartPos; // [1]���� 1�� ���� ������(���� ���� ��)

int distance[10][10]; // [a]�� ������ [b]�� ������ �ǳʰ��� �ּ��� ��

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

int PickMin(int dep, int des) { // �����, ������
	// ���� Ž��

	// ���� Ž��

	return 0;
}

vector<int> V;
int Selected[10];
void Pick(int cnt) {
	if (cnt >= isCnt - 1) { // ���� ����
		cout << "����: ";
		for (int i = 1; i < V.size(); i++) {
			cout << V[i-1] << "->" << V[i] << " ";
		}
		cout << endl;
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
	cout << "������===============" << endl;
	for (int i = 1; i < isCnt; i++) {
		cout << i << "�� ���� ������: " << IslandStartPos[i].r << ", " << IslandStartPos[i].c << endl;
	}
	cout << endl;
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

	// �� id�� ���� �̱�
	Pick(0);
	

	return 0;
 }