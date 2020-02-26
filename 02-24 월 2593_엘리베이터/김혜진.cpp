/*
BFS, 메모리초과
*/
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

int N, M;
vector<int> xarr;
vector<int> yarr;
int Start, End;
int thisStair;

vector<vector<int>> ev; // ev[0]은 0번 엘리베이터가 갈 수 있는 층 정보
int maxStair = 1;

void Input() {
	scanf("%d %d\n", &N, &M);
	int x, y;
	for (int i = 0; i < M; i++) {
		scanf("%d %d\n", &x, &y);
		xarr.push_back(x);
		yarr.push_back(y);
	}
	scanf("%d %d", &Start, &End);
	thisStair = Start;

}

void Print() {
	cout << N << " " << M << endl;

	for (int i = 0; i < M; i++) {
		cout << xarr[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < M; i++) {
		cout << yarr[i] << " ";
	}
	cout << endl;

	cout << Start << " " << End << endl;

}
int MIN = 999999;
int lastEv = 9999;

vector<int> sequence;

struct Pos {
	int cnt;
	int pos;
	vector<int> route;
	int visited[110] = { 0, }; // 이미 탄 엘리베이터
};
queue<Pos> q;
int lastStair;

int main() {

	Input();
	// Print();

	Pos start;
	start.cnt = 0; start.pos = Start;
	q.push(start);
	lastStair = Start;

	while (!q.empty()) {
		Pos thisPos = q.front();
		q.pop();
		// cout << thisPos.pos << "층, cnt: " << thisPos.cnt << "=========" << endl;

		if (thisPos.pos == End) { // 종료 조건 (가장 먼저 끝나는 애가 최소)
			MIN = thisPos.cnt;
			for (int i = 0; i < thisPos.route.size(); i++) {
				sequence.push_back(thisPos.route[i]);
			}
			break;
		}

		for (int i = 0; i < M; i++) {
			// i번 엘리베이터를 탈 수 없는 경우
			if ((thisPos.pos - xarr[i]) % yarr[i] != 0) continue; // 해당 층과 연결되어 있지 않다
			if (thisPos.visited[i] == 1) continue; // 이미 사용한 엘리베이터이다
			
			
			lastStair = thisPos.pos;
			// cout << i << "번 엘리베이터 탈 수 있음" << endl;

			// j: 그 엘리베이터를 타고 갈 수 있는 층들
			for (int j = xarr[i]; j <= N; j += yarr[i]) { 
				if (lastStair == j) continue; // 방금 전에 있던 층에 다시 가지 않는다

				if (thisPos.visited[i] == 0) {
					Pos newPos;

					memcpy(newPos.visited, thisPos.visited, 110);
					newPos.visited[i] = 1;

					newPos.cnt = thisPos.cnt + 1;

					for (int i = 0; i < thisPos.route.size(); i++) {
						newPos.route.push_back(thisPos.route[i]);
					}
					newPos.route.push_back(i);

					newPos.pos = j;
					// cout << j << "층 가기" << endl;

					q.push(newPos);
				}
				
			}

		}
	}
	
	

	if (MIN == 999999) {
		cout << -1;
	}
	else {
		cout << MIN << endl;
		for (int i = 0; i < sequence.size(); i++) {
			cout << sequence[i] + 1 << endl;
		}
	}


	return 0;
}