/*
13% 틀렸습니다

예외사항
- 1 0 2 0 0 0 1 0 0 2 처럼 앞부분에선 연결불가했는데 뒤에서 연결가능한 때
5 10
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 0 0 0 0
1 0 1 0 0 1 0 1 0 1
1 1 1 0 0 0 0 1 1 1
1 1 1 1 1 1 1 1 1 1
답: 2

- '모든 섬 연결 체크'란 1,2,3이 서로 연결되고 4,5가 연결됐지만 이 두 그룹이 연결 안되면 꽝
10 6
0 0 0 1 0 0
0 0 0 1 0 0
0 1 0 0 0 1
0 0 0 0 0 0
1 1 0 1 1 0
1 0 0 0 1 0
1 1 0 0 1 0
0 0 0 0 1 1
0 0 0 0 0 0
0 1 0 0 0 0
답: 13

- 짧은 다리라도 이미 연결된 섬을 연결한다면 pass
9 8
0 0 1 0 0 0 0 1
0 0 1 1 0 0 0 1
0 0 1 1 1 0 0 1
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 1 1 1 1
0 0 0 0 0 0 1 1
1 0 0 0 0 0 1 1
답: 10
10 7
1 1 1 1 1 1 1
0 0 0 0 0 0 0
0 0 0 0 0 0 0
1 0 0 1 0 0 1
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 1 0 0 1
답: 13
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Dist {
	int is1;
	int is2;
	int dist;
};
vector<Dist> distList;

int N, M;
int map[10][10];
int island[10][10];
int minDist[7][7]; // 섬 간의 거리

int answer;

int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int visitedIsland[10][10];
int islandIdx;

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
}

void getIsland(int r, int c) {
	int tmpR, tmpC;

	for (int i = 0; i < 4; i ++) {
		tmpR = r + dir[i][0];
		tmpC = c + dir[i][1];

		if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) continue;
		if (visitedIsland[tmpR][tmpC] == 1) continue;
		if (map[tmpR][tmpC] != 1) continue;

		visitedIsland[tmpR][tmpC] = 1;
		island[tmpR][tmpC] = islandIdx;
		getIsland(tmpR, tmpC);

	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << island[i][j];
		}
		cout << endl;
	}
}

int horDist(int is1, int is2) {
	int answer = 9999;

	for (int i = 0; i < N; i++) {
		int startPos = -1;
		int endPos = -1;
		bool started = false;
		int startedIsland = -1;

		for (int j = 0; j < M; j++) {
			
			if (island[i][j] == is1 || island[i][j] == is2) {
				if (!started) { // 최초로 어떤 점을 찾음
					startedIsland = island[i][j];
					startPos = j;
					started = true;
				}
				else if (island[i][j] == startedIsland) {
					startPos = j;
				}
				else if (island[i][j] != startedIsland) {

					endPos = j;
					if (endPos - startPos <= 2) { // 길이가 2 이상이어야 함
						started = false;
						continue;
					}
						
					if ((endPos - startPos) < answer) answer = endPos - startPos;

					break; // 다음 행을 검사하러 가기
				}
			}
			else if (started && island[i][j] != 0) { // 중간에 다른 섬이 껴있음
				started = false;
				continue;
			}

		}
	}

	// cout << answer << endl;
	return answer;
}

int verDist(int is1, int is2) {
	int answer = 9999;

	for (int j = 0; j < M; j++) {
		int startPos = -1;
		int endPos = -1;
		bool started = false;
		int startedIsland = -1;

		for (int i = 0; i < N; i++) {
			if (island[i][j] == is1 || island[i][j] == is2) {
				if (!started) {
					startedIsland = island[i][j];
					startPos = i;
					started = true;
				}
				else if (island[i][j] == startedIsland) {
					startPos = i;
				}
				else if (island[i][j] != startedIsland) {
					endPos = i;
					if (endPos - startPos <= 2) { // 다리 길이는 2 이상
						started = false;
						continue;
					}

					if ((endPos - startPos) < answer) answer = endPos - startPos;

					break;
				}
			}
			else if (started && island[i][j] != 0) { // 중간에 다른 섬이 껴있는 경우
				started = false;
				continue;
			}
		}
	}
	return answer;
}

void getDistance(int is1, int is2) {
	int minDistance = 9999;

	// 가로로 연결
	int tmp = horDist(is1, is2);
	if (tmp >= 3 && minDistance > tmp) minDistance = tmp - 1;

	// 세로로 연결
	tmp = verDist(is1, is2);
	if (tmp >= 3 && minDistance > tmp) minDistance = tmp - 1;

	// cout << minDistance << endl;

	minDist[is1][is2] = minDistance;
	//minDist[is2][is1] = minDistance;
	distList.push_back(Dist{ is1, is2, minDistance });
}

bool cmp(Dist a, Dist b) {
	if (a.dist == b.dist && a.is1 == b.is1) {
		return a.is2 < b.is2;
	}
	if (a.dist == b.dist) {
		return a.is1 < b.is1;
	}

	return a.dist < b.dist;
}

int linked[7];
int main() {

	Input();

	// 섬의 개수 구하기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] != 1) continue;
			if (visitedIsland[i][j] == 1) continue;
			islandIdx++;

			visitedIsland[i][j] = 1;
			island[i][j] = islandIdx;
			getIsland(i, j);
		}
	}

	// Print();

	// 각 섬별 거리 최소거리 구하기 (디버깅용)
	for (int i = 1; i < islandIdx; i++) {
		for (int j = i + 1; j <= islandIdx; j++) {
			getDistance(i, j);
		}
	}

	/*for (int i = 1; i <= islandIdx; i++) {
		for (int j = 1; j <= islandIdx; j++) {
			cout << minDist[i][j] << " ";
		}
		cout << endl;
	}*/

	sort(distList.begin(), distList.end(), cmp);

	int uniqueIdx = 0;
	for (int i = 0; i < distList.size(); i++) {
		cout << "이번 짧은 다리:" << distList[i].dist << endl;
		
		// 완료조건 충족여부==========================================
		int check = 0;
		for (int j = 1; j <= 6; j++) if (linked[j] == 1) check++;

		/*for (int j = 1; j <= 6; j++) cout << linked[j] << " ";
		cout << endl;
		cout << "check: " << check << "?=" << islandIdx << endl;*/

		if (check == islandIdx) break;
		// 완료조건 충족여부==========================================

		if (distList[i].dist == 9999) {
			answer = 9999;
			break;
		}

		int is1 = distList[i].is1;
		int is2 = distList[i].is2;
		cout << is1 << "과 " << is2 << endl;

		if (linked[is1] != 0 && linked[is2] != 0) { // 이미 어딘가에 연결되어 있는 두 개
			if (linked[is1] == linked[is2]) continue; // 이미 서로 연결 돼있다면 다리 만들지 않고 pass

			int std; // 더 작은 수
			int verse; // 더 큰 수
			if (linked[is1] > linked[is2]) {
				std = linked[is2];
				verse = linked[is1];
			}
			else {
				std = linked[is1];
				verse = linked[is2];
			}

			for (int t = 1; t <= islandIdx; t++) {
				if (linked[t] == verse) linked[t] = std;
			}
		}
		else if (linked[is1] == 0 && linked[is2] == 0) { // 둘다 처음 연결
			uniqueIdx++;
			linked[is1] = uniqueIdx;
			linked[is2] = uniqueIdx;
		}
		else if (linked[is2] != 0 && linked[is1] == 0) { // is1만 새로 연결
			linked[is1] = linked[is2];
		}
		else if (linked[is1] != 0 && linked[is2] == 0) { // is2만 새로 연결
			linked[is2] = linked[is1];
		}
		

		answer += distList[i].dist;
		cout << "다리길이 += " << distList[i].dist << endl;

	}

	if (answer == 9999) cout << -1;
	else cout << answer;

	return 0;
}