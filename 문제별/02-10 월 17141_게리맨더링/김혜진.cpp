#include <iostream>
#include <stdlib.h>
using namespace std;

int N;
int population[15];
int num[15][15];
int team[15];

void Input() {
	scanf("%d\n", &N);

	for (int i = 1; i <= N; i++) {
		scanf("%d ", &population[i]);
	}
	
	for (int n = 0; n < N; n++) {
		for (int i = 1; i <= N; i++) {
			scanf("%d ", &num[i][0]);
			for (int j = 1; j <= num[i][0]; j++) {
				scanf("%d ", &num[i][j]);
			}
		}
	}
}

void Print() {
	cout << "인구" << endl;
	for (int i = 1; i <= N; i++) {
		printf("%d ", population[i]);
	}
	cout << endl;

	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			printf("%d ", num[i][j]);
		}
		cout << endl;
	}
}

int min = 1000;
void DFS(int n, int t) {
	if (n > N) {
		/*for (int i = 1; i <= N; i++) {
			cout << team[i] << " ";
		}
		cout << endl;*/
		// 조건에 부합하는지 확인한다
			// 1) 같은 구역끼리 연결되어 있다.
				// A선거구 검증

				// B선거구 검증

			// 2) 하나가 아니라 두 개 선거구이다.
		int scoreA = 0;
		int scoreB = 0;
		for (int i = 1; i <= N; i++) {
			if (team[i] == 1) {
				scoreA += population[i];
			}
			else {
				scoreB += population[i];
			}
		}

		if (scoreA == 0 || scoreB == 0) return;

		// 각 팀 인구수 차이 구해 min과 비교한다
		/*for (int i = 1; i <= N; i++) {
			cout << team[i] << " ";
		}
		cout << endl;*/
		if (min > abs(scoreA - scoreB)) {
			min = abs(scoreA - scoreB);
		}
		return;
	}

	team[n] = t;

	DFS(n + 1, 1);
	DFS(n + 1, 2);

	team[n] = 0;

}

int main() {

	Input();
	// Print();

	DFS(1, 1);
	DFS(1, 2);

	if (min == 1000) {
		cout << "-1";
	}
	else {
		cout << min;
	}
	

	return 0;
}