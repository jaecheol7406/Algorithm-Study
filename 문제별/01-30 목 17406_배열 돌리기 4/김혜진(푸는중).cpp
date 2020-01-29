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
void Init();

#define MAX 10
bool Select[MAX];
vector<int> V;
void DFS(int cnt);

int MIN = 6000;
int main() {

	Input();

	DFS(0);

	/*for (int i = 0; i < Infos.size(); i++) {
		Turn(Infos[i].xStart, Infos[i].yStart, Infos[i].xEnd, Infos[i].yEnd, Infos[i].n);
		Print();
		printf("최솟값: %d\n", GetMin());
	}*/
	cout << MIN;


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
		Infos.push_back(Info{ r - k, c - k, r + k, c + k, k });
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

/*void Init() {
	for (int i = 1; i < R; i++) {
		for (int j = 1; j < C; j++) {
			map[i][j] = backup[i][j];
		}
	}
}*/

void PrintPermutation() {
	for (int i = 0; i < V.size(); i++) {
		Info thisInfo = Infos[V[i] - 1];
		cout << thisInfo.n << " ";
		
	}
	cout << endl;
}

int copiedMap[60][60];

/*void CopyMap() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			copiedMap[i][j] = map[i][j];
		}
	}
}

void RevertMap() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			map[i][j] = copiedMap[i][j];
		}
	}
}*/

int(*BackupMap(int(*map)[60]))[60]{
	return map;
}

void DFS(int cnt) {
	cout << "cnt: " << cnt << endl;
	if (cnt >= K) {
		// PrintPermutation();
		int tmp = GetMin();
		if (MIN > tmp) {
			MIN = tmp;
		}

		return;
	}

	for (int i = 1; i <= K; i++) {
		if (Select[i]) continue;

		// CopyMap();
		int(*origMap)[60] = BackupMap(map);
		cout << "백업한 오리지널 맵: " << endl;
		for (int i = 1; i <= C; i++) {
			cout << origMap[i];
			cout << endl;
		}

		Select[i] = true;
		// V.push_back(i);
		Info thisInfo = Infos[i-1];
		Turn(thisInfo.xStart, thisInfo.yStart, thisInfo.xEnd, thisInfo.yEnd, thisInfo.n);
		cout << cnt+1 << "번째 숫자로 " << i << "선택" << endl;
		cout << "연산: " << thisInfo.xStart + thisInfo.n << " " << thisInfo.yStart + thisInfo.n << endl;
		Print();
		cout << endl;

		DFS(cnt + 1);

		// RevertMap();
		for (int i = 1; i <= R; i++) {
			for (int j = 1; j <= C; j++) {
				map[i][j] = origMap[i][j];
			}
		}
		// V.pop_back();

		Select[i] = false;
	}
}