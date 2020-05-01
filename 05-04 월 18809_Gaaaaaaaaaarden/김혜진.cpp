/*
function call: main -> Input -> (DFS -> Throw -> Grow -> BFS -> Init) -> main

1. 함수 설명
DFS: 초기에 배양액을 뿌릴 땅(2)을 G+R개 고른다
Throw: DFS에서 고른 땅을 각각 초록색, 빨간색 뿌리는 경우를 나누어 고른다
Grow: 배양액을 퍼뜨리도록 BFS 함수를 호출한 뒤 그 경우에 피운 꽃 개수를 구하고, 다른 경우를 시도하기 위해 조건을 초기화한다
BFS: 배양액이 퍼진다. 몇 초에 뿌려진 배양액인지 bfsVisitTime에 적으면서 다닌다.

2. 주의점
- DFS로 2차원 배열 점을 뽑는 것이 헷갈림.
  순열로 뽑아야 하고 (예: (1,3)&(3,1) 과 (3,1)&(1,3) 두 개 다 뽑으면 안 됨)
  같은 것을 여러 개 뽑으면 안 됨 (예: (0,0)&(0,0) 뽑으면 안 됨)
- 배양액이 이미 뿌려진 곳에는 다른 배양액을 뿌릴 수 없고, 서로 다른 색의 배양액이 동시에 도착했을 때에만 꽃이 핀다는
  조건을 간과하기 쉬움
*/
#include <iostream>
#include <vector>
#include <queue>;
using namespace std;

struct Pos {
	int r;
	int c;
	int cnt=0;
};

int N, M, G, R;
int map[50][50];
int backup[50][50];

int maxAnswer = 0;
int tmpNumber = 0;

vector<Pos> picked; // DFS에서 사용

queue<Pos> q; // BFS에서 사용
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int bfsVisitTime[50][50];

void Input() {
	cin >> N >> M >> G >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			backup[i][j] = map[i][j];
		}
	}
}

void Init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			map[i][j] = backup[i][j];
			bfsVisitTime[i][j] = 0;
		}
	}
}

void BFS() {
	int tmpR, tmpC;
	while (!q.empty()) {
		Pos thisPos = q.front();
		q.pop();
		if (map[thisPos.r][thisPos.c] != 10 && map[thisPos.r][thisPos.c] != 20) continue; // 이미 꽃이 됐는데 이전에 넣은 애는 pass

		for (int i = 0; i < 4; i++) {
			tmpR = thisPos.r + dir[i][0];
			tmpC = thisPos.c + dir[i][1];

			if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) continue;
			if (map[tmpR][tmpC] == 0 || map[tmpR][tmpC] == -1) continue; // 호수면 pass
			if (map[thisPos.r][thisPos.c] == map[tmpR][tmpC]) continue; // 같은 배양액이 이미 뿌려져 있으면

			if (map[tmpR][tmpC] < 10) { // 이전에 배양액이 도착한 적 없음
				map[tmpR][tmpC] = map[thisPos.r][thisPos.c];
				q.push(Pos{ tmpR, tmpC, thisPos.cnt+1 });
				bfsVisitTime[tmpR][tmpC] = thisPos.cnt + 1;
			}
			else if (map[tmpR][tmpC] != map[thisPos.r][thisPos.c] && bfsVisitTime[tmpR][tmpC] == thisPos.cnt + 1) { // 꽃이 핀다
				tmpNumber++;
				map[tmpR][tmpC] = -1;
			}
		}
	}
}

void Grow() { // 배양액 퍼뜨리기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] != 10 && map[i][j] != 20) continue;
			q.push(Pos{ i,j,0 });
			bfsVisitTime[i][j] = 0;
		}
	}
	tmpNumber = 0;
	BFS();
	if (tmpNumber > maxAnswer) maxAnswer = tmpNumber;
}

int green[5];
void Throw(int cnt, int pre) {
	// 초록색 배양액 뿌릴 부분 고르기
	if (cnt >= G) {
		/*cout << "초록색: ";
		for (int i = 0; i < G; i++) {
			cout << green[i] << "번째 좌표 & ";
		}
		cout << endl;*/

		// 초록, 빨강 구분해 뿌리기
		int greenIdx = 0;
		for (int i = 0; i < picked.size(); i++) {
			if (i == green[greenIdx]) {
				map[picked[i].r][picked[i].c] = 10; // green 뿌리기

				greenIdx++;
			}
			else {
				map[picked[i].r][picked[i].c] = 20; // red  뿌리기
			}
		}

		Grow();

		Init();
		
		return;
	}

	for (int i = pre; i < picked.size(); i++) {
		green[cnt] = i;
		Throw(cnt + 1, i + 1);
	}
}


void DFS(int cnt, int preR, int preC) {
	if (cnt >= (G + R)) {
		/*for (int i = 0; i < picked.size(); i++) {
			cout << "(" << picked[i].r << "," << picked[i].c << ") ";
		}
		cout << endl;*/

		Throw(0, 0);

		return;
	}

	// 2차원 배열에서 점을 순열로 중복 없이 고르기
	for (int i = preR; i < N; i++) { // 이미 고른 점보다 더 위 행은 보지 않는다
		int startJ;
		if (preR == i) { // 이번에 고르는 점의 행과 이미 고른 점의 행이 같으면 j는 더 작은 건 안 본다
			startJ = preC;
		}
		else { // 이번 행이 저번 행보다 크다
			startJ = 0;
		}

		for (int j = startJ; j < M; j++) {
			if (map[i][j] != 2) continue;

			// 이미 뽑힌 점과 같은 것은 x
			 if (cnt != 0 && picked[cnt - 1].r == i && picked[cnt - 1].c == j) 
				 continue;

			if (map[i][j] == 2) {
				picked.push_back(Pos{ i, j });
				DFS(cnt + 1, i, j);
				picked.pop_back();
			}
		}
	}
}

int main() {

	Input();

	DFS(0, 0, 0);

	cout << maxAnswer;

	return 0;
}