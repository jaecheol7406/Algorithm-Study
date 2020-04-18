/*
BOJ 17140: ������ �迭�� ����
------------------------------------------------------------------------
3x3 �迭 A
R ���� : �迭 A�� ��� �࿡ ���ؼ� ���� ����. �� ����>= �� ������ ��� ����
C ���� : �迭 A�� ��� ���� ���ؼ� ���� ����. �� ���� < �� ������ ��� ����
���� Ƚ�� ������ ���� ���� Ƚ���� ������ ���� ũ�� ������ ����
-----------------------------------------------------------------------------
���� �� �� �Ǵ� ���� ���� ���� ����Ƚ���� �����ϴ� �ڷᱸ���� vector<num>�� ����Ͽ���.
ó���� hashmap�� ����ؼ� �Ϸ��ߴµ� ������ �ȵǴ� �̽��� vector<num>���� ����. num�� struct�� ���� ����Ƚ���� ����.

���� : 1.  �� ��Ǵ� ���� ���ؼ� nums���Ϳ� ���� �� ���� ����Ƚ���� �����Ѵ�.
       2.  nums�迭�� ���ҵ��� �����ϴµ�, ����Ƚ���� ������ ���� ���� ���� �ƴ϶�� ����Ƚ���� ���� ����
	   2.  nums.size()*2 �� 100�� �Ѵ��� �ƴ��� ���Ѵ�. (nums.size()*2�� nums�� ���Ұ� �� ���� ���� ����Ƚ���� �����ϹǷ� size�� ���ϱ� 2�� ���ش�.)
	   3.  ������ �迭�� 0���� ������ �� ���� �� ���� �迭�� �־��ش�.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int result;
int r, c, k;
int row_num = 3;
int col_num = 3;
int   arr[101][101];
struct num {
	int val; //��
	int cnt;//����Ƚ��
};

vector<num> nums; //��or�� Ž�� �߿� �� ��or���� ���� ����Ƚ���� ����
				  //�ؽø� ����
bool cmp(num a, num b) {
	if (a.cnt == b.cnt)
		return a.val < b.val;
	return a.cnt < b.cnt;
}
void Input() {
	memset(arr, 0, sizeof(arr));
	cin >> r >> c >> k;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> arr[i][j];
		}
	}
}
void rCalc() {
	int flag;
	int max_col = 0;
	for (int i = 1; i <= row_num; i++) {
		nums.clear();
		for (int j = 1; j <= col_num; j++) {
			if (arr[i][j] == 0) //�迭�� ���� 0�̸� ����
				continue;
			flag = 0;
			for (int k = 0; k < nums.size(); k++) { //nums���Ϳ� �� ���� ���� �����ϴ��� Ž�� 
				if (nums[k].val == arr[i][j]) {     //�����ϸ� ����Ƚ�� ����
					nums[k].cnt++;
					flag = 1;
					break;
				}
			}

			if (flag == 0) {  //�������� ������ �� ���� ����Ƚ�� 1�� ���Ϳ� �߰�
				nums.push_back(num{ arr[i][j], 1 });
			}
		}
		sort(nums.begin(), nums.end(), cmp); //����Ƚ���� ������ ���� ���� ���� �ƴ϶�� ����Ƚ���� ���� ����

		int nums_iter = 0;
		for (int j = 1; j <= 100; j++) { //�� 0���� �ʱ�ȭ
			arr[i][j] = 0;
		}
		if (nums.size() * 2 > 100) { //�� �Ǵ� ���� ũ�Ⱑ 100�� �Ѿ�� ���
			if (max_col < 100) {
				max_col = 100;
			}
			for (int j = 1; j <= 100; j++) { //���� �� �� ����

				if (j % 2 == 1) { //j�� Ȧ���� ��
					arr[i][j] = nums[nums_iter].val;
				}
				else { //j�� ¦���� ����Ƚ��
					arr[i][j] = nums[nums_iter++].cnt;
				}
			}
		}
		else {
			if (max_col < nums.size() * 2) {
				max_col = nums.size() * 2;
			}
			for (int j = 1; j <= nums.size() * 2; j++) { //�� �ٽ� �ֱ�

				if (j % 2 == 1) {
					arr[i][j] = nums[nums_iter].val;
				}
				else {
					arr[i][j] = nums[nums_iter++].cnt;
				}
			}
		}
	}
	col_num = max_col; //�Լ��� ���������� �� �Ǵ� ���� ���� �ִ밪���� ����

}
void cCalc() {
	int flag;
	int max_row = 0;
	for (int i = 1; i <= col_num; i++) {
		nums.clear();

		for (int j = 1; j <= row_num; j++) {
			if (arr[j][i] == 0)
				continue;
			flag = 0;
			for (int k = 0; k < nums.size(); k++) {
				if (nums[k].val == arr[j][i]) {
					nums[k].cnt++;
					flag = 1;
					break;
				}
			}
			if (flag == 0) {
				nums.push_back(num{ arr[j][i], 1 });
			}
		}
		sort(nums.begin(), nums.end(), cmp);
		int nums_iter = 0;
		for (int j = 1; j <= 100; j++) { //�� 0���� �ʱ�ȭ
			arr[j][i] = 0;
		}
		if (nums.size() * 2 > 100) {
			if (max_row < 100) {
				max_row = 100;
			}
			for (int j = 1; j <= 100; j++) { //�� �ٽ� �ֱ�

				if (j % 2 == 1) {
					arr[j][i] = nums[nums_iter].val;
				}
				else {
					arr[j][i] = nums[nums_iter++].cnt;
				}
			}
		}
		else {
			if (max_row < nums.size() * 2) {
				max_row = nums.size() * 2;
			}
			for (int j = 1; j <= nums.size() * 2; j++) { //�� �ٽ� �ֱ�

				if (j % 2 == 1) {
					arr[j][i] = nums[nums_iter].val;
				}
				else {
					arr[j][i] = nums[nums_iter++].cnt;
				}
			}
		}
	}
	row_num = max_row;

}
void Solution() {
	int time = 0;
	while (true) {
		if (time > 100) {
			cout << "-1" << endl;
			return;
		}
		if (arr[r][c] == k) {
			cout << time << endl;
			return;
		}

		if (row_num >= col_num) {
			rCalc();
		}
		else {
			cCalc();
		}

		time++;
	}
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