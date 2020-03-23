/*
BOJ 16236번: 아기 상어


잘못접근: 1. BFS로 처음 방문한 물고기를 먹으면 되는 것으로 착각 -> 먹을 수 있는 물고기 들을 저장하여 조건에 맞게 먹을 물고기를 선택해야함
		  2. eatList의 size가 0인 경우에도 BFS함수 내에서 0번째 인덱스에 접근해서 런타임에러 발생
				-> eatList를 전역변수로 바꾸고, while문 로직 변경 

문제 풀이 : 1. BFS를 사용해서 먹을 수 있는 물고기들 확인한다.
				(1) 먹을 수 있는 물고기가 존재하면 vector에 저장한다.
			2. 먹을 수 있는 물고기의 수가 0인지 1인지 2이상인지 확인한다.
				(1) 0이면 종료
				(2) 1이면 먹을 수 있는 물고기의 리스트인 eatList[0]에 접근하여 잡아 먹고 그에 따른 조건 수행
				(3) 2이상이면 먹을 수 있는 물고기의 리스트를 거리->x축->y축 순서로 sort한다.
			3. 결과 도출
펑션콜 순서 : Solution()에서 무한 루프 수행
				->eatFish() (BFS함수) -> eatList의 size에 따른 조건문 수행 
*/
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
struct Shark {
	int size;
	int x;
	int y;
};
bool visit[25][25];
int board[25][25];
int dx[4] = { -1,0,0,1 };
int dy[4] = { 0,-1,1,0 };
int N;
int time = 0;
Shark shark;
vector<pair<pair<int, int>, int >> eatList;
int sharkEatCnt = 0;
int fishNum = 0;
void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			if (board[i][j] >= 1 && board[i][j] <= 6) {
				fishNum++;
			}
			if (board[i][j] == 9) {
				board[i][j] = 0;
				shark.size = 2;
				shark.x = i;
				shark.y = j;
			}
		}
	}
}
 //                 x,  y         size, time
bool cmp(pair<pair<int, int>,int > A, pair<pair<int, int>,int> B) {
	if (A.second == B.second) {
		if (A.first.first == B.first.first)
			return A.first.second < B.first.second;
		return A.first.first < B.first.first;
	}
	return A.second < B.second;
}
void eatFish() {
	queue<pair<pair<int, int>,int>> que;
	que.push(make_pair(make_pair(shark.x, shark.y),0));
	visit[shark.x][shark.y] = true;
	//vector<pair<pair<int, int>,int >> eatList;
	while (!que.empty()) {
		
		auto cur = que.front();
		que.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.first.first + dx[i];
			int ny = cur.first.second + dy[i];
			int time = cur.second;
			//cout << nx << " " << ny << endl;
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
				continue;
			}
			if (visit[nx][ny])
				continue;
			if (board[nx][ny] > shark.size)
				continue;
			/*
			<!-- 잘못접근 1 -->
			if (board[nx][ny]>0 &&board[nx][ny] < shark.size) { //잡아 먹는다
				board[nx][ny] = 0;
				sharkEatCnt++;
				if (sharkEatCnt == shark.size) {
					sharkEatCnt = 0;
					shark.size++;
				}
				board[shark.x][shark.y] = 0;
				shark.x = nx;
				shark.y = ny;
				fishNum--;
				cout << "Hi: " << nx << " " << ny << endl;
				return time + 1;
			}*/
			if (board[nx][ny] > 0 && board[nx][ny] < shark.size) {
				eatList.push_back(make_pair(make_pair(nx,ny), time+1));
			}
			que.push(make_pair(make_pair(nx, ny), time + 1));
			visit[nx][ny] = true;
		}
	}
	/*
	<!-- 잘못접근 2 -->
	sort(eatList.begin(), eatList.end(), cmp);
	int nx = eatList[0].first.first;
	int ny = eatList[0].first.second;
	board[nx][ny] = 0;
	sharkEatCnt++;
	if (sharkEatCnt == shark.size) {
		sharkEatCnt = 0;
		shark.size++;
	}
	shark.x = nx;
	shark.y = ny;
	fishNum--;
	return eatList[0].second;*/
}

void Solution() {
	int time = 0;
	/*
	<!-- 잘못접근 2 -->
	while (true) {
		//cout << time << endl;
		if (fishNum==0 || checkFinish())
			break;
		//else if (fishNum == 1) {

		//}
		else {
			//가장 가까운 물고기를 먹으러 간다.
			time += eatFish();
		}
		memset(visit, 0, sizeof(visit));
	}*/
	while (true) {
		eatList.clear();
		memset(visit, 0, sizeof(visit));
		eatFish();
		if (eatList.size() == 0) {
			break;
		}
		else if (eatList.size() == 1) {
			int nx = eatList[0].first.first;
			int ny = eatList[0].first.second;
			time += eatList[0].second;
			board[nx][ny] = 0;
			sharkEatCnt++;
			if (sharkEatCnt == shark.size) {
				sharkEatCnt = 0;
				shark.size++;
			}
			shark.x = nx;
			shark.y = ny;
		}
		else {
			sort(eatList.begin(), eatList.end(), cmp);
			int nx = eatList[0].first.first;
			int ny = eatList[0].first.second;
			time += eatList[0].second;
			board[nx][ny] = 0;
			sharkEatCnt++;
			if (sharkEatCnt == shark.size) {
				sharkEatCnt = 0;
				shark.size++;
			}
			shark.x = nx;
			shark.y = ny;
		}
	}
	cout << time << endl;
}
void Solve() {
	Input();
	Solution();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	Solve();
	return 0;
}