/*
BOJ 14890��: ����
���� ���� : �ùķ��̼�
���� Ǯ�� : �� ���� ��, �Է� ���� �迭�� ��� ���� �ٲ㼭 board [N~2N]���� �������ش�.
            [���� ĭ�� ���̰� ���� ���]
				--> ���� ĭ���� L���̸�ŭ�� ���̰� ���ӵ��� Ȯ��
			[���� ĭ�� ���̰� ū ���]
			   --> �ݺ����� ���� ���ӵ� ���̸� ī��Ʈ�� cnt������ L���� ũ�ٸ� ���θ� ���� �� �ִ�.
			[���� ĭ�� ���̰� ���� ���]
			   -->���ӵ� ���ϱ� ī�����Ѵ�.
*/
#include <iostream>
#include <algorithm>
using namespace std;
int N, L;
int board[200][105];
void Input() {
	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = N; i < N * 2; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = board[j][i - N];
		}

	}
}
bool Check_Runway(int x, int y) {
	int val = board[x][y + 1];
	for (int i = y + 2; i < y + L+1; i++) {
		if (y > N) {
			return false;
		}
		if (board[x][i] != val) {
			return false;
		}
	}
	return true;
}
void Solution() {
	int answer = 0;
	for (int i = 0; i < 2*N; i++) {
		bool flag = true;
		int cnt = 1;
		for (int j = 0; j < N-1; j++) {
			if (abs(board[i][j] - board[i][j + 1]) > 1) { //���̰� 1���� ũ�� ���� ����.
				flag = false;
				break;
			}
			if (board[i][j] == board[i][j + 1]) { //���� ���� ��� ī����
				cnt++;
				continue;
			}
			if (board[i][j + 1] > board[i][j]) {
				if (cnt >= L) {
					cnt = 1;
					//continue;
				}
				else {
					flag = false;
					break;
				}
			}
			else {
				if (Check_Runway(i, j)==true) {
					cnt = 0;
					j = j + L-1;
					continue;
					
				}
				else {
					flag = false;
					break;
				}

			}
		}
		if (flag == true) {
			//cout << "HI : " << i << endl;
			answer++;
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