제 코드는
#include <iostream>
#include <queue>
using namespace std;

int m, n; // 세로, 가로
int matrix[110][110];
int visited[110][110];

struct Pos {
	int x;
	int y;
	int dir;
	int cnt = 0;
};
Pos start;
Pos dest;

void Input() {
	scanf("%d %d\n", &m, &n);
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d ", &matrix[i][j]);
		}
	}
	scanf("%d %d %d\n", &start.x, &start.y, &start.dir);
	scanf("%d %d %d\n", &dest.x, &dest.y, &dest.dir);
}

void Print() {
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			cout << matrix[i][j];
		}
		cout << endl;
	}
}

queue<Pos> q;
int dir[5][2] = { {0, 0},  {0, 1}, {0, -1}, {1, 0}, {-1, 0} }; // 동서남북순

int BFS(Pos start) {
	visited[start.x][start.y] = 1;
	q.push(start);

	while (!q.empty()) {
		Pos thisPos = q.front();
		q.pop();

		if (thisPos.x == dest.x && thisPos.y == dest.y) {
			// dest.dir과의 일치여부도 판단
			if (thisPos.dir == dest.dir) {
				return thisPos.cnt;
			}
			else {
				if ((thisPos.dir + dest.dir) % 4 == 3) {
					return thisPos.cnt + 2;
				}
				else {
					return thisPos.cnt + 1;
				}

			}

		}

		int xtmp, ytmp;
		for (int i = 1; i < 5; i++) { // i 자체가 이동방향과 일치하도록 짰음
			xtmp = thisPos.x + dir[i][0];
			ytmp = thisPos.y + dir[i][1];

			if (xtmp < 1 || m < xtmp || ytmp < 1 || n < ytmp) continue;
			if (matrix[xtmp][ytmp] == 0 && visited[xtmp][ytmp] == 0) {

				if (i == thisPos.dir) { // dir이 같아서 바로 갈 수 있다=> 1번 2번 3번 갈 수 있는지 다 확인하고 가능하면 q에 넣기
					visited[xtmp][ytmp] = 1;
					q.push(Pos{ xtmp, ytmp, thisPos.dir, thisPos.cnt + 1 });

					for (int j = 1; j < 3; j++) { // 2번, 3번 갈 수 있는지 체크
						xtmp += dir[i][0];
						ytmp += dir[i][1];

						if (xtmp < 1 || m < xtmp || ytmp < 1 || n < ytmp) continue;
						if (matrix[xtmp][ytmp] == 0 && visited[xtmp][ytmp] == 0) {
							//visited[xtmp][ytmp] = 1;
							q.push(Pos{ xtmp, ytmp, thisPos.dir, thisPos.cnt + 1 });
						}
					}
				}
				else { // dir이 달라서 turn해야 한다=> 적절한 cnt만큼 더하고 dir 수정해 q에 넣기
					if ((thisPos.dir + i) % 4 == 3) {
						q.push(Pos{ thisPos.x, thisPos.y, i, thisPos.cnt + 2 });
					}
					else {
						q.push(Pos{ thisPos.x, thisPos.y, i, thisPos.cnt + 1 });
					}
				}
			}
		}
	}
	return -1;
}

int main()
{
	Input();

	cout << BFS(start);

	return 0;
}