/*

# 1*1 ¥�� ĭ�� ������ ����ü�� ������
struct Space {
	vector<int> tree;		---> �ش� ��ġ�� �ɾ��� ������ ����. ������ ������ �� �� �����Ƿ� ���ͷ� ����
	vector<int> dead;		---> �ش� ��ġ�� �ɾ��� �־����� ���� ���� ������ �Ǵܵ� ������ ����
	int nutr = 5;			---> �ش� ��ġ�� ���

# Space ����ü�� �����ϴ� 2���� �迭�� ����
Space map[12][12];

# �ش� �迭�� ���Ͽ� 4������ ������
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int N, M, K;

struct Space {
	vector<int> tree;		// �ش� ��ġ�� �ɾ��� ������ ����
	vector<int> dead;		// ���� ������ ����
	int nutr = 5;				// ���
};

// 2���� �迭 �ε��� 1���� ����
Space map[12][12];			// �� ����
int winter[12][12];			// �ܿ￡ �� ��� ����

void Input() {
	scanf("%d %d %d\n", &N, &M, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d ", &winter[i][j]);
		}
	}

	int r, c, age;
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d\n", &r, &c, &age);
		map[r][c].tree.push_back(age);
	}
}

void Count() {
	// cout << "���� ������ ��: ";
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cnt += map[i][j].tree.size();
		}
	}
	cout << cnt << endl;
}

void Info() {
	cout << "==================" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << i << "," << j << "�� ���� ����: ";
			for (int t = 0; t < map[i][j].tree.size(); t++) {
				cout << map[i][j].tree[t] << " ";
			}
			cout << "/ ���: " << map[i][j].nutr << endl;
		}
		cout << endl;
	}
}

void Spring() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			sort(map[i][j].tree.begin(), map[i][j].tree.end());					// ���̰� � ���� ���� ����� �ֱ� ���� �������� ����

			// ��� ������ ��� ���븦 �õ��Ѵ�
			vector<int> alive;													// ���� ������ ��Ƴ��� ���� �迭���� �����ϱ� ����, ��Ƴ��� �ֵ鸸 ���� ����
			for (int t = 0; t < map[i][j].tree.size(); t++) {
				if (map[i][j].nutr >= map[i][j].tree[t]) {						// ��Ƴ���
					map[i][j].nutr -= map[i][j].tree[t];
					alive.push_back(map[i][j].tree[t] + 1);
				}
				else {															 // ����
					map[i][j].dead.push_back(map[i][j].tree[t]);
				}
			}

			map[i][j].tree.clear();												// ������ ���� ���͸� �����, ��Ƴ��� �ֵ鸸 ��� �ִ� ���ͷ� �����
			for (int t = 0; t < alive.size(); t++) {
				map[i][j].tree.push_back(alive[t]);
			}

		}
	}
}

void Summer() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int sum = 0;
			for (int t = 0; t < map[i][j].dead.size(); t++) {
				sum += floor(map[i][j].dead[t]/2);
			}
			map[i][j].nutr += sum;
			map[i][j].dead.clear();
		}
	}
}

int dir[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
void Fall() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			for (int t = 0; t < map[i][j].tree.size(); t++) {
				if (map[i][j].tree[t] % 5 == 0) {								// ���� ���
					int tmpr, tmpc;
					for (int c = 0; c < 8; c++) {
						tmpr = i + dir[c][0];
						tmpc = j + dir[c][1];

						if (tmpr < 1 || tmpc < 1 || 10 < tmpr || 10 < tmpc) continue;
						map[tmpr][tmpc].tree.push_back(1);
					}
				}
			}
		}
	}
}

void Winter() {
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j].nutr += winter[i][j];
		}
	}
}

int main() {

	Input();

	for (int year = 1; year <= K; year++) {
		Spring();
		Summer();
		Fall();
		Winter();
	}
	Count();

	return 0;
}