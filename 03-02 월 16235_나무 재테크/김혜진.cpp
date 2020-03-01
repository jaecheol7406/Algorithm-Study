/*

# 1*1 짜리 칸의 정보를 구조체로 정의함
struct Space {
	vector<int> tree;		---> 해당 위치에 심어진 나무의 나이. 나무의 개수를 알 수 없으므로 벡터로 선언
	vector<int> dead;		---> 해당 위치에 심어져 있었으나 봄에 죽은 것으로 판단된 나무의 나이
	int nutr = 5;			---> 해당 위치의 양분

# Space 구조체를 저장하는 2차원 배열을 생성
Space map[12][12];

# 해당 배열에 대하여 4계절을 돌린다
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int N, M, K;

struct Space {
	vector<int> tree;		// 해당 위치에 심어진 나무의 나이
	vector<int> dead;		// 죽은 나무의 나이
	int nutr = 5;				// 양분
};

// 2차원 배열 인덱스 1부터 시작
Space map[12][12];			// 땅 정보
int winter[12][12];			// 겨울에 줄 양분 정보

void Input() {
	scanf("%d %d %d\n", &N, &M, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d ", &winter[i][j]);
		}
	}

	int r, c, age;
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d\n", &r, &c, &age);
		map[r][c].tree.push_back(age);
	}
}

void Count() {
	// cout << "현재 나무의 수: ";
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cnt += map[i][j].tree.size();
		}
	}
	cout << cnt << endl;
}

void Info() {
	cout << "==================" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << i << "," << j << "의 나무 나이: ";
			for (int t = 0; t < map[i][j].tree.size(); t++) {
				cout << map[i][j].tree[t] << " ";
			}
			cout << "/ 양분: " << map[i][j].nutr << endl;
		}
		cout << endl;
	}
}

void Spring() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			sort(map[i][j].tree.begin(), map[i][j].tree.end());					// 나이가 어린 나무 먼저 양분을 주기 위해 오름차순 정렬

			// 모든 나무가 양분 섭취를 시도한다
			vector<int> alive;													// 죽은 나무를 살아남은 나무 배열에서 제거하기 위해, 살아남은 애들만 담을 벡터
			for (int t = 0; t < map[i][j].tree.size(); t++) {
				if (map[i][j].nutr >= map[i][j].tree[t]) {						// 살아남음
					map[i][j].nutr -= map[i][j].tree[t];
					alive.push_back(map[i][j].tree[t] + 1);
				}
				else {															 // 죽음
					map[i][j].dead.push_back(map[i][j].tree[t]);
				}
			}

			map[i][j].tree.clear();												// 기존의 나무 벡터를 지우고, 살아남은 애들만 들어 있는 벡터로 덮어쓴다
			for (int t = 0; t < alive.size(); t++) {
				map[i][j].tree.push_back(alive[t]);
			}

		}
	}
}

void Summer() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int sum = 0;
			for (int t = 0; t < map[i][j].dead.size(); t++) {
				sum += floor(map[i][j].dead[t]/2);
			}
			map[i][j].nutr += sum;
			map[i][j].dead.clear();
		}
	}
}

int dir[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
void Fall() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			for (int t = 0; t < map[i][j].tree.size(); t++) {
				if (map[i][j].tree[t] % 5 == 0) {								// 번식 대상
					int tmpr, tmpc;
					for (int c = 0; c < 8; c++) {
						tmpr = i + dir[c][0];
						tmpc = j + dir[c][1];

						if (tmpr < 1 || tmpc < 1 || 10 < tmpr || 10 < tmpc) continue;
						map[tmpr][tmpc].tree.push_back(1);
					}
				}
			}
		}
	}
}

void Winter() {
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j].nutr += winter[i][j];
		}
	}
}

int main() {

	Input();

	for (int year = 1; year <= K; year++) {
		Spring();
		Summer();
		Fall();
		Winter();
	}
	Count();

	return 0;
}