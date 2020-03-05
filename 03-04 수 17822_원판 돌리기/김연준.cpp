/*
BOJ 17822��: ���� ������
���� ���� : �ùķ��̼�

���� Ǯ�� : 1. ������ ������. (�̶�, �Է¹��� x�� ����� �����ϴ� ���� ��� ��������)
            2. ������ ���� �ִ��� ã�´�.
			   -> ���ܻ���) �� ������ ù��° ��, ������ ��,  ù��° ����, ������ ������ ���ܻ����̹Ƿ� ���� ó���Ѵ�.
			   ->������ �� ��� tmp�迭(�ӽ� ���� �迭)�� 0(������ ���� �ǹ�)�� ����, �ƴ϶�� �� �� �״�� ���� (flag������ ������ ��찡 �ִ��� üũ)
			   ->����, ������ ���� �ƿ� ���� ����� ���� ����ȯ(�Ҽ����� �ִ� ��찡 �����Ƿ�)�� ���� ��� ���� ���Ѵ�.
			   ->recovery_map()�Լ����� tmp�迭�� �ִ� ������Ʈ �� ������ ���� �������� �����.
*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
struct command {
	int x; //���� ��ȣ
	int d; // ����(0�̸� �ð�, 1�̸� �ݽð�)
	int k; // ��ĭ ȸ��
};
int N, M, T;
int board[51][51];
int tmp[51][51];
vector<command>  command_list;
void Input() {
	cin >> N >> M >> T;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 0; i < T; i++) {
		command cmd;
		cin >> cmd.x >> cmd.d >> cmd.k;
		command_list.push_back(cmd);
	}
}
void rotate(int x,int d,int k) {
	for (int i = 0; i < k; i++) { //k�� ����
		if (d == 0) { //�ð����
			int tmp = board[x][M - 1];
			for (int j = M - 1; j >= 1; j--) {
				board[x][j] = board[x][j - 1];
			}
			board[x][0] = tmp;
		}
		else { //�ݽð����
			int tmp = board[x][0];
			for (int j = 0; j < M-1; j++) {
				board[x][j] = board[x][j + 1];
			}
			board[x][M - 1] = tmp;
		}
	}
}
void check_adj() { //������ �� ã��
	memset(tmp, 0, sizeof(tmp));
	bool flag = false;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == 0) { //0�̸� ������ �� �̹Ƿ� ������ �� ã�� ���ص��ȴ�.
				tmp[i][j] = 0;
				continue;
			}
			if (j == 0) { //�� ������ ù��° ��
				if (board[i][j] == board[i][M - 1] || board[i][j] == board[i][1]) { //�ι�°���� ������ ���� ���ؾ���
					tmp[i][j] = 0;
					flag = true;
					continue;
				}
			}
			else if (j == M - 1) { //�� ������ ������ ��
				if (board[i][j] == board[i][0] || board[i][j] == board[i][M - 2]) { //ù��°���� ������ �� ���� ���ؾ���
					tmp[i][j] = 0;
					flag = true;
					continue;
				}
			}
			else {
				if (board[i][j] == board[i][j - 1] || board[i][j] == board[i][j + 1]) { //�ƴϸ� -1,+1���� ��
					tmp[i][j] = 0;
					flag = true;
					continue;
				}
			}
			if (i == 1) { //ù��° ������ ���
				if (board[i][j] == board[i + 1][j]) { //�ι��� ������ ������ ���� ��
					tmp[i][j] = 0;
					flag = true;
					continue;
				}
			}
			else if (i == N) {
				if (board[i][j] == board[i - 1][j]) { //������ ������ ��� ������ �� ���ǰ��� ������ ���� ��
					tmp[i][j] = 0;
					flag = true;
					continue;
				}
			}
			else {
				if (board[i][j] == board[i + 1][j] || board[i][j] == board[i - 1][j]) { //�ƴ϶�� �� ����, ���� ���ǰ� ��
					tmp[i][j] = 0;
					flag = true;
					continue;
				}
			}
			tmp[i][j] = board[i][j];
		}
	}
	int sum = 0;
	int cnt = 0;
	if (!flag) { //������ ���� ���ٸ�
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < M; j++) {
				if (tmp[i][j] == 0)
					continue;
				sum += tmp[i][j];
				cnt++;
			}
		}
		float avg = (float)sum / cnt; //��հ�
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < M; j++) {
				if (tmp[i][j] == 0)
					continue;
				if (tmp[i][j] > avg)
					tmp[i][j]--;
				else if(tmp[i][j]<avg)
					tmp[i][j]++;
			}
		}
	}
}
void recovery_map() { //���� ������Ʈ
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			board[i][j] = tmp[i][j];
		}
	}
}
void Print() {
	int sum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			sum += board[i][j];
		}
	}
	cout << sum << endl;
}
void Solution() {
	for (int i = 0; i < command_list.size(); i++) {
		
		int x = command_list[i].x;
		int d = command_list[i].d;
		int k = command_list[i].k;
		for (int j = x; j <= N; j += x) {//x�� ��� ���� ������
			rotate(j, d, k);
		}
		check_adj(); //������ ��� Ȯ���ϱ�
		recovery_map(); //���� ������Ʈ
	}
	Print();
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