/*
function call: main -> Input -> (DFS <-> Count) -> main

1. 1 ~ N�� ���� �� N/2���� �������� �̴´�.
2. �� ���� ���� ���ο���, ���� ���� N/2�� �� 2���� ������ �̾� score�� �����Ѵ�.
3. score[i] �� score[score���� - 1 - i] �� ���� ��ġ�� �ʰ� ���� ���̹Ƿ� ���� �ٸ� ���̰� �ȴ�.
   ���� abs(score[i] - score[score���� - 1 - i] �� ���� ���� ���� ����Ѵ�.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int map[30][30];
vector<int> picked;
vector<int> score;

void Input() {
	scanf("%d\n", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
}

int teamStart[15];
void Count() {
	int tmpSum = 0;
	for (int i = 0; i < picked.size(); i++) {
		for (int j = 0; j < picked.size(); j++) {
			if (i != j) {
				// cout << picked[i] << picked[j] << "(" << map[picked[i]][picked[j]] << ") ";
				tmpSum += map[picked[i]][picked[j]];
			}
		}
		// cout << endl;
	}
	score.push_back(tmpSum);
}

void DFS(int pre) {
	if (picked.size() >= N / 2) { // cnt �Ű����� ��� ���� ���
		/*for (int i = 0; i < picked.size(); i++) {
			cout << picked[i] << " ";
		}
		cout << endl;*/
		Count();
		return;
	}

	for (int i = pre + 1; i <= N; i++) {
		picked.push_back(i);
		DFS(i);
		picked.pop_back();
	}
}

int main() {

	Input();

	DFS(0);

	int tmpMin = 0;
	int MinValue = 9000;

	for (int i = 0; i < score.size() / 2; i++) {
		tmpMin = abs(score[i] - score[score.size() - 1 - i]);
		if (tmpMin < MinValue) MinValue = tmpMin;
	}

	cout << MinValue;

	return 0;
}