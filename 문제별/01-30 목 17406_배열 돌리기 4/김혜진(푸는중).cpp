#include <iostream>
#include <vector>
using namespace std;

struct Info {
	int xStart; // 시작점 x
	int yStart;
	int xEnd;
	int yEnd;
	int n; // 몇 번 돌아야 하는지
};

int R, C, K;
int map[60][60]; // 인덱스는 1부터 시작
int backup[60][60];
vector<Info> Infos;

void Input();
void Print();
void PrintInfos();
void Turn(int startX, int startY, int endX, int endY, int n);
int GetMin();

int main() {

	Input();

	for (int i = 0; i < Infos.size(); i++) {
		Turn(Infos[i].xStart, Infos[i].yStart, Infos[i].xEnd, Infos[i].yEnd, Infos[i].n);
		Print();
		printf("최솟값: %d\n", GetMin());
	}

	return 0;
}

void Input() {
	scanf("%d %d %d\n", &R, &C, &K);

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			scanf("%d ", &map[i][j]);
			backup[i][j] = map[i][j];
		}
	}

	int r, c, k;

	for (int i = 0; i < K; i++) {
		scanf("%d %d %d\n", &r, &c, &k);
		Infos.push_back(Info{r-k, c-k, r+k, c+k, k});
	}
}

void Print() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void PrintInfos() {
	for (int i = 0; i < Infos.size(); i++) {
		printf("시작점: %d,%d 끝점: %d,%d 달팽이 개수: %d\n", Infos[i].xStart, Infos[i].yStart, Infos[i].xEnd, Infos[i].yEnd, Infos[i].n);
	}
}

void Turn(int startX, int startY, int endX, int endY, int n) {
	int r, c;
	int tmp; // map[startX][startY]를 백업

	for (int i = 0; i < n; i++) { // 달팽이 개수
		r = startX + i; // 이번 달팽이에서의 시작점
		c = startY + i;

		tmp = map[r][c];
		r++;

		while (r < endX - i) {
			map[r - 1][c] = map[r][c];
			r++;
		}
		map[r - 1][c] = map[r][c];
		c++;

		while (c < endY - i) {
			map[r][c - 1] = map[r][c];
			c++;
		}
		map[r][c - 1] = map[r][c];
		r--;

		while (r > startX + i) {
			map[r + 1][c] = map[r][c];
			r--;
		}
		map[r + 1][c] = map[r][c];
		c--;

		while (c > startY + i) {
			map[r][c + 1] = map[r][c];
			c--;
		}
		map[r][++c] = tmp;
	}
}

int GetMin() {
	int min = 6000;
	int sum = 0;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			sum += map[i][j];
		}
		if (sum < min) min = sum;
		sum = 0;
	}
	return min;
}