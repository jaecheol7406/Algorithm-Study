/*
BOJ 15662��: ��Ϲ���(2)
���� ���� : �ùķ��̼�

<���� Ǯ��>
1. ȸ����Ű�� ��Ϲ����� ��������, �����ʿ� �ִ� ��Ϲ������� ������ ���Ͽ� dir�迭�� ����
2. ȸ����Ű�� ��Ϲ����� ��������, ���ʿ� �ִ� ��Ϲ������� ������ ���Ͽ� dir �迭�� ����
3. 1,2�� ���߿� ȸ������ �ʴ� ��Ϲ����� �߰��ϸ� return�Ͽ� ������ ������ �ʴ´�.(������ 0���� ����)
4. ��Ϲ����� ȸ�� ��Ų��. dir�� 0�̸� ȸ������ �ʰ� 1�̸� �ð�, -1�̸� �ݽð�
5. ��� ����.
*/
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
int T,K;
int gear[1001][8];
int dir[1001];
vector<pair<int, int>> cmd;
void Input() {
	cin >> T;
	for (int i = 1; i <= T; i++) {
		string input;
		cin >> input;
		for (int j = 0; j < input.size(); j++) {
			gear[i][j] = input[j]-'0';
		}
	}
	cin >> K;
	for (int i = 0; i < K; i++) {
		int num, dir;
		cin >> num >> dir;
		cmd.push_back(make_pair(num, dir));
	}
}
void rotateRightGear(int nowGear, int nowDir) {
	for (int i = nowGear; i < T; i++) {
		if (gear[i][2] != gear[i + 1][6]) {
			dir[i + 1] = nowDir * -1;
		}
		else
			return;
		nowDir = nowDir * -1;
	}
}
void rotateLeftGear(int nowGear, int nowDir) {
	for (int i = nowGear; i > 1; i--) {
		if (gear[i][6] != gear[i - 1][2]) {
			dir[i - 1] = nowDir * -1;
		}
		else
			return;
		nowDir = nowDir * -1;
	}
}
void rotate() {
	for (int i = 1; i <= T; i++) {
		if (dir[i] == 0)
			continue;
		else if (dir[i] == 1) { //�ð����
			int tmp = gear[i][7];
			for (int j = 7; j >= 1; j--) {
				gear[i][j] = gear[i][j - 1];
			}
			gear[i][0] = tmp;
		}
		else { //�ݽð����
			int tmp = gear[i][0];
			for (int j = 0; j <= 6; j++) {
				gear[i][j] = gear[i][j + 1];
			}
			gear[i][7] = tmp;
		}
	}
}
void getAnswer() {
	int answer = 0;
	for (int i = 1; i <= T; i++) {
		if (gear[i][0] == 1)
			answer++;
	}
	cout << answer << endl;
}
void print() {
	
	for (int i = 1; i <= T; i++) {
		cout << "ȸ������ : " << dir[i] << endl;
		for (int j = 0; j < 8; j++) {
			cout << gear[i][j] << " ";
		}
		cout << endl;
	}
}
void Solution() {
	for (int i = 0; i < cmd.size(); i++) {
		int nowGear = cmd[i].first;
		int nowDir = cmd[i].second;
		dir[nowGear] = nowDir;
		//������ ȸ�� ���� ���ϱ�
		rotateRightGear(nowGear,nowDir); //1��
		//���� ȸ�� ���� ���ϱ�
		rotateLeftGear(nowGear,nowDir); //2��
		//ȸ���ϱ� 
		rotate();//4��

		//print();
		//�𷺼� �ʱ�ȭ
		memset(dir, 0, sizeof(dir));
	}
	getAnswer(); //5��
}
void Solve() {
	Input();
	Solution();
}
int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	Solve();

	return 0;
}