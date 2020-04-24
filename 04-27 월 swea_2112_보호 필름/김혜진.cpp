/*
function call: main -> Input -> (DFS -> Check) -> main

1. 각 행마다 0 또는 1 또는 2를 중복 있게 순열로 뽑는다 (예: W=4면 0000, 0001 ...)
2. 뽑는 것과 `동시에` 해당 행에 약물을 붓고 tmpAnswer++ 시킨다.
3. minAnswer보다 tmpAnswer가 아직 작으면, 그 다음 행에도 약물을 뽑아본다.
4. 모든 행을 다 뽑고 난 뒤 tmpAnswer을 minAnswer과 비교한다.
5. 뽑은 걸 철회할 때 `동시에` 원래의 셀로 복구시킨다

주의점: 시간초과
*/
#include <iostream>
using namespace std;

int D, W, K;
int map[15][25];
int backup[15][25];

int minAnswer = 20;
int picked[15]; // 0:약품투입x   1:약품 A(0)투입   2:약품 B(1)투입
int tmpAnswer;

void Input() {
	minAnswer = 20;
	tmpAnswer = 0;
	scanf("%d %d %d\n", &D, &W, &K);
	for (int i = 0; i < D; i++) {
		for (int j = 0; j < W; j++) {
			scanf("%d ", &map[i][j]);
			backup[i][j] = map[i][j];
		}
	}
}

void Print() {
	for (int i = 0; i < D; i++) {
		for (int j = 0; j < W; j++) {
			printf("%d ", map[i][j]);
		}
		cout << endl;
	}
}

bool Check() {
	for (int j = 0; j < W; j++) {
		int lastStatus = map[0][j];
		int num = 1;

		for (int i = 1; i < D; i++) {
			if (lastStatus == map[i][j]) {
				num++;
				if (num >= K) break; // 이번열 되는것 확인했으면 다음열로 넘어가기
			}
			else {
				lastStatus = map[i][j];
				num = 1;
			}
		}

		// 이번 j열에서 충족이 안 된 경우
		if (num < K) return false;
	}

	return true;
}

void DFS(int cnt) {
	if (cnt >= D) {

		/*cout << endl;
		Print();
		cout << endl;*/

		if (Check()) { // 이번에 됨
			if (tmpAnswer < minAnswer) minAnswer = tmpAnswer;
		}

		return;
	}

	for (int i = 0; i < 3; i++) {
		// cout << i;
		if (i != 0) { // 시간 줄이기 1: 전부 뽑아놓고 매번 다 바꿔보는 게 아니라, 진행하면서 동시에 바꾸기
			for (int j = 0; j < W; j++) {
				map[cnt][j] = i - 1;
			}
			tmpAnswer++;
		}
		
		if (tmpAnswer < minAnswer) { // 시간 줄이기 2: 이번 케이스에 어차피 최소가 안될 게 밝혀지면 그만하기
			DFS(cnt + 1);
		}

		if (i != 0) { // 시간 줄이기 1: 전부 뽑아놓고 매번 다 바꿔보는 게 아니라, 진행하면서 동시에 바꾸기
			for (int j = 0; j < W; j++) {
				map[cnt][j] = backup[cnt][j];
			}
			tmpAnswer--;
		}
		
	}
}

int main() {

	int test;
	scanf("%d\n", &test);
	for (int testCase = 1; testCase <= test; testCase++) {
		Input();

		cout << "#" << testCase << " ";

		if (Check()) { // 처음부터 성능 충족된 경우
			cout << 0 << endl;
		}
		else {
			DFS(0);
			cout << minAnswer << endl;
		}
	}

	return 0;
}