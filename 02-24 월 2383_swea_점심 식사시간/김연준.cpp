/*
Swea 2383: 점심 식사시간

1. 계단이 2개이므로 중복순열을 사용해 사람들이 1 or 2를 선택하게 함. (처음에 조합을 사용해서 시간초과 발생)
2. 1번 계단을 선택한 사람들과 1번 계단과의 거리를 구해 벡터에 저장, 2번 계단을 선택한 사람들과 2번 계단과의 거리를 구해 벡터에 저장.
3. 계단 입구에 도착할 시간이면 해당 계단의 대기 큐에 계단의 거리를 넣어준다.
4. 1초마다 대기 큐의 값들을 1씩 감소시면서 0이 된다면 이동 완료 된 것으로 판단.
    ==>여기서 계단에서 최대 3명만 이동할 수 있으므로 대기 큐의 3명까지만 1씩 감소시키고 그 뒤에 값들은 감소시키지 않는다.
	==>이동 완료된 사람이 나오면 이동 완료된 사람의 인원(최대 3명)만큼의 값을 1씩 값소시켜서 움직인다.
	==> 이 부분에서 굉장히 해맸음.
5. 거리를 저장해준 벡터와 대기 큐들이 전부 비었으면 종료해준다.
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define endl '\n'
using namespace std;

int room[11][11];
int N;
const int INF = 987654321;
int result = INF;
int Select[11];
struct loc {
	int x;
	int y;
	int len;
};
vector<loc> peoples; //사람의 좌표
vector<loc> stairs; //계단의 좌표와 길이
vector<int> dis1; //1번 계단을 선택한 사람들의 1번 계단까지의 거리
vector<int> dis2; //2번 계단을 선택한 사람들의 2번 계단까지의 거리
queue<int> stair1; //1번 계단의 정보 
queue<int> stair2; //2번 계단의 정보
void Initialize() {
	memset(room, 0, sizeof(room));
	memset(Select, 0, sizeof(Select));
	peoples.clear();
	stairs.clear();
	result = INF;

}
void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> room[i][j];
			if (room[i][j] == 1) {
				peoples.push_back(loc{ i,j,0 });
			}
			else if (room[i][j] != 0) {
				stairs.push_back(loc{ i,j,room[i][j] });
			}
		}
	}
}
void Init() {
	dis1.clear();
	dis2.clear();
	while (!stair1.empty()) {
		stair1.pop();
	}
	while (!stair2.empty()) {
		stair2.pop();
	}
}
void getDistancePeopleToStairs(){

	for (int i = 0; i < peoples.size(); i++) {
		if (Select[i] == 0) { //1번 계단을 선택한 사람
			int dis = abs(peoples[i].x - stairs[0].x) + abs(peoples[i].y - stairs[0].y);
			dis1.push_back(dis); //그 사람과 1번 계단과의 거리를 저장
		}
		else if (Select[i] == 1) { //2번 계단을 선택한 사람
			int dis = abs(peoples[i].x - stairs[1].x) + abs(peoples[i].y - stairs[1].y);
			dis2.push_back(dis); //그 사람과 2번 계단과의 거리를 저장
		}
	}

	sort(dis1.begin(), dis1.end());  //이동거리를 정렬한다.
	sort(dis2.begin(), dis2.end());
}
void Solution() {
	Init();//경우의 수 마다 초기화
	getDistancePeopleToStairs();
	int time = 0;
	while (true) {
		//계단 내려가기
		int stair1_size = stair1.size();
		for (int i = 0; i < stair1_size; i++) { //1번 계단 내려가기
			int cur = stair1.front();
			stair1.pop();
			if (i < 3) { //3번째 사람까지만 이동한다
				if (cur != 0) {
					stair1.push(--cur);
				}
			}
			else { 
				if (cur != 0) { 
					if (stair1.size() < 3) { //3번째 사람이 아니었지만 앞 사람이 다 내려가서 3번째 사람안에 들어오면 계단을 내려간다.
						stair1.push(--cur);
					}
					else { //3번째 사람이 아니었으면 내려가지 않음
						stair1.push(cur);
					}
				}

			}
		}
		int stair2_size = stair2.size();
		for (int i = 0; i < stair2_size; i++) {
			int cur = stair2.front();
			stair2.pop();
			if (i < 3) {
				if (cur != 0) {
					stair2.push(--cur);
				}
			}
			else {
				if (cur != 0) {
					if (stair2.size() < 3) {
						stair2.push(--cur);
					}
					else {
						stair2.push(cur);
					}
				}

			}
		}

		//계단 입구 도착
		while (true) { //1번 계단 case
			if (dis1.size() == 0)
				break;
			if (dis1[0] == time) { //계단 입구까지 이동했다면
				stair1.push(stairs[0].len); //1번 계단 대기 큐에 넣어줌.
				dis1.erase(dis1.begin() + 0); //넣었으면 그 사람의 거리는 삭제.
			}
			else
				break;
		}
		while (true) { //2번 계단 case
			if (dis2.size() == 0)
				break;
			if (dis2[0] <= time) {
				stair2.push(stairs[1].len);
				dis2.erase(dis2.begin());
			}
			else
				break;
		}
		//종료조건
		if (dis1.empty() && dis2.empty() && stair1.empty() && stair2.empty()) {
			if (result > time) {
				result = time;
			}
			break;
		}
		time++;
	}

}
void DFS(int cnt) {
	if (cnt == peoples.size()) {
		Solution();
		return;
	}

	for (int i = 0; i < 2; i++) {
		Select[cnt] = i;
		DFS(cnt + 1);
	}
}
void Solve() {
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Initialize();
		Input();
		DFS(0);
		cout << "#" << i << " " << result << endl;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}