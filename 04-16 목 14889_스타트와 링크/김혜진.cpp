/*
function call: main -> Input -> (DFS <-> Count) -> main

1. 1 ~ N의 숫자 중 N/2개를 조합으로 뽑는다.
2. 각 뽑힌 조합 내부에서, 뽑힌 숫자 N/2개 중 2개씩 순열로 뽑아 score로 저장한다.
3. score[i] 와 score[score개수 - 1 - i] 가 서로 겹치지 않게 뽑은 것이므로 서로 다른 팀이게 된다.
   따라서 abs(score[i] - score[score개수 - 1 - i] 중 가장 작은 값을 출력한다.
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
	if (picked.size() >= N / 2) { // cnt 매개변수 대신 벡터 사용
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