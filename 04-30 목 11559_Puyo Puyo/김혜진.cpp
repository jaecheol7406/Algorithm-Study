#include <iostream>
#include <string.h>
using namespace std;

string map[12];
int visited[12][6];
bool cont = true; // 터지는 게 있었어서 다음에도 체크를 할 건지
int number = 0; // 연속해서 연결된 개수
int answer;

void Input() {
	for (int i = 0; i < 12; i++) {
		cin >> map[i];
	}
}

void Print() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
	cout << "=====" << endl;
}

void Init() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			visited[i][j] = 0;
		}
	}
	
}


int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
void DFS(char color, int r, int c) {
	int tmpR, tmpC;

	for (int i = 0; i < 4; i++) {
		tmpR = r + dir[i][0];
		tmpC = c + dir[i][1];

		if (tmpR < 0 || tmpC < 0 || 12 <= tmpR || 6 <= tmpC) continue;
		if (map[tmpR][tmpC] != color) continue;
		if (visited[tmpR][tmpC] == 1) continue;

		visited[tmpR][tmpC] = 1;
		number++;
		DFS(color, tmpR, tmpC);

	}
}

void Boom() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			if (visited[i][j] == 1) map[i][j] = '.';
		}
	}
}

bool Check() {
	bool boomed = false;

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			// cout << "(" << i << "," << j << "): " << map[i][j] << endl;
			if (visited[i][j] != 1 && map[i][j] != '.') {
				Init(); // visited 초기화
				number = 1;

				visited[i][j] = 1;
				DFS(map[i][j], i, j);

				if (number >= 4) {
					Boom();
					boomed = true;
				}
			}
		}
	}

	return boomed;
}

void Pull() {
	for (int j = 0; j < 6; j++) {
		int btm = -1; // 초기상태
		for (int i = 11; i >= 0; i--) {
			if (btm == -1 && map[i][j] == '.') { // 비어있는 가장 아래에 있는 곳을 btm에 저장
				btm = i;
			}

			if (btm != -1 && map[i][j] != '.' && btm > i) {
				map[btm][j] = map[i][j];
				map[i][j] = '.';
				btm--;
			}
		}
	}
}

int main() {

	Input();

	while (cont) {
		// cout << "continue: " << cont << endl;

		if (Check()) {
			answer++;
		}
		else {
			cont = false;
		}

		//Print();
		Pull();
		//Print();

	}

	cout << answer;

	return 0;
}