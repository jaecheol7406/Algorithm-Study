/*
BOJ 15685��: �巡�� Ŀ��
���� ���� : �ùķ��̼�

1. K���� �巡�� Ŀ���� ������( K-1���� �巡�� Ŀ�갡 ������ ���� + �� ������� ������ (+1%4)������ ���� �� �� �Ǵ� ��Ģ�� ������.  (��α� ����..)
2. ���� 0���븦 �׸��� 0������ ������ �������� ���� ������ �巡�� Ŀ�긦 ����.
3. �� ������ �巡�� Ŀ���� ���� visit�迭�� üũ�ϰ�, ��� �巡��Ŀ�긦 ���ϰ�,  100x100 �迭�� ��ȸ�ϸ鼭 ������ ���Ѵ�.

���� ���� ���� ������� ������

�ٽ� �ѹ� Ǯ���
*/
#include <iostream>
#include <vector>
using namespace std;
struct curve {
	int x;
	int y;
	int dir;
	int gen;
};
int N;
int board[100][100];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,-1,0,1 };
bool visit[101][101];
vector<curve> curve_list;
vector<int> dir_list;
int x, y;
void Input() {
	cin >> N;
	curve input;
	for (int i = 0; i < N; i++) {
		cin >> input.x >> input.y >> input.dir >> input.gen;
		curve_list.push_back(input);
	}
}
void nextCurve() {
	int size = dir_list.size();
	for (int i = size-1; i >= 0; i--) {
		int nd = dir_list[i];
		nd = (nd + 1) % 4;
		x += dx[nd];
		y += dy[nd];
		visit[y][x] = true;
		dir_list.push_back(nd);
	}
}
int getAnswer() {
	int result = 0;
	for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 100; j++) {
			if (visit[i][j] && visit[i][j + 1] && visit[i + 1][j] && visit[i + 1][j + 1])
				result++;
		}
	}
	return result;
}
void Solution() {
	for (int i = 0; i < N; i++) {
		dir_list.clear();
		//0����
		x = curve_list[i].x;
		y = curve_list[i].y;
		visit[y][x] = true;
		x = x + dx[curve_list[i].dir];
		y = y + dy[curve_list[i].dir];
		visit[y][x] = true;
		dir_list.push_back(curve_list[i].dir);
		for (int j = 0; j < curve_list[i].gen; j++) {
			//���� ���� �׸���
			nextCurve();
		}
	}
	cout << getAnswer() << endl;
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