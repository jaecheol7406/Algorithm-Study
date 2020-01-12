// 코딩중

// 예제 답은 맞으나, 시간 초과 나는 코드
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
using namespace std;

int R, C, Num; // 행, 열, 상어 수
struct Shark {
	int r;
	int c;
	int s; // 속력
	int d; // 방향
	int z; // 크기
	int idx = -1; // 상어 번호
};
struct Human {
	int c = -1;
	int point = 0;
};
Human man;

int map[110][110];
Shark newmap[110][110];
int gobackArr[10010];
vector<Shark> sharkList;

int maxSpeed = 0;

void Input() {
	scanf("%d %d %d\n", &R, &C, &Num);

	for (int i = 0; i < R; i++) {
		/*for (int j = 0; j < C; j++) {
			map[i][j] = -1;
		}*/
		memset(map[i], -1, sizeof(int) * C);
	}

	for (int i = 0; i < Num; i++) {
		int r, c, s, d, z;
		int idx = i;
		scanf("%d %d %d %d %d\n", &r, &c, &s, &d, &z);
		if (maxSpeed < s) {
			maxSpeed = s;
		}
		sharkList.push_back(Shark{ r - 1, c - 1, s, d, z, i });
		map[r - 1][c - 1] = i;

		// 시간 줄이기
		int goback;
		if (d <= 2) { // 위 또는 아래 즉 행과 관련
			goback = 2 * (R - 1);
		}
		else {
			goback = 2 * (C - 1);
		}
		gobackArr[i] = goback;

		// 시간 줄이기
	}
}

void Print() {
	for (int i = 0; i < sharkList.size(); i++) {
		Shark thisShark = sharkList[i];
		printf("%d: %d %d %d %d %d\n", thisShark.idx, thisShark.r, thisShark.c, thisShark.s, thisShark.d, thisShark.z);
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			printf("%d ", map[i][j]);
		}
		printf("%\n");
	}
}

bool compare(Shark a, Shark b) {
	/*if (a.r == b.r) {
		return (abs(a.c - man.c) < abs(b.c - man.c));
	}
	return a.r < b.r;*/
	if (a.c == b.c) {
		return a.r < b.r;
	}
	return (abs(a.c - man.c) < abs(b.c - man.c)); // 컬럼이 제일 비슷한 애
}

int CheckDir(Shark thisShark) {
	switch (thisShark.d) {
	case 1:
		if (thisShark.r <= 0) return 2;
		break;
	case 2:
		if (thisShark.r >= R - 1) return 1;
		break;
	case 3:
		if (thisShark.c >= C - 1) return 4;
		break;
	case 4:
		if (thisShark.c <= 0) return 3;
		break;
	default:
		return thisShark.d;
		break;
	}
	return thisShark.d;
}

void RemoveFromMap(int idx) {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] == idx) {
				map[i][j] = -1;
				return;
			}
		}
	}
	/*for (int i = 0; i < R; i++) {
		memset(map[i], -1, sizeof(int) * C);
	}*/
}

void Init() {
	// map을 초기화
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] = -1;
		}
	}
	for (int i = 0; i < R; i++) {
		memset(map[i], -1, sizeof(int) * C);
	}

	// newmap 정보를 map 으로 이동
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] = newmap[i][j].idx;
		}
	}


	// newmap 초기화
	Shark emptyShark;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			newmap[i][j] = emptyShark;
		}
	}
}

