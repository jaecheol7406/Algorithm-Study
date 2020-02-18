#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int T, bcNum;
int aMove[110]; // index는 0부터 사용
int bMove[110];
struct BC {
	int x;
	int y;
	int c; // coverage
	int p; // power
};
vector<BC> bcList;

struct Person {
	int x;
	int y;
};
Person A;
Person B;

int map[15][15][10];
int visited[15][15][10];
int dir[5][2] = { {0, 0},  {0 ,1}, {0, -1}, {1, 0}, {-1, 0} };

void Init() {
	// aMove 초기화
	// bMove 초기화

	bcList.clear();

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			for (int z = 0; z < 10; z++) {
				map[i][j][z] = 0;
				visited[i][j][z] = 0;
			}
		}
	}

}

void Input() {
	Init();

	scanf("%d %d\n", &T, &bcNum);

	for (int i = 0; i < T; i++) {
		scanf("%d ", &aMove[i]);
	}
	for (int i = 0; i < T; i++) {
		scanf("%d ", &bMove[i]);
	}

	for (int i = 0; i < bcNum; i++) {
		int x, y, c, p;
		scanf("%d %d %d %d\n", &y, &x, &c, &p);
		bcList.push_back(BC{ x - 1, y - 1, c, p });
	}

	A.x = 0; A.y = 0;
	B.x = 9; B.y = 9;
}



void DFS(int x, int y, int c, int p, int cnt, int bcIdx) {
	// visited[x][y][bcIdx] = 1;
	map[x][y][bcIdx] = p;

	if (c == cnt) {
		return;
	}

	int xtmp, ytmp;
	for (int i = 0; i < 4; i++) {
		xtmp = x + dir[i + 1][0];
		ytmp = y + dir[i + 1][1];

		if (xtmp < 0 || 10 <= xtmp || ytmp < 0 || 10 <= ytmp) continue;
		/*if (visited[xtmp][ytmp][bcIdx] == 0) { cnt 때문인지 visited가 불필요하다
			DFS(xtmp, ytmp, c, p, cnt + 1, bcIdx);
			// visited[xtmp][ytmp][bcIdx] = 1;
		}*/
		DFS(xtmp, ytmp, c, p, cnt + 1, bcIdx);
	}
}
void MakeMap() {
	for (int i = 0; i < bcNum; i++) {
		// 출발 위치는 bcList[i].x, bcList[i].y이고 bcList[i].c번만 DFS를 해야 하며 map에는 bcList[i].p를 채운다
		DFS(bcList[i].x, bcList[i].y, bcList[i].c, bcList[i].p, 0, i);
		// visited[bcList[i].x][bcList[i].y][i] = 1;
	}
}

void PrintMap() {
	for (int i = 0; i < bcNum; i++) {
		cout << i << "번째 BC의 맵" << endl;
		for (int j = 0; j < 10; j++) {
			for (int z = 0; z < 10; z++) {
				printf("%d ", map[j][z][i]);
			}
			cout << endl;
		}
	}
}

int moveDir[5][2] = { {0, 0}, {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
int main() {
	int t;
	cin >> t;

	for (int t_case = 1; t_case <= t; t_case++) {
		Input();

		// 범위 matrix 만들기
		MakeMap();

		//printf("#%d====================================\n", t_case);
		//PrintMap();

		// 이동시 충전량 세기
		
		int sum = 0;
		for (int second = 0; second <= T; second++) {
			int max = 0;
			for (int i = 0; i < bcNum; i++) {
				for (int j = 0; j < bcNum; j++) {

					int pointNow = map[A.x][A.y][i] + map[B.x][B.y][j];
					if (i == j && bcNum > 1) pointNow /= 2;
					if (max < pointNow) max = pointNow;
				}
			}

			sum += max;

			A.x += moveDir[aMove[second]][0];
			A.y += moveDir[aMove[second]][1];
			B.x += moveDir[bMove[second]][0];
			B.y += moveDir[bMove[second]][1];
		}

		cout << "#" << t_case << " " << sum << endl;



	}

	return 0;
}