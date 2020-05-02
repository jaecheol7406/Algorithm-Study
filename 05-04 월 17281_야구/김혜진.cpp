/*
function call: main -> Input -> (DFS -> Hit) -> main

1. 순열로 타순을 정한다.
2. 3아웃 당하기 전까지 진루한다

주의점
1. 선수 idx를 0부터 사용한다면 '루'에 비어 있는 상태를 0으로 정의하면 안 됨
2. 진루할 때 코드 잘못 작성한 부분 찾는 데 오래걸렸음
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
int pos[3] = { -1, -1, -1}; // 각 루에 있는 타자 번호. -1: 비어 있음
int idx = 0; // 이번에 공을 칠 타자= seq[idx]
int tmpScore = 0;
int maxScore = 0;

void Hit(int inn) {
	if (map[inn][seq[idx]] == 0) { // 아웃
		outNum++;
	}
	else if (map[inn][seq[idx]] == 1) { // 안타
		if (pos[2] != -1) {
			tmpScore++;
			//pos[2] = -1;
		}
		for (int i = 2; i >= 1; i--) {
			pos[i] = pos[i - 1]; // 1칸씩 전진
		}
		pos[0] = idx;
	}
	else if (map[inn][seq[idx]] == 2) {
		for (int i = 1; i < 3; i++) {
			if (pos[i] != -1) {
				tmpScore++;
				pos[i] = -1;
			}
		}
		pos[2] = pos[0];
		pos[0] = -1; // 간과한 부분
		pos[1] = idx;
	}
	else if (map[inn][seq[idx]] == 3) { // 3루타
		for (int i = 0; i < 3; i++) {
			if (pos[i] != -1) {
				tmpScore++;
				pos[i] = -1;
			}
		}

		pos[2] = idx;
	}
	else if (map[inn][seq[idx]] == 4) { // 홈런
		for (int i = 0; i < 3; i++) {
			if (pos[i] != -1) {
				tmpScore++;
				pos[i] = -1;
			}
		}
		tmpScore++;
	}

	idx = (idx + 1) % 9;
}
void DFS(int cnt) {
	if (cnt >= 9) {
		idx = 0;
		tmpScore = 0;
		
		for (int inn = 0; inn < N; inn++) {
			outNum = 0;
			for (int i = 0; i < 3; i++) { // 이닝이 시작될 때 주자는 없다
				pos[i] = -1;
			}

			while (outNum < 3) {
				Hit(inn); //타자 바뀌고 공 치고 달리기
			}
		}
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

	// 1~8를 순서 있게 중복 없이 뽑는다
	DFS(0);

	cout << maxScore;

	return 0;
}