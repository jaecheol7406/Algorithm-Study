#include <iostream>
#include <vector>
using namespace std;

struct Chess {
	int r;
	int c;
	int dir;
};

int N, K;
int bg[15][15];
vector<int> map[15][15];
vector<Chess> chessInfo;

void Input() {
	scanf("%d %d\n", &N, &K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &bg[i][j]);
		}
	}

	chessInfo.push_back(Chess{ -1, -1, 0 }); // dummy data
	int r, c, dir;
	for (int i = 1; i <= K; i++) {
		scanf("%d %d %d", &r, &c, &dir);
		chessInfo.push_back(Chess{ r - 1, c - 1, dir - 1 });
		map[r - 1][c - 1].push_back(i);
	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", bg[i][j]);
		}
		cout << endl;
	}

	for (int i = 1; i <= K; i++) {
		Chess thisChess = chessInfo[i];
		cout << thisChess.r << thisChess.c << thisChess.dir << endl;
	}
}

void PrintNum() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j].size();
		}
		cout << endl;
	}
	cout << endl;
}
int newR, newC, targetNum;
Chess thisChess;

int dir[4][2] = { {0, 1}, {0, -1}, {-1, 0}, {1, 0} };
int dirChange[4] = { 1, 0, 3, 2 };

void MoveWhite(int num) {
	for (int i = 0; i < map[thisChess.r][thisChess.c].size(); i++) {
		// cout << map[thisChess.r][thisChess.c][i] << " *";
		if (map[thisChess.r][thisChess.c][i] == num) {
			targetNum = i;
			break;
		}

	}
	// cout << num << "�� �� ��°���� ����? " << targetNum << endl;

   // ���ο� ��ġ�� �̵��� ��Ų��
	for (int i = targetNum; i < map[thisChess.r][thisChess.c].size(); i++) {
		map[newR][newC].push_back(map[thisChess.r][thisChess.c][i]);
	}

	// ���� ���� ����
	for (int i = targetNum; i < map[thisChess.r][thisChess.c].size(); i++) {
		chessInfo[map[thisChess.r][thisChess.c][i]].r = newR;
		chessInfo[map[thisChess.r][thisChess.c][i]].c = newC;
	}

	// ���� ��ġ���� ������
	int tmpRem = map[thisChess.r][thisChess.c].size();
	for (int i = targetNum; i < tmpRem; i++) {
		map[thisChess.r][thisChess.c].erase(map[thisChess.r][thisChess.c].begin() + targetNum);
	}
}

void MoveRed(int num) {
	for (int i = 0; i < map[thisChess.r][thisChess.c].size(); i++) {
		if (map[thisChess.r][thisChess.c][i] == num) {
			targetNum = i;
			break;
		}

	}

	// ���ο� ��ġ�� �̵��� ��Ų��
	for (int i = map[thisChess.r][thisChess.c].size() - 1; i >= targetNum; i--) {
		map[newR][newC].push_back(map[thisChess.r][thisChess.c][i]);
	}

	// ���� ���� ����
	for (int i = map[thisChess.r][thisChess.c].size() - 1; i >= targetNum; i--) {
		chessInfo[map[thisChess.r][thisChess.c][i]].r = newR;
		chessInfo[map[thisChess.r][thisChess.c][i]].c = newC;
	}

	// ���� ��ġ���� ������
	int tmpRem = map[thisChess.r][thisChess.c].size();
	for (int i = targetNum; i < tmpRem; i++) {
		map[thisChess.r][thisChess.c].pop_back();
	}
}

void MoveBlue(int num) {
	// cout << "blue! ������ " << chessInfo[num].dir << "���� ";
	chessInfo[num].dir = dirChange[thisChess.dir];
	// cout << chessInfo[num].dir << "�� �ٲ�" << endl;
	thisChess = chessInfo[num];


	newR = thisChess.r + dir[thisChess.dir][0];
	newC = thisChess.c + dir[thisChess.dir][1];
	// cout << "=> ���ο� ��ġ: " << newR << newC << "(" << bg[newR][newC] << ")" << endl;

	if (newR < 0 || N <= newR || newC < 0 || N <= newC) {
		MoveBlue(num);
	}
	// ������ �ٲٰ� �ٽ� �õ�
	else if (bg[newR][newC] == 0) { // ���
		MoveWhite(num);
	}
	else if (bg[newR][newC] == 1) { // ������
		MoveRed(num);
	}
	else { // �� �Ķ���
		// �ƹ��͵� ���� �ʴ´�
	}
}


bool Move(int num) {
	// �����δ�

	thisChess = chessInfo[num];
	// cout << num << "�� �� ������. " << endl;

	newR = thisChess.r + dir[thisChess.dir][0];
	newC = thisChess.c + dir[thisChess.dir][1];
	// cout << "���� " << bg[newR][newC] << endl;

	if (newR < 0 || N <= newR || newC < 0 || N <= newC) {
		MoveBlue(num);
	}
	else if (bg[newR][newC] == 0) { // ���
		MoveWhite(num);
	}
	else if (bg[newR][newC] == 1) { // ������
		MoveRed(num);
	}
	else { // �Ķ���
		MoveBlue(num);
	}

	// PrintNum();


	// ������ ���� 4�� �̻� �׿� ������ 
	if (map[newR][newC].size() >= 4)
		return true;
	else
		return false;
}

bool Go() {
	for (int i = 1; i <= K; i++) {
		if (Move(i)) { // ��������
			return true;
		}

	}
	return false;
}


int main() {

	Input();
	// PrintNum();

	for (int t = 1; t <= 1000; t++) {
		if (Go()) { // ��������
			cout << t;
			return 0;
		}
	}
	cout << "-1";

	return 0;
}