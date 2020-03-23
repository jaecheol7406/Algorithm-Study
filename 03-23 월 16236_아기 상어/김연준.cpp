/*
BOJ 16236��: �Ʊ� ���


�߸�����: 1. BFS�� ó�� �湮�� ����⸦ ������ �Ǵ� ������ ���� -> ���� �� �ִ� ����� ���� �����Ͽ� ���ǿ� �°� ���� ����⸦ �����ؾ���
		  2. eatList�� size�� 0�� ��쿡�� BFS�Լ� ������ 0��° �ε����� �����ؼ� ��Ÿ�ӿ��� �߻�
				-> eatList�� ���������� �ٲٰ�, while�� ���� ���� 

���� Ǯ�� : 1. BFS�� ����ؼ� ���� �� �ִ� ������ Ȯ���Ѵ�.
				(1) ���� �� �ִ� ����Ⱑ �����ϸ� vector�� �����Ѵ�.
			2. ���� �� �ִ� ������� ���� 0���� 1���� 2�̻����� Ȯ���Ѵ�.
				(1) 0�̸� ����
				(2) 1�̸� ���� �� �ִ� ������� ����Ʈ�� eatList[0]�� �����Ͽ� ��� �԰� �׿� ���� ���� ����
				(3) 2�̻��̸� ���� �� �ִ� ������� ����Ʈ�� �Ÿ�->x��->y�� ������ sort�Ѵ�.
			3. ��� ����
����� ���� : Solution()���� ���� ���� ����
				->eatFish() (BFS�Լ�) -> eatList�� size�� ���� ���ǹ� ���� 
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
			<!-- �߸����� 1 -->
			if (board[nx][ny]>0 &&board[nx][ny] < shark.size) { //��� �Դ´�
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
	<!-- �߸����� 2 -->
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
	<!-- �߸����� 2 -->
	while (true) {
		//cout << time << endl;
		if (fishNum==0 || checkFinish())
			break;
		//else if (fishNum == 1) {

		//}
		else {
			//���� ����� ����⸦ ������ ����.
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