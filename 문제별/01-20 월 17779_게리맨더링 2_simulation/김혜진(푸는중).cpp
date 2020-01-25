#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int map[110][110];
int All;

void Input() {
	scanf("%d\n", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d ", &map[i][j]);
			All += map[i][j];
		}
	}
}

int Sum[110][110];
void MakeSum() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Sum[i][j] = Sum[i][j - 1] + map[i][j];
		}
	}
}

void Print() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			printf("%d ", Sum[i][j]);
		}
		printf("\n");
	}
}

int GetFirst(int x, int y, int d1, int d2) {
	int sum = 0;
	int j = y;
	for (int i = 1; i < x + d1; i++) {
		if (i >= x) {
			j--;
		}
		sum += Sum[i][j];
	}
	return sum;
}

int GetSecond(int x, int y, int d1, int d2) {
	int sum = 0;
	int j = y;
	for (int i = 1; i <= x + d2; i++) {
		sum += Sum[i][N] - Sum[i][j];
		if (i >= x) {
			j++;
		}
	}
	return sum;
}

int GetThird(int x, int y, int d1, int d2) {
	int sum = 0;
	int j = y - d1 - 1;
	int tmp = x + d1; 
	// if (y - d1 <= 1) tmp++;
	for (int i = tmp; i <= N; i++) {
		if (j < 1) continue;
		
		sum += Sum[i][j];
		if (i < x + d1 + d2 ) {
			j++;
		}
	}
	return sum;
}

int GetFourth(int x, int y, int d1, int d2) {
	int sum = 0;
	int j = y + d2 - 1;
	//int tmp = y + d2 - 1;
	for (int i = x + d2 + 1; i <= N; i++) {
		sum += Sum[i][N] - Sum[i][j];
		if (i <= x + d1 + d2) {
			j--;
		}
	}
	return sum;
}

int main() {
	Input();

	MakeSum();
	
	int minDiff = 40000;
	for (int i = 1; i <= N - 2; i++) {
		for (int j = 2; j <= N-1; j++) {
			for (int d1 = 1; d1 <= j - 1; d1++) {
				for (int d2 = 1; d2 <= N - j; d2++) {
					if (i + d1 + d2 > N) continue;
					// if (!(i + d1 + d2 <= N && 1 <= j - d1 && j + d2 <= N)) continue;
					vector<int> mans;
					
					mans.push_back(GetFirst(i, j, d1, d2));
					mans.push_back(GetSecond(i, j, d1, d2));
					mans.push_back(GetThird(i, j, d1, d2));
					mans.push_back(GetFourth(i, j, d1, d2));
					mans.push_back(All - (mans[0] + mans[1] + mans[2] + mans[3]));

					sort(mans.begin(), mans.end());
					if (mans[4] - mans[0] < minDiff) {
						minDiff = mans[4] - mans[0];
					}
				}
			}
		}
	}
	cout << minDiff;
	return 0;
}