int dir[5][2] = { {0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

// map은 -1일 때 상어가 없는 것.
int main()
{
	Input();
	if (Num == 0) {
		printf("0");
		return 0;
	}

	for (int time = 0; time < C; time++) {
		//printf("time: %d==========\n", time);
		// 1.낚시꾼 이동
		man.c += 1;
		// 상어벡터 정렬
		sort(sharkList.begin(), sharkList.end(), compare);
		//Print();

		// 2.상어 잡기
		if (sharkList[0].c == man.c) {

			// 포인트 얻기
			man.point += sharkList[0].z;

			// map에서 지우기
			//RemoveFromMap(sharkList[0].idx);
			map[sharkList[0].r][sharkList[0].c] = -1;
			// 이 상어 없애기
			sharkList.erase(sharkList.begin() + 0);


		}

		//printf("Point: %d\n", man.point);

		//3.상어 이동
		// for (int second = 0; second < maxSpeed; second++) {
// 			for (int i = 0; i < sharkList.size(); i++) {
		for (int i = 0; i < sharkList.size(); i++) {
			int newR = 0;
			int newC = 0;

			int thisGoBack = gobackArr[sharkList[i].idx];
			int seconds = sharkList[i].s % thisGoBack;

			for (int second = 0; second < seconds; second++) {
				// if (sharkList[i].s < second) continue;

				// 방향 검사 및 보정
				sharkList[i].d = CheckDir(sharkList[i]);

				// 시간 줄이기
				/*int goback;
				if (sharkList[i].d <= 2) { // 위 또는 아래 즉 행과 관련
					goback = 2 * (R - 1);
				}
				else {
					goback = 2 * (C - 1);
				}

				if (second >= goback) {
					second = second % goback - 1;
				}*/

				// 시간 줄이기

				sharkList[i].r += dir[sharkList[i].d][0];
				sharkList[i].c += dir[sharkList[i].d][1];
			}
			// 겹치는 애들이 있는지 확인 (newmap에는 이동을 이미 끝낸 애들만 들어있다)
			int idxToRemove;
			if (newmap[sharkList[i].r][sharkList[i].c].idx != -1) { // 비어 있지 않으면
				if (newmap[sharkList[i].r][sharkList[i].c].z > sharkList[i].z) {
					idxToRemove = sharkList[i].idx;
				}
				else {
					idxToRemove = newmap[sharkList[i].r][sharkList[i].c].z;
					newmap[sharkList[i].r][sharkList[i].c] = sharkList[i];
				}

				// idxToRemove를 지운다
				for (int q = 0; q < sharkList.size(); q++) {
					if (sharkList[q].idx == idxToRemove) {
						sharkList.erase(sharkList.begin() + q);
						break;
					}
				}
				if (i != sharkList.size() - 2) { // 지운 것 직후 번째가 움직이지 않는 문제
					i--;
				}

			}
			else { // 비어 있으면
				newmap[sharkList[i].r][sharkList[i].c] = sharkList[i];
			}

		}
		// 이동: newmap에서 map으로 옮긴다
		Init();

	}
	printf("%d", man.point);
}


// 새로 짜는 중인 코드
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
using namespace std;

int R, C, Num; // 행, 열, 상어 수
struct Shark {
	int r;
	int c;
	int s; // 속력
	int d; // 방향
	int z; // 크기
	int idx=-1; // 상어 번호
};
struct Human {
	int c=-1;
	int point=0;
};
Human man;

int map[110][110];
Shark newmap[110][110];
int gobackArr[10010];
vector<Shark> sharkList;

int maxSpeed=0;

void Input() {
	scanf("%d %d %d\n", &R, &C, &Num);

	for (int i = 0; i < R; i++) {
		/*for (int j = 0; j < C; j++) {
			map[i][j] = -1;
		}*/
		memset(map[i], -1, sizeof(int) * C);
	}
	
	for (int i = 0; i < Num; i++) {
		int r, c, s, d, z;
		int idx = i;
		scanf("%d %d %d %d %d\n", &r, &c, &s, &d, &z);
		if (maxSpeed < s) {
			maxSpeed = s;
		}
		sharkList.push_back(Shark{ r-1, c-1, s, d, z, i });
		map[r - 1][c - 1] = i;

		// 시간 줄이기
		int goback;
		if (d <= 2) { // 위 또는 아래 즉 행과 관련
			goback = 2 * (R - 1);
		}
		else {
			goback = 2 * (C - 1);
		}
		gobackArr[i] = goback;

		// 시간 줄이기
	}
}

void Print() {
	for (int i = 0; i < sharkList.size(); i++) {
		Shark thisShark = sharkList[i];
		printf("%d: %d %d %d %d %d\n", thisShark.idx, thisShark.r, thisShark.c, thisShark.s, thisShark.d, thisShark.z);
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			printf("%d ", map[i][j]);
		}
		printf("%\n");
	}
}

bool compare(Shark a, Shark b) {
	/*if (a.r == b.r) {
		return (abs(a.c - man.c) < abs(b.c - man.c));
	}
	return a.r < b.r;*/
	if (a.c == b.c) {
		return a.r < b.r;
	}
	return (abs(a.c - man.c) < abs(b.c - man.c)); // 컬럼이 제일 비슷한 애
}

int CheckDir(Shark thisShark) {
	switch (thisShark.d) {
	case 1:
		if (thisShark.r <= 0) return 2;
		break;
	case 2:
		if (thisShark.r >= R - 1) return 1;
		break;
	case 3:
		if (thisShark.c >= C - 1) return 4;
		break;
	case 4:
		if (thisShark.c <= 0) return 3;
		break;
	default:
		return thisShark.d;
		break;
	}
	return thisShark.d;
}

void RemoveFromMap(int idx) {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] == idx) {
				map[i][j] = -1;
				return;
			}
		}
	}
	/*for (int i = 0; i < R; i++) {
		memset(map[i], -1, sizeof(int) * C);
	}*/
}

