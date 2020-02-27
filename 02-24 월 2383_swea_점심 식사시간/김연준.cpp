/*
Swea 2383: ���� �Ļ�ð�

1. ����� 2���̹Ƿ� �ߺ������� ����� ������� 1 or 2�� �����ϰ� ��. (ó���� ������ ����ؼ� �ð��ʰ� �߻�)
2. 1�� ����� ������ ������ 1�� ��ܰ��� �Ÿ��� ���� ���Ϳ� ����, 2�� ����� ������ ������ 2�� ��ܰ��� �Ÿ��� ���� ���Ϳ� ����.
3. ��� �Ա��� ������ �ð��̸� �ش� ����� ��� ť�� ����� �Ÿ��� �־��ش�.
4. 1�ʸ��� ��� ť�� ������ 1�� ���ҽø鼭 0�� �ȴٸ� �̵� �Ϸ� �� ������ �Ǵ�.
    ==>���⼭ ��ܿ��� �ִ� 3�� �̵��� �� �����Ƿ� ��� ť�� 3������� 1�� ���ҽ�Ű�� �� �ڿ� ������ ���ҽ�Ű�� �ʴ´�.
	==>�̵� �Ϸ�� ����� ������ �̵� �Ϸ�� ����� �ο�(�ִ� 3��)��ŭ�� ���� 1�� ���ҽ��Ѽ� �����δ�.
	==> �� �κп��� ������ �ظ���.
5. �Ÿ��� �������� ���Ϳ� ��� ť���� ���� ������� �������ش�.
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
vector<loc> peoples; //����� ��ǥ
vector<loc> stairs; //����� ��ǥ�� ����
vector<int> dis1; //1�� ����� ������ ������� 1�� ��ܱ����� �Ÿ�
vector<int> dis2; //2�� ����� ������ ������� 2�� ��ܱ����� �Ÿ�
queue<int> stair1; //1�� ����� ���� 
queue<int> stair2; //2�� ����� ����
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
		if (Select[i] == 0) { //1�� ����� ������ ���
			int dis = abs(peoples[i].x - stairs[0].x) + abs(peoples[i].y - stairs[0].y);
			dis1.push_back(dis); //�� ����� 1�� ��ܰ��� �Ÿ��� ����
		}
		else if (Select[i] == 1) { //2�� ����� ������ ���
			int dis = abs(peoples[i].x - stairs[1].x) + abs(peoples[i].y - stairs[1].y);
			dis2.push_back(dis); //�� ����� 2�� ��ܰ��� �Ÿ��� ����
		}
	}

	sort(dis1.begin(), dis1.end());  //�̵��Ÿ��� �����Ѵ�.
	sort(dis2.begin(), dis2.end());
}
void Solution() {
	Init();//����� �� ���� �ʱ�ȭ
	getDistancePeopleToStairs();
	int time = 0;
	while (true) {
		//��� ��������
		int stair1_size = stair1.size();
		for (int i = 0; i < stair1_size; i++) { //1�� ��� ��������
			int cur = stair1.front();
			stair1.pop();
			if (i < 3) { //3��° ��������� �̵��Ѵ�
				if (cur != 0) {
					stair1.push(--cur);
				}
			}
			else { 
				if (cur != 0) { 
					if (stair1.size() < 3) { //3��° ����� �ƴϾ����� �� ����� �� �������� 3��° ����ȿ� ������ ����� ��������.
						stair1.push(--cur);
					}
					else { //3��° ����� �ƴϾ����� �������� ����
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

		//��� �Ա� ����
		while (true) { //1�� ��� case
			if (dis1.size() == 0)
				break;
			if (dis1[0] == time) { //��� �Ա����� �̵��ߴٸ�
				stair1.push(stairs[0].len); //1�� ��� ��� ť�� �־���.
				dis1.erase(dis1.begin() + 0); //�־����� �� ����� �Ÿ��� ����.
			}
			else
				break;
		}
		while (true) { //2�� ��� case
			if (dis2.size() == 0)
				break;
			if (dis2[0] <= time) {
				stair2.push(stairs[1].len);
				dis2.erase(dis2.begin());
			}
			else
				break;
		}
		//��������
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