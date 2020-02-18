// 시간 초과는 안 나고, 틀렸습니다 나오는 코드
/* 반례
3 3 9
1 1 1000 1 1
1 2 999 2 2
2 1 1000 3 3
2 2 999 4 4
1 3 1000 1 5
3 1 999 2 6
2 3 1000 3 7
3 2 999 4 8
3 3 1000 1 9

answer: 8

*/
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
//Shark newmap[110][110];
int gobackArr[10010];
vector<Shark> sharkList;

int maxSpeed = 0;

void Input() {
	scanf("%d %d %d\n", &R, &C, &Num);

	for (int i = 0; i < Num; i++) {
		int r, c, s, d, z;
		int idx = i;
		scanf("%d %d %d %d %d\n", &r, &c, &s, &d, &z);
		if (maxSpeed < s) {
			maxSpeed = s;
		}
		sharkList.push_back(Shark{ r - 1, c - 1, s, d, z, i });

		int goback;
		if (d <= 2) { // 위 또는 아래 즉 행과 관련
			goback = 2 * (R - 1);
		}
		else {
			goback = 2 * (C - 1);
		}
		gobackArr[i] = goback;

	}
}

void Print() {
	for (int i = 0; i < sharkList.size(); i++) {
		Shark thisShark = sharkList[i];
		printf("%d: %d %d %d %d %d\n", thisShark.idx, thisShark.r, thisShark.c, thisShark.s, thisShark.d, thisShark.z);
	}

}

bool compare(Shark a, Shark b) {
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

void Init() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] = -1;
		}
	}
}

int dir[5][2] = { {0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

int main()
{
	Input();
	if (Num == 0) {
		printf("0");
		return 0;
	}

	for (int time = 0; time < C; time++) {
		
		Init();
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

			// 이 상어 없애기
			sharkList.erase(sharkList.begin() + 0);


		}

		//printf("Point: %d\n", man.point);

		//3.상어 이동
		for (int i = 0; i < sharkList.size(); i++) {
			int newR = 0;
			int newC = 0;

			int thisGoBack = gobackArr[sharkList[i].idx];
			int seconds = sharkList[i].s % thisGoBack;

			for (int second = 0; second < seconds; second++) {

				// 방향 검사 및 보정
				sharkList[i].d = CheckDir(sharkList[i]);

				sharkList[i].r += dir[sharkList[i].d][0];
				sharkList[i].c += dir[sharkList[i].d][1];
			}
			// 겹치는 애들이 있는지 확인 (map에는 이동을 이미 끝낸 애들만 들어있다)
			int idxToRemove;
			if (map[sharkList[i].r][sharkList[i].c] != -1) { // 비어 있지 않으면
				int legacyIdx = map[sharkList[i].r][sharkList[i].c]; // 이전에 넣은 애가 현재 sharkList에서 몇 번째 인덱스인지
				if (sharkList[legacyIdx].z > sharkList[i].z) { // 이전에 들어간 애가 더 크면
					// sharkList.erase(sharkList.begin() + i); // 이번 애를 지운다
					idxToRemove = i;
				}
				else { // 이번 애가 더 크면
					// sharkList.erase(sharkList.begin() + legacyIdx);
					idxToRemove = legacyIdx;
					map[sharkList[i].r][sharkList[i].c] = i;
				}
				// i--;
				sharkList.erase(sharkList.begin() + idxToRemove);
				i--;
			}

			else {
				map[sharkList[i].r][sharkList[i].c] = i;
			}

		}

	}
	printf("%d", man.point);
}
