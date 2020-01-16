#include <iostream>
using namespace std;

int n;
int map[20][20];

void Input() {
	scanf("%d\n", &n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
}

void Print() {
	printf("%d\n", n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}

struct Pos {
	int r;
	int c;
};

struct Pipe {
	Pos el;
	Pos er;
	int dir; // 1�� ����, 2�� ����, 3�� �밢��
};

bool SearchWidth(Pipe now) {
	int rtmp = now.er.r;
	int ctmp = now.er.c + 1;

	if (rtmp < 0 || n < rtmp || ctmp < 0 || n < ctmp) return false;
	if (map[rtmp][ctmp] == 0) {
		/*Pipe newPipe = Pipe{ now.er, Pos{rtmp, ctmp}, 1 };
		DFS(newPipe);*/
		return true;
	}
	return false;
}

bool SearchHigh(Pipe now) {
	int rtmp = now.er.r + 1;
	int ctmp = now.er.c;

	if (rtmp < 0 || n <= rtmp || ctmp < 0 || n <= ctmp) return false;
	if (map[rtmp][ctmp] == 0) {
		/*Pipe newPipe = Pipe{ now.er, Pos{rtmp, ctmp}, 2 };
		DFS(newPipe);*/
		return true;
	}
	return false;
}

int dir[3][2] = { {1, 0}, {0, 1}, {1, 1} };
bool SearchDiag(Pipe now) {
	int r = now.er.r;
	int c = now.er.c;
	int rtmp, ctmp;
	for (int i = 0; i < 3; i++) {
		rtmp = r + dir[i][0];
		ctmp = c + dir[i][1];

		if (rtmp < 0 || n <= rtmp || ctmp < 0 || n <= ctmp) return false; // �ϳ��� ������ �н��Ѵ�
		if (map[rtmp][ctmp] != 0) { // �ϳ��� �� ��� ������ �н��Ѵ�
			return false;
		}
		
	}

	/*Pipe newPipe = Pipe{ now.er, Pos{ r + 1, c + 1 },3 };
	DFS(newPipe);*/
	return true;
}

int answer;
void DFS(Pipe now) {
	// ���� ����
	if (now.er.r == n - 1 && now.er.c == n - 1) {
		answer++;
		return;
	}

	if (now.dir == 1) { // ���� ����
		if (SearchWidth(now)) { // true��
			Pipe newPipe = Pipe{ now.er, Pos{now.er.r, now.er.c + 1}, 1 };
			DFS(newPipe);
		}
		if (SearchDiag(now)) {
			Pipe newPipe = Pipe{ now.er, Pos{now.er.r + 1, now.er.c + 1}, 3 };
			DFS(newPipe);
		}
	}
	else if (now.dir == 2) { // ���� ����
		if(SearchHigh(now)) {
			Pipe newPipe = Pipe{ now.er, Pos{now.er.r + 1, now.er.c}, 2 };
			DFS(newPipe);
		}
		if (SearchDiag(now)) {
			Pipe newPipe = Pipe{ now.er, Pos{now.er.r + 1, now.er.c + 1}, 3 };
			DFS(newPipe);
		}
	}
	else {
		if (SearchWidth(now)) { // true��
			Pipe newPipe = Pipe{ now.er, Pos{now.er.r, now.er.c + 1}, 1 };
			DFS(newPipe);
		}
		if (SearchHigh(now)) {
			Pipe newPipe = Pipe{ now.er, Pos{now.er.r + 1, now.er.c}, 2 };
			DFS(newPipe);
		}
		if (SearchDiag(now)) {
			Pipe newPipe = Pipe{ now.er, Pos{now.er.r + 1, now.er.c + 1}, 3 };
			DFS(newPipe);
		}
	}
}

int main() {
	Input();

	DFS(Pipe{ Pos{0, 0}, Pos{0, 1}, 1 });
	printf("%d", answer);

	return 0;
}