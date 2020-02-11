#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
int N;
int population[12];
const int INF = 987654321;
int answer = INF;
bool vis[12];
bool vis_BFS[12];
vector<vector<int>> adj; //연결 확인을 위한 vector
void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> population[i];
	}
	for (int i = 0; i < N; i++) {
		int areaNum;
		cin >> areaNum;
		vector<int> element;
		element.push_back(areaNum);

		for (int j = 0; j < areaNum; j++) {
			int area;
			cin >> area;
			element.push_back(area);
		}
		adj.push_back(element);
	}

}
bool IsConnect(vector<int> area, bool b) { //BFS탐색을 통해 선거구가 연결되어 있는지 확인.
	memset(vis_BFS, 0, sizeof(vis_BFS));
	queue<int> que;
	que.push(area[0]);
	int cnt = 1;
	vis_BFS[area[0]] = true;
	while (!que.empty()) {
		int cur = que.front();
		que.pop();
		for (int j = 1; j <= adj[cur - 1][0]; j++) {
			if (!vis_BFS[adj[cur - 1][j]] && vis[adj[cur - 1][j]] == b) {
				vis_BFS[adj[cur - 1][j]] = true;
				cnt++;
				que.push(adj[cur - 1][j]);
			}

		}
	}
	if (cnt == area.size())
		return true;
	else
		return false;
}
void Calculate() { //두 선거구에 포함되어 있는 인구 계산
	int area1_people = 0;
	int area2_people = 0;
	for (int i = 1; i <= N; i++) {
		if (vis[i]) {
			area1_people += population[i];
		}
		else
			area2_people += population[i];
	}
	if (answer > abs(area1_people - area2_people))
		answer = abs(area1_people - area2_people);
}
void DFS(int idx,int cnt){
	vector<int> area1, area2; //2개의 구역으로 나누기
	if (cnt >= 1) {  
		for (int i = 1; i <= N; i++) {
			if (vis[i])
				area1.push_back(i);
			else 
				area2.push_back(i);
			
		}
		if (!(area1.size() == 0 || area2.size() == 0 || !IsConnect(area1, true) || !IsConnect(area2, false))) //각 선거구는 적어도 한개의 구역을 포함하는가?
			Calculate();                                                                                      //각 선거구가 연결되어있는가?
	}

	for (int i = idx; i <= N; i++) { //DFS를 사용해서 조합 가능한 모든 경우의 수를 다 본다.
		if (vis[i] == true)
			continue;
		vis[i] = true;
		DFS(i, cnt + 1);
		vis[i] = false;
	}
}
void Solution() {

	DFS(1,0);
	if (answer == INF)
		cout << "-1" << endl;
	else
		cout << answer << endl;
}

void Solve() {
	Input();
	Solution();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();

	return 0;
}