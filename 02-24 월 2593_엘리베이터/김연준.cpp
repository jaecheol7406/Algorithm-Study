/*
Æ²·È½À´Ï´Ù.
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int N, M;
bool selected_ele[101];
vector<int> eleToFloor[150];
vector<int> floorToEle[100100];
int start_floor, end_floor;
const int INF = 987654321;
int result = INF;
struct list_info {
	int ele;
	int cnt;
	vector<int> list_ele;
};
queue<list_info> que;

void Input() {
	cin >> N >> M;
	int x, y;
	for (int i = 1; i <= M; i++) {
		cin >> x >> y;
		for (int j = x; j <= N; j += y) {
			eleToFloor[i].push_back(j);
			floorToEle[j].push_back(i);
		}
	}
	cin >> start_floor >> end_floor;
}
void BFS() {
	for (int i = 0; i < floorToEle[start_floor].size(); i++) {
		int flag = 0;
		for (int j = 0; j < floorToEle[end_floor].size(); j++) {
			if (floorToEle[start_floor][i] == floorToEle[end_floor][j])
				flag = 1;
		}
		if (flag == 1) {
			result = 1;
			cout << "1" << endl;
			cout << floorToEle[start_floor][i] << endl;
			return;
		}
		vector<int> t;
		t.push_back(floorToEle[start_floor][i]);
		que.push(list_info{floorToEle[start_floor][i],1,t });
		//que.push(make_pair(floorToEle[start_floor][i],1));
		selected_ele[floorToEle[start_floor][i]] = true;
	}
	while (!que.empty()) {
		list_info cur = que.front();
		que.pop();
		int now_ele = cur.ele;
		int now_cur = cur.cnt;
		vector<int> now_list = cur.list_ele;

		for (int i = 0; i < eleToFloor[now_ele].size(); i++) {
			int n_floor = eleToFloor[now_ele][i];
			if (n_floor == end_floor) {
				if (result > now_cur) {
					result = now_cur;
				}
				cout << now_cur << endl;
				for (int j = 0; j < now_list.size(); j++) {
					cout << now_list[j] << endl;
					
				}
				return;
			}
			else {
				for (int j = 0; j < floorToEle[n_floor].size(); j++) {
					int n_ele = floorToEle[n_floor][j];
					if (selected_ele[n_ele] == true) {
						continue;
					}
					now_list.push_back(n_ele);
					//que.push(make_pair(n_ele, cur.second + 1));
					selected_ele[n_ele] = true;
					que.push(list_info{ n_ele,now_cur + 1,now_list });
				}
			}


		}

	}
}
void Solve() {
	Input();
	BFS();
	if (result == INF) {
		cout << "-1" << endl;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();

	return 0;
}