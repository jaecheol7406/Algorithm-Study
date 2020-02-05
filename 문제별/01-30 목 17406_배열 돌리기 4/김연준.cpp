#include <iostream>
#include <vector>
#include <algorithm>
#define endl '\n'
using namespace std;

int Map[51][51];
int t_Map[51][51];
int Cal[3][6];
int N, M, K;
const int INF = 987654321;
int ans = INF;
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

vector<int> arr;
bool Select[6];
vector<int> V;
void input() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> Map[i][j];
		}
	}
	for (int i = 0; i < K; i++) {
		cin >> Cal[i][0] >> Cal[i][1] >> Cal[i][2];
		arr.push_back(i);
	}
}
void CopyMap() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			t_Map[i][j] = Map[i][j];
		}
	}
}

void Rotate(int val) {
	int start_x = Cal[val][0] - Cal[val][2];
	int start_y = Cal[val][1] - Cal[val][2];
	int end_x = Cal[val][0] + Cal[val][2];
	int end_y = Cal[val][1] + Cal[val][2];
	int count = (end_x - start_x) / 2;
	for (int i = 0; i < count; i++) {

		int x = start_x;
		int y = start_y;
		int dir = 0;
		int start_value = t_Map[x][y];
		while (true) {
			if (x == start_x && y == start_y && dir == 3)//시작점으로 다시 돌아온경우 
			{
				t_Map[x][y+1] = start_value;
				break;
			}

			if ((x == start_x && y == end_y)||(x == end_x && y == end_y) ||(x==end_x&&y==start_y)) { //밑으로 변경
				dir = dir + 1;
			}
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			t_Map[x][y] = t_Map[nx][ny];
			x = nx;
			y = ny;
		}
		start_x += 1;
		start_y += 1;
		end_x -= 1;
		end_y -= 1;


	}
}
void Print() {
	cout << "-------------------" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << t_Map[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-------------------" << endl;
}
void DFS(int cnt) {
	if (cnt == K) {
		//알고리즘 수행
		CopyMap();
		for (int i = 0; i < V.size(); i++) { //각 순열에 대해서 배열 돌리기
			Rotate(V[i]);
		}
		for (int i = 1; i <= N; i++) { //최소값 탐색
			int sum = 0;
			for (int j = 1; j <= M; j++) {
				sum += t_Map[i][j];
			}
			ans = min(ans, sum);

		}
	}
	for (int i = 0; i < K; i++) {
		if (Select[i] == true)
			continue;
		Select[i] = true;
		V.push_back(arr[i]);
		DFS(cnt + 1);
		V.pop_back();
		Select[i] = false;
	}

}
void solve() {
	input();
	DFS(0);
	cout << ans << endl;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();

	return 0;
}