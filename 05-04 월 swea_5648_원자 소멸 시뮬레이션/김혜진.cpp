/*
제한시간 초과
*/
#include <iostream>
#include <vector>
using namespace std;

struct Atom {
	int r;
	int c;
	int d; // 이동 방향
	int e; // 에너지. 에너지 0이면 이미 터져서 없어진 원자
};

int N; // 원자 개수
vector<Atom> atomList;
int map[4001][4001]; // 원자위치 표시, 값: 원자 인덱스(atomList상 인덱스)
int alive;

int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

void Input() {
	for (int i = 0; i <= 4000; i++) {
		for (int j = 0; j <= 4000; j++) {
			map[i][j] = -1;
		}
	}

	cin >> N;

	int r, c, d, e;
	for (int i = 0; i < N; i++) {
		cin >> c >> r >> d >> e;

		r = (r + 1000) * 2;
		c = (c + 1000) * 2;
		atomList.push_back(Atom{ r, c, d, e });
		map[r][c] = i;
		alive++;
	}

	
}

int tmpR, tmpC;
vector<int> crash; // 이번 시간내에 충돌하는 원자 리스트

int main() {

	int tCase;
	cin >> tCase;

	for (int tcase = 1; tcase <= tCase; tcase++) {
		int answer = 0;

		Input();

		/*for (int i = 0; i < atomList.size(); i++) {
			cout << "i: " << i << " => " << atomList[i].r << "," << atomList[i].c << endl;
		}*/
		int time = 4005;

		while (alive != 0 && time > 0) { // 1초
			time--;

			// cout << "===================alive(" << alive << ") time(" << time << ")" << endl;
			crash.clear();

			// 원자 움직이기
			for (int t = 0; t < atomList.size(); t++) {

				Atom at = atomList[t]; // 이번에 이동하는 원자
				if (at.e == 0) continue; // 이동하지 않을 원자
				// cout << "원자인덱스: " << t << " " << at.r << "," << at.c << endl;

				tmpR = at.r + dir[at.d][0];
				tmpC = at.c + dir[at.d][1];
				if (tmpR == -1) tmpR = 4000;
				if (tmpC == -1) tmpC = 4000;
				if (tmpR == 4001) tmpR = 0;
				if (tmpC == 4001) tmpC = 0;

				if (map[tmpR][tmpC] != -1) { // 어떤 원자와 충돌
					// cout << "crash!" << endl;
					crash.push_back(t);
					crash.push_back(map[tmpR][tmpC]);

					map[at.r][at.c] = -1;
					map[tmpR][tmpC] = t;
				}
				else {
					atomList[t].r = tmpR;
					atomList[t].c = tmpC;

					map[at.r][at.c] = -1;
					map[tmpR][tmpC] = t;
				}
			}

			// 충돌한 원자들 처리
			// cout << "crashed: ";
			for (int t = 0; t < crash.size(); t++) {
				// cout << crash[t] << " ";
				Atom at = atomList[crash[t]];
				if (at.e == 0) continue; // 이미 앞에서 처리한 원자

				answer += at.e;
				atomList[crash[t]].e = 0;

				map[at.r][at.c] = -1;
				alive--;
			}
			// cout << endl;
		}

		cout << "#"<< tcase << " " << answer << endl;
	}

	

	return 0;
}