void Init() {
	// map을 초기화
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] = -1;
		}
	}
	for (int i = 0; i < R; i++) {
		memset(map[i], -1, sizeof(int) * C);
	}

	// newmap 정보를 map 으로 이동
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] = newmap[i][j].idx;
		}
	}
	

	// newmap 초기화
	Shark emptyShark;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			newmap[i][j] = emptyShark;
		}
	}
}

int dir[5][2] = { {0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

// map은 -1일 때 상어가 없는 것.
int main()
{
	Input();
	if (Num == 0) {
		printf("0");
		return 0;
	}
	int idxToRemove = -1;
	for (int time = 0; time < C; time++) {
		printf("time: %d==========\n", time);
		// 1.낚시꾼 이동
		man.c += 1;
		// 상어벡터 정렬
		sort(sharkList.begin(), sharkList.end(), compare);
		Print();

		// 2.상어 잡기
		if (sharkList[0].c == man.c) {

			// 포인트 얻기
			man.point += sharkList[0].z;

			// map에서 지우기
			//RemoveFromMap(sharkList[0].idx);
			map[sharkList[0].r][sharkList[0].c] = -1;
			// 이 상어 없애기
			sharkList.erase(sharkList.begin()+0);
			
			
		}
		
		printf("Point: %d\n", man.point);

		//3.상어 이동
		// for (int second = 0; second < maxSpeed; second++) {
// 			for (int i = 0; i < sharkList.size(); i++) {
		for(int i=0; i<sharkList.size(); i++) {
			if (sharkList[i].idx == idxToRemove) {
				sharkList.erase(sharkList.begin() + i);
				continue;
			}

			int thisGoBack = gobackArr[sharkList[i].idx];
			int seconds = sharkList[i].s % thisGoBack;

			/*for(int second = 0; second < seconds; second++) {
				// if (sharkList[i].s < second) continue;

				// 방향 검사 및 보정
				sharkList[i].d = CheckDir(sharkList[i]);
				
				sharkList[i].r += dir[sharkList[i].d][0];
				sharkList[i].c += dir[sharkList[i].d][1];
			}*/

			/*if (sharkList[i].d <= 2) { // 행을 비교한다 하여튼 이런식으로 직접 안가고 자리를 계산하게끔 짠다
				if (seconds <= sharkList[i].r) {
					sharkList[i].r -= seconds;
					if (sharkList[i].r == 0) {
						sharkList[i].d = (sharkList[i].d+1)%3;
					}
				}
				else if(seconds <= sharkList[i].r + R) {
					sharkList[i].r += seconds - sharkList[i].r*2;
					if (sharkList[i].r != R - 1) {
						sharkList[i].d = (sharkList[i].d+1) % 3;
					}
				}
				else {
					//if(sharkList[i].r == 0)
					sharkList[i].r =  (seconds - (sharkList[i].r * 2));
				}
			}
			else {
				if (seconds <= sharkList[i].c) {
					sharkList[i].c -= seconds;
					if (sharkList[i].c == 0) {
						sharkList[i].d = (sharkList[i].d+1) % 5;
					}
				}
				else if (seconds <= sharkList[i].c + C) {
					sharkList[i].c += seconds - sharkList[i].c * 2;
					if (sharkList[i].c != C - 1) {
						sharkList[i].d = (sharkList[i].d+1) % 5;
					}
				}
				else {
					sharkList[i].c = seconds - (C - 1 - sharkList[i].c) - (sharkList[i].c * 2);
				}
			}*/

			// 겹치는 애들이 있는지 확인 (newmap에는 이동을 이미 끝낸 애들만 들어있다)
			int idxToRemove;
			if (newmap[sharkList[i].r][sharkList[i].c].idx != -1) { // 비어 있지 않으면
				if (newmap[sharkList[i].r][sharkList[i].c].z > sharkList[i].z) {
					idxToRemove = sharkList[i].idx;
				}
				else {
					idxToRemove = newmap[sharkList[i].r][sharkList[i].c].z;
					newmap[sharkList[i].r][sharkList[i].c] = sharkList[i];
				}

				// idxToRemove를 지운다
				/*for (int q = 0; q < sharkList.size(); q++) {
					if (sharkList[q].idx == idxToRemove) {
						sharkList.erase(sharkList.begin() + q);
						break;
					}
				}
				if (i != sharkList.size() - 2) { // 지운 것 직후 번째가 움직이지 않는 문제
					i--;
				}*/

			}
			else { // 비어 있으면
				newmap[sharkList[i].r][sharkList[i].c] = sharkList[i];
			}

		}
		// 이동: newmap에서 map으로 옮긴다
		Init();

	}
	printf("%d", man.point);
}
