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
	cout << "�α�" << endl;
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
int verification[15] = { 0, };

void Check(int n) {
	// cout << "n: " << n << " ����: " << num[n][0] <<  endl;
	for (int i = 1; i <= num[n][0]; i++) {

		// �̹� ������ ������ pass
		if (verification[num[n][i]] != 0) continue;


		// cout << " �̹� üũ����:" << num[n][i] << " " << team[num[n][i]] << "==" << team[n] << endl;
		if (team[num[n][i]] == team[n]) {
			verification[num[n][i]] = team[n];
			Check(num[n][i]);
		}

	}
}

int MIN = 1000;
void DFS(int n, int t) {
	if (n > N) {

		/*for (int i = 1; i <= N; i++) {
			cout << team[i] << " ";
		}
		cout << endl;*/

		// ���ǿ� �����ϴ��� Ȯ���Ѵ�
			// 0) �ʱ�ȭ
		for (int i = 1; i <= N; i++) {
			verification[i] = 0;
		}

		// 1) ���� �������� ����Ǿ� �ִ�.

		verification[1] = team[1];
		Check(1);

		/*for (int i = 2; i <= N; i++) {
			if (team[i] != team[1])
				verification[i] = team[i];
		}*/



		for (int i = 2; i <= N; i++) {
			// cout << "*" << i;
			if (verification[i] == 0 && team[i] != team[1]) {
				// cout << i << "�� �ٸ� ������ ������" << endl;
				team[1] == 1 ? verification[i] = 2 : verification[i] = 1;
				Check(i);
				break;
			}
		}
		//cout << endl;

		/*for (int i = 1; i <= N; i++) {
			cout << team[i] << " ";
		}
		cout << endl;
		for (int i = 1; i <= N; i++) {
			cout << verification[i] << " ";
		}
		cout << endl;
		cout << "===================" << endl;*/

		// ���� �� �Ǹ� ������
		for (int i = 1; i <= N; i++) {

			if (team[i] != verification[i]) return;
		}

		// 2) �ϳ��� �ƴ϶� �� �� ���ű��̴�.
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

		// �� �� �α��� ���� ���� MIN�� ���Ѵ�
		/*for (int i = 1; i <= N; i++) {
			cout << team[i] << " ";
		}
		cout << endl;*/
		if (MIN > abs(scoreA - scoreB)) {
			MIN = abs(scoreA - scoreB);
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

	if (MIN == 1000) {
		cout << "-1";
	}
	else {
		cout << MIN;
	}


	return 0;
}