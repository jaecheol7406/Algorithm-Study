/*
2
4 3 2 1 0 4 3 2 1
1 2 3 4 1 2 3 4 0
��: 46

9
1 2 4 3 0 2 1 0 3
1 2 1 2 0 0 0 0 1
3 4 2 3 1 2 3 4 0
0 1 2 3 4 2 1 0 0
0 0 0 0 0 0 1 4 4
0 4 0 4 0 4 0 4 0
0 4 2 2 2 2 2 2 2
1 1 1 1 1 1 1 1 0
0 2 0 3 0 1 0 2 0
��: 89
������
1. ���� idx�� 0���� ����Ѵٸ� '��'�� ��� �ִ� ���¸� 0���� �����ϸ� �� ��
*/
#include <iostream>
using namespace std;

int N;
int map[50][9];
int used[9];
int seq[9];

void Input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> map[i][j];
		}
	}
}

int outNum = 0;
int pos[3] = { -1, -1, -1}; // �� �翡 �ִ� Ÿ�� ��ȣ. -1: ��� ����
int idx = 0; // �̹��� ���� ĥ Ÿ��= seq[idx]
int tmpScore = 0;
int maxScore = 0;

void Hit(int inn) {
	// cout << "�̹� ���� " << seq[idx] << " ���: " << map[inn][seq[idx]] << endl;
	if (map[inn][seq[idx]] == 0) { // �ƿ�
		outNum++;
	}
	else if (map[inn][seq[idx]] == 1) { // ��Ÿ
		if (pos[2] != -1) {
			tmpScore++;
			pos[2] = -1;
		}
		for (int i = 2; i >= 1; i--) {
			pos[i] = pos[i - 1]; // 1ĭ�� ����
		}
		pos[0] = idx;
	}
	else if (map[inn][seq[idx]] == 2) { // 2��Ÿ
		for (int i = 1; i < 3; i++) {
			if (pos[i] != -1) {
				tmpScore++;
				pos[i] = -1;
			}

			pos[2] = pos[0];
			pos[1] = idx;
		}
	}
	else if (map[inn][seq[idx]] == 3) { // 3��Ÿ
		for (int i = 0; i < 3; i++) {
			if (pos[i] != -1) {
				tmpScore++;
				pos[i] = -1;
			}
		}

		pos[2] = idx;
	}
	else if (map[inn][seq[idx]] == 4) { // Ȩ��
		for (int i = 0; i < 3; i++) {
			if (pos[i] != -1) {
				tmpScore++;
				pos[i] = -1;
			}
		}
		tmpScore++;
	}

	/*cout << "�� ������Ȳ: ";
	for (int i = 0; i < 3; i++) {
		cout << pos[i] << " ";
	}
	cout << endl;*/

	idx = (idx + 1) % 9;
}
void DFS(int cnt) {
	if (cnt >= 9) {
		/*for (int i = 0; i < 9; i++) {
			cout << seq[i] << " ";
		}
		cout << endl;*/
		idx = 0;
		tmpScore = 0;
		
		for (int inn = 0; inn < N; inn++) {
			//cout << "�̹� �̴�: ";
			/*for (int i = 0; i < 9; i++) {
				cout << map[inn][seq[i]] << " ";
			}
			cout << endl;*/
			// cout << "inning " << inn << "=============" << endl;
			outNum = 0;
			for (int i = 0; i < 3; i++) { // �̴��� ���۵� �� ���ڴ� ����
				pos[i] = -1;
			}

			while (outNum < 3) {
				Hit(inn); //Ÿ�� �ٲ�� �� ġ�� �޸���
			}
			//cout << inn << "�� �̴� ���: " << tmpScore << endl;
		}
		//cout << "tmpScore: " << tmpScore << "============="<< endl;
		if (tmpScore > maxScore) maxScore = tmpScore;

		return;
	}

	for (int i = 1; i <= 8; i++) {
		if (cnt == 3) cnt++;
		if (used[i] == 1) continue;

		seq[cnt] = i;
		used[i] = 1;
		DFS(cnt + 1);

		used[i] = 0;
	}

}

int main() {

	Input();
	seq[3] = 0;

	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < 9; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}*/

	// 1~8�� ���� �ְ� �ߺ� ���� �̴´�
	DFS(0);

	cout << maxScore;

	return 0;
}