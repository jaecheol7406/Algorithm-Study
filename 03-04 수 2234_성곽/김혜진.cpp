/*
# 기본적으로 BFS로 순회해서 방의 개수 및 가장 큰 방의 크기를 구한다.
# 방문 가능한 방향을 판단한다.
  1.특정 위치(i,j)의 값을 2진수로 바꿔 크기 4짜리 배열(jinsu)에 담는다.
    13  ->  1 1 0 1

  2. dir 배열은 다음과 같이 구성한다.
    dir[0]  <==  2^3 의미, 남쪽에 벽이 있음.
	dir[1]  <==  2^2 의미, 동쪽에 벽이 있음.
	dir[2]  <==  2^1 의미, 북쪽에 벽이 있음.
	dir[3]  <==  2^0 의미, 서쪽에 벽이 있음.

  3. 2진수 배열(jinsu)와 dir배열을 비교해 갈 수 있는 좌표를 q에 넣는다
    if(dir[0] == 1) 남쪽으로 못감=> continue
	if(dir[1] == 1) 동쪽으로 못감=> continue
	if(dir[2] == 1) 북쪽으로 못감=> continue
	if(dir[3] == 1) 서쪽으로 못감=> continue


# 벽을 하나씩 허물 때에는 모든 좌표의 모든 벽을 허문 뒤 위의 과정을 반복한다.
# 벽을 허문다.
  1. 특정 위치(i,j)의 값을 2진수로 바꿔 크기 4짜리 배열(jinsu)에 담는다.
  2. jinsu 배열을 돌면서 값이 1일 경우, 해당 값만큼을 map[i][j]에서 빼고 탐색을 한다.
    map[i][j] -= pow(2, (3 - c));
	예: map[i][j] = 13이라면,
	  map[i][j] -= 8 한 뒤 탐색 시작, 탐색 끝나면 map[i][j] += 8
	  map[i][j] -= 4 한 뒤 탐색 시작, 탐색 끝나면 map[i][j] += 4
	  map[i][j] -= 1 한 뒤 탐색 시작, 탐색 끝나면 map[i][j] += 1
	이와 같은 과정을 모든 (i,j) 구역에 대해 실행한다.
*/
#include <iostream>
#include <queue>
#include <vector>
#include <math.h>
using namespace std;

// BFS에 필요한 기본 변수
struct Pos {
	int r;
	int c;
};
int m, n;
int map[110][110];
int visited[110][110];
queue<Pos> q;

// 벽의 위치가 남쪽, 동쪽, 북쪽, 서쪽 순.
int dir[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
int jinsu[4];

void Input() {
	scanf("%d %d\n", &n, &m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
}

void Print() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", map[i][j]);
		}
		cout << endl;
	}
}

// 10진수 org를 2진수로 바꿔 jinsu 배열에 넣는다
void Convert(int org) {
	for (int i = 3; i>=0; i--) {
		int rems = org % 2;
		jinsu[i] = rems;
		org /= 2;
	}
	/*for (int i = 0; i < 4; i++) {
		cout << jinsu[i] << " ";
	}
	cout << endl;*/
}

int MAX = 0;
void BFS() {
	int maxCnt = 0;
	while (!q.empty()) {
		Pos thisPos = q.front();
		q.pop();
		maxCnt++;
		// cout << thisPos.r << "," << thisPos.c << "방문" << endl;

		int tmpr, tmpc;
		Convert(map[thisPos.r][thisPos.c]);
		for (int i = 0; i < 4; i++) {
			if (jinsu[i] == 1) continue;
			tmpr = thisPos.r + dir[i][0];
			tmpc = thisPos.c + dir[i][1];

			if (tmpr < 0 || tmpc < 0 || m <= tmpr || n <= tmpc) continue;
			if (visited[tmpr][tmpc] != 0) continue;

			q.push(Pos{ tmpr, tmpc });
			visited[tmpr][tmpc] = 1;
		}
	}
	if (MAX < maxCnt) MAX = maxCnt;
}


int cnt = 0;
void Search() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j] == 1) continue;
			q.push(Pos{ i, j });
			visited[i][j] = 1;
			// cout << i << "," << j << "에서 cnt++" << endl;
			cnt++;
			BFS();
		}
	}
}

void Destroy() {

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			Convert(map[i][j]);

			for (int c = 0; c < 4; c++) {
				if (jinsu[c] == 0) continue;
				map[i][j] -= pow(2, (3 - c));
				//cout << i << "," << j << "의 " << c << "번 벽을 허물었다: -" << pow(2, (3-c)) << "=" << map[i][j] << endl;
				
				// visited 리셋
				for (int i = 0; i < m; i++) {
					for (int j = 0; j < n; j++) {
						visited[i][j] = 0;
					}
				}

				Search();
				// cout << "방 개수: " << cnt << "최대 크기: " << MAX << endl;
				map[i][j] += pow(2, (3 - c));
			}
		}
	}
}

int main() {

	Input();
	// Print();

	Search();

	cout << cnt << endl;
	cout << MAX << endl;

	Destroy();
	cout << MAX << endl;

	return 0;
}