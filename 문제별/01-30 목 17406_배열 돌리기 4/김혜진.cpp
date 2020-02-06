#include <iostream>
#include <vector>
using namespace std;

struct Info {
	int xStart; // ������ x
	int yStart;
	int xEnd;
	int yEnd;
	int n; // �� �� ���ƾ� �ϴ���
};

int R, C, K;
int map[60][60]; // �ε����� 1���� ����
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
void DFS(int cnt);

int MIN = 6000;
int main() {

	Input();

	DFS(0);

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
		printf("������: %d,%d ����: %d,%d ������ ����: %d\n", Infos[i].xStart, Infos[i].yStart, Infos[i].xEnd, Infos[i].yEnd, Infos[i].n);
	}
}

void Turn(int startX, int startY, int endX, int endY, int n) {
	int r, c;
	int tmp; // map[startX][startY]�� ���

	for (int i = 0; i < n; i++) { // ������ ����
		r = startX + i; // �̹� �����̿����� ������
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

vector<int> V; // Infos�� ������ ����

void DFS(int cnt) {
	
	if (cnt >= K) {
		
		for (int i = 0; i < V.size(); i++) {
			Info t = Infos[V[i]];
			Turn(t.xStart, t.yStart, t.xEnd, t.yEnd, t.n);
			// cout << V[i] << "�� ����" << endl;
			// Print();

			
		}
		int min = GetMin();
		// cout << "min: " << min << endl;

		if (MIN > min) MIN = min;

		// �ǵ�����
		for (int i = 1; i <= R; i++) {
			for (int j = 1; j <= C; j++) {
				map[i][j] = backup[i][j];
			}
		}
		// cout << "=========" << endl;

		return;
	}

	for (int i = 0; i < K; i++) {
		if (Select[i]) continue;

		Select[i] = true;
		V.push_back(i);

		DFS(cnt + 1);

		V.pop_back();
		Select[i] = false;
	}
}