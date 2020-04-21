/*
BOJ 17779��: �Ը��Ǵ���2
���� ���� : �ùķ��̼�
main() -> Solve() -> Input() -> Solution() -> divide() -> getBoundary()

1. ������ ���ǿ� �´� x,y,d1,d2 ��� ����� ���� Ȯ���Ͽ� ������ �����Ѵ�.
2. ��輱�� ���Ѵ�.
	(1) 1,4�� ��輱�� (+1,-1)�� ���� ��Ģ�̰�, 2,3�� ��輱�� (+1,+1)�� ���� ��Ģ�̹Ƿ� ���� �ݺ��� �ȿ��� ���Ѵ�.
3. 5�� ���ű��� �̸� ���Ѵ�.
	(1) ��輱�� (x,y)�� (x+d1+d2,y-d1+d2) �� ���� ������ 5�� ���ű��� ���� ��Ģ�� ����.
	(2) ���� ���϶�, ��輱�� ������ �������� �ٽ� ������ ���������� 5�� �����̹Ƿ� 5�� ���ű��� �̸� ���Ѵ�.
4. ��ü ���� ��ȸ�ϸ鼭, 5�������̶�� 5�� ���� �α����� ���ϰ�, �ƴ϶�� �� ���ű� ���ǿ� �´� ������ �α����� ����.

*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int N;
int board[21][21];
int district[21][21];
int people_count[6];
int answer = 987654321;
void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}
}
void getBoundary(int x, int y, int d1, int d2) {
	for (int i = 0; i <= d1; i++) { //1,4�� ���
		district[x + i][y - i] = 5;
		district[x + d2 + i][y + d2 - i] = 5;
	}
	for (int i = 0; i <= d2; i++) { //2,3�� ���
		district[x + i][y + i] = 5;
		district[x + d1 + i][y - d1 + i] = 5;
	}
}
void divide(int x, int y, int d1, int d2) {
	//��輱 ���ϱ�.
	getBoundary(x,y,d1,d2);
	//5�� ���ű� ���ϱ�
	for (int i = x + 1; i <= x + d1 + d2 - 1; i++) {
		bool flag = false;
		for (int j = y - d1; j <= y + d2; j++) {
			if (district[i][j] == 5 && !flag) {
				flag = true;
				continue;
			}
			else if (district[i][j] == 5 && flag)
				break;
			if (flag)
				district[i][j] = 5;
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (district[i][j] == 5)
				people_count[5] += board[i][j];
			else {
				if (i < x + d1 && j <= y)
					people_count[1] += board[i][j];
				else if (i <= x + d2 && y < j)
					people_count[2] += board[i][j];
				else if (x + d1 <= i && j < y - d1 + d2)
					people_count[3] += board[i][j];
				else if (x + d2 < i && y - d1 + d2 <= j)
					people_count[4] += board[i][j];
			}
		}
	}
	sort(people_count + 1, people_count + 6);
	answer = min(answer, people_count[5] - people_count[1]);
}
void Solution() {
	for (int x = 1; x <= N; x++) {
		for (int y = 2; y <= N; y++) {
			for (int d1 = 1; d1 <= N; d1++) {
				if (y-d1<1)
					break;
				for (int d2 = 1; y+d2 <= N; d2++) {
					if (x + d1 + d2 > N)
						break;
					memset(district, 0, sizeof(district));
					memset(people_count, 0, sizeof(people_count));
					divide(x, y, d1, d2);
				}
			}
		}
	}
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