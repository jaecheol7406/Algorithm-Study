/*
틀렸습니다
*/
#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

int r, c, k;
int map[110][110];
int R = 3; int C = 3; // 현재 배열의 r, c 값
vector<int> cand; // 등장하는 숫자
int number[110]; // 숫자 key의 등장 횟수

struct num {
	int n;
	int cnt;
};
vector<num> V;

bool cmp(num a, num b) {
	if (a.cnt == b.cnt) {
		return a.n < b.n;
	}
	return a.cnt < b.cnt;
}

void Input() {
	scanf("%d %d %d", &r, &c, &k);

	int tmp;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
}

void Print() {
	// cout << r << c << k << endl;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main() {

	Input();
	// Print();
	
	int t = 0;

	while (map[r-1][c-1] != k) {
		t++;
		if (t > 100) {
			t = -1;
			break;
		}

		if (R >= C) {
			// 행연산
			for (int i = 0; i < R; i++) {
				
				memset(number, 0, 110);
				cand.clear();

				for (int j = 0; j < C; j++) { // 각 열 요소에 대해
					if (map[i][j] != 0) {
						if (number[map[i][j]] == 0) {
							cand.push_back(map[i][j]);
						}
						number[map[i][j]]++;
					}
				}

				for (int j = 0; j < cand.size(); j++) {
					V.push_back(num{ cand[j], number[cand[j]] });
				}
				sort(V.begin(), V.end(), cmp);

				memset(map[i], 0, 110);


				for (int j = 0; j < V.size(); j++) {
					map[i][j*2] = V[j].n;
					map[i][(j*2)+1] = V[j].cnt;
					if (j >= 49) break;
				}

				if (C < V.size() * 2)
					C = V.size() * 2;

				V.clear();

			}
		}
		else {
			// 열연산
			for (int j = 0; j < C; j++) {
				memset(number, 0, 110);
				cand.clear();

				for (int i = 0; i < R; i++) {
					if (map[i][j] != 0) {
						if (number[map[i][j]] == 0) {
							cand.push_back(map[i][j]);
						}
						number[map[i][j]]++;
					}
				}

				for (int i = 0; i < cand.size(); i++) {
					V.push_back(num{ cand[i], number[cand[i]] });
				}
				sort(V.begin(), V.end(), cmp);

				for (int i = 0; i < R; i++) { // 초기화 (=clear)
					map[i][j] = 0;
				}

				for (int i = 0; i < V.size(); i++) {
					map[i * 2][j] = V[i].n;
					map[(i * 2) + 1][j] = V[i].cnt;
					if (i >= 49) break;
				}

				if (R < V.size() * 2)
					R = V.size() * 2;

				V.clear();
			}
			

		}
		// Print();
	}

		
		printf("%d", t);
	

	return 0;
}