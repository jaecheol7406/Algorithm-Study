/*
해답에 필요한 function call: main -> Input -> (DFS <--반복--> BFS) -> main

1. K개의 바이러스 중, 초기에 활성화시킬 M개 바이러스를 조합(DFS)으로 선정한다
2. 뽑힌 경우에서 BFS를 활용해 모든 빈칸을 활성화시키는 최소 시간을 구한다
3. 매 경우에도 나온 최소시간 중 값이 가장 작은 것을 출력한다
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
int map[55][55];

struct Pos {
	int r;
	int c;
	int cnt;
};

// 활성화시킬 바이러스를 선정할 때(DFS) 쓰는 변수
vector<Pos> virus;
int picked[15];

// 각 경우에 모든 빈 칸을 활성바이러스화 시키는 데(BFS) 쓰는 변수
queue<Pos> q;
int tmpMap[55][55];
int visited[55][55];
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

// 반복문을 돌면서 답을 도출할 때 쓰이는 변수
int vacantSize = 0;
int tmpR, tmpC;
int tmpTime;
int answer = 5000;

void Input() {
	scanf("%d %d\n", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &map[i][j]);
			if (map[i][j] == 2) {
				virus.push_back(Pos{ i, j, 0 });
			}
			else if (map[i][j] == 0) {
				vacantSize++;
			}
		}
	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", tmpMap[i][j]);
		}
		cout << endl;
	}
	/*for (int i = 0; i < virus.size(); i++) {
		cout << virus[i].r << "," << virus[i].c << endl;
	}*/
}


int BFS(int cnt) {
	/*for (int i = 0; i < M; i++) { // 뽑힌 바이러스 순번
		cout << picked[i];
	}
	cout << endl;*/

	int activatedNum = 0; // 활성화된 빈 칸의 개수 초기화

	// 현재 활성화된 바이러스 상태를 tmpMap에 복사
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tmpMap[i][j] = map[i][j];
		}
	}
	// Print();

	// visited 초기화
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[i][j] = 0;
		}
	}

	while (!q.empty()) {
		Pos thisVirus = q.front();
		// cout << "thisVirus(" << thisVirus.cnt << "): " << thisVirus.r << "," << thisVirus.c << endl;
		q.pop();
		visited[thisVirus.r][thisVirus.c] = 1;

		for (int i = 0; i < 4; i++) {
			tmpR = thisVirus.r + dir[i][0];
			tmpC = thisVirus.c + dir[i][1];

			if (tmpR < 0 || N <= tmpR || tmpC < 0 || N <= tmpC) continue;
			if (visited[tmpR][tmpC] == 1 || tmpMap[tmpR][tmpC] == 1) continue;

			if (tmpMap[tmpR][tmpC] == 0) { // 빈공간을 활성바이러스화 시키는 경우
				activatedNum++;
				// cout << tmpR << "," << tmpC << ":"<< tmpMap[tmpR][tmpC] << ", 바이러스 활성화 => " << activatedNum << " 총 빈칸 수: " << vacantSize << endl;

				if (activatedNum == vacantSize) { // 모든 바이러스를 활성화한 경우
					return thisVirus.cnt + 1;
				}
			}

			tmpMap[tmpR][tmpC] = 9; // 빈 칸 또는 비활성바이러스를 활성바이러스화 하기
			q.push(Pos{ tmpR, tmpC, thisVirus.cnt + 1 });
			visited[tmpR][tmpC] = 1;
			// cout << "push " << tmpR << "," << tmpC << "(" << thisVirus.cnt+1 << ")" << endl;
		}
	}

	return 5000; // 찾지 못함
}


void DFS(int cnt, int pre) {
	if (cnt >= M) {
		/*for (int i = 0; i < M; i++) { // 뽑힌 바이러스 순번
			cout << picked[i];
		}
		cout << endl;*/

		while (!q.empty()) { // q 비우기
			q.pop();
		}

		for (int i = 0; i < M; i++) {
			tmpR = virus[picked[i]].r;
			tmpC = virus[picked[i]].c;
			map[tmpR][tmpC] = 9; // 활성화
			q.push(Pos{ tmpR, tmpC, 0 }); // q에 초기부터 활성화된 바이러스 넣기
		}

		// Print();

		// 퍼지는 데 몇 초 걸리는지 재기
		tmpTime = BFS(0);

		while (!q.empty()) { // q 비우기
			q.pop();
		}

		// cout << tmpTime << "과 " << answer << "비교" << endl;
		if (tmpTime < answer) answer = tmpTime;

		// 다시 바이러스를 모두 비활성화
		for (int i = 0; i < M; i++) {
			tmpR = virus[picked[i]].r;
			tmpC = virus[picked[i]].c;
			map[tmpR][tmpC] = 2;
		}
		return;
	}

	for (int i = pre + 1; i < virus.size(); i++) {
		picked[cnt] = i;
		DFS(cnt + 1, i);	
	}

}

int main() {

	Input();

	if (vacantSize == 0) {
		cout << 0;
		return 0;
	}

	// virus 개수개만큼 중에서 m개를 뽑는 조합
	DFS(0, -1);

	if (answer == 5000) cout << -1;
	else cout << answer;

	return 0;
}