/*
13% Ʋ�Ƚ��ϴ�

���ܻ���
- 1 0 2 0 0 0 1 0 0 2 ó�� �պκп��� ����Ұ��ߴµ� �ڿ��� ���ᰡ���� ��
5 10
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 0 0 0 0
1 0 1 0 0 1 0 1 0 1
1 1 1 0 0 0 0 1 1 1
1 1 1 1 1 1 1 1 1 1
��: 2

- '��� �� ���� üũ'�� 1,2,3�� ���� ����ǰ� 4,5�� ��������� �� �� �׷��� ���� �ȵǸ� ��
10 6
0 0 0 1 0 0
0 0 0 1 0 0
0 1 0 0 0 1
0 0 0 0 0 0
1 1 0 1 1 0
1 0 0 0 1 0
1 1 0 0 1 0
0 0 0 0 1 1
0 0 0 0 0 0
0 1 0 0 0 0
��: 13

- ª�� �ٸ��� �̹� ����� ���� �����Ѵٸ� pass
9 8
0 0 1 0 0 0 0 1
0 0 1 1 0 0 0 1
0 0 1 1 1 0 0 1
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 1 1 1 1
0 0 0 0 0 0 1 1
1 0 0 0 0 0 1 1
��: 10
10 7
1 1 1 1 1 1 1
0 0 0 0 0 0 0
0 0 0 0 0 0 0
1 0 0 1 0 0 1
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 1 0 0 1
��: 13
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Dist {
	int is1;
	int is2;
	int dist;
};
vector<Dist> distList;

int N, M;
int map[10][10];
int island[10][10];
int minDist[7][7]; // �� ���� �Ÿ�

int answer;

int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int visitedIsland[10][10];
int islandIdx;

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
}

void getIsland(int r, int c) {
	int tmpR, tmpC;

	for (int i = 0; i < 4; i ++) {
		tmpR = r + dir[i][0];
		tmpC = c + dir[i][1];

		if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) continue;
		if (visitedIsland[tmpR][tmpC] == 1) continue;
		if (map[tmpR][tmpC] != 1) continue;

		visitedIsland[tmpR][tmpC] = 1;
		island[tmpR][tmpC] = islandIdx;
		getIsland(tmpR, tmpC);

	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << island[i][j];
		}
		cout << endl;
	}
}

int horDist(int is1, int is2) {
	int answer = 9999;

	for (int i = 0; i < N; i++) {
		int startPos = -1;
		int endPos = -1;
		bool started = false;
		int startedIsland = -1;

		for (int j = 0; j < M; j++) {
			
			if (island[i][j] == is1 || island[i][j] == is2) {
				if (!started) { // ���ʷ� � ���� ã��
					startedIsland = island[i][j];
					startPos = j;
					started = true;
				}
				else if (island[i][j] == startedIsland) {
					startPos = j;
				}
				else if (island[i][j] != startedIsland) {

					endPos = j;
					if (endPos - startPos <= 2) { // ���̰� 2 �̻��̾�� ��
						started = false;
						continue;
					}
						
					if ((endPos - startPos) < answer) answer = endPos - startPos;

					break; // ���� ���� �˻��Ϸ� ����
				}
			}
			else if (started && island[i][j] != 0) { // �߰��� �ٸ� ���� ������
				started = false;
				continue;
			}

		}
	}

	// cout << answer << endl;
	return answer;
}

int verDist(int is1, int is2) {
	int answer = 9999;

	for (int j = 0; j < M; j++) {
		int startPos = -1;
		int endPos = -1;
		bool started = false;
		int startedIsland = -1;

		for (int i = 0; i < N; i++) {
			if (island[i][j] == is1 || island[i][j] == is2) {
				if (!started) {
					startedIsland = island[i][j];
					startPos = i;
					started = true;
				}
				else if (island[i][j] == startedIsland) {
					startPos = i;
				}
				else if (island[i][j] != startedIsland) {
					endPos = i;
					if (endPos - startPos <= 2) { // �ٸ� ���̴� 2 �̻�
						started = false;
						continue;
					}

					if ((endPos - startPos) < answer) answer = endPos - startPos;

					break;
				}
			}
			else if (started && island[i][j] != 0) { // �߰��� �ٸ� ���� ���ִ� ���
				started = false;
				continue;
			}
		}
	}
	return answer;
}

void getDistance(int is1, int is2) {
	int minDistance = 9999;

	// ���η� ����
	int tmp = horDist(is1, is2);
	if (tmp >= 3 && minDistance > tmp) minDistance = tmp - 1;

	// ���η� ����
	tmp = verDist(is1, is2);
	if (tmp >= 3 && minDistance > tmp) minDistance = tmp - 1;

	// cout << minDistance << endl;

	minDist[is1][is2] = minDistance;
	//minDist[is2][is1] = minDistance;
	distList.push_back(Dist{ is1, is2, minDistance });
}

bool cmp(Dist a, Dist b) {
	if (a.dist == b.dist && a.is1 == b.is1) {
		return a.is2 < b.is2;
	}
	if (a.dist == b.dist) {
		return a.is1 < b.is1;
	}

	return a.dist < b.dist;
}

int linked[7];
int main() {

	Input();

	// ���� ���� ���ϱ�
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] != 1) continue;
			if (visitedIsland[i][j] == 1) continue;
			islandIdx++;

			visitedIsland[i][j] = 1;
			island[i][j] = islandIdx;
			getIsland(i, j);
		}
	}

	// Print();

	// �� ���� �Ÿ� �ּҰŸ� ���ϱ� (������)
	for (int i = 1; i < islandIdx; i++) {
		for (int j = i + 1; j <= islandIdx; j++) {
			getDistance(i, j);
		}
	}

	/*for (int i = 1; i <= islandIdx; i++) {
		for (int j = 1; j <= islandIdx; j++) {
			cout << minDist[i][j] << " ";
		}
		cout << endl;
	}*/

	sort(distList.begin(), distList.end(), cmp);

	int uniqueIdx = 0;
	for (int i = 0; i < distList.size(); i++) {
		cout << "�̹� ª�� �ٸ�:" << distList[i].dist << endl;
		
		// �Ϸ����� ��������==========================================
		int check = 0;
		for (int j = 1; j <= 6; j++) if (linked[j] == 1) check++;

		/*for (int j = 1; j <= 6; j++) cout << linked[j] << " ";
		cout << endl;
		cout << "check: " << check << "?=" << islandIdx << endl;*/

		if (check == islandIdx) break;
		// �Ϸ����� ��������==========================================

		if (distList[i].dist == 9999) {
			answer = 9999;
			break;
		}

		int is1 = distList[i].is1;
		int is2 = distList[i].is2;
		cout << is1 << "�� " << is2 << endl;

		if (linked[is1] != 0 && linked[is2] != 0) { // �̹� ��򰡿� ����Ǿ� �ִ� �� ��
			if (linked[is1] == linked[is2]) continue; // �̹� ���� ���� ���ִٸ� �ٸ� ������ �ʰ� pass

			int std; // �� ���� ��
			int verse; // �� ū ��
			if (linked[is1] > linked[is2]) {
				std = linked[is2];
				verse = linked[is1];
			}
			else {
				std = linked[is1];
				verse = linked[is2];
			}

			for (int t = 1; t <= islandIdx; t++) {
				if (linked[t] == verse) linked[t] = std;
			}
		}
		else if (linked[is1] == 0 && linked[is2] == 0) { // �Ѵ� ó�� ����
			uniqueIdx++;
			linked[is1] = uniqueIdx;
			linked[is2] = uniqueIdx;
		}
		else if (linked[is2] != 0 && linked[is1] == 0) { // is1�� ���� ����
			linked[is1] = linked[is2];
		}
		else if (linked[is1] != 0 && linked[is2] == 0) { // is2�� ���� ����
			linked[is2] = linked[is1];
		}
		

		answer += distList[i].dist;
		cout << "�ٸ����� += " << distList[i].dist << endl;

	}

	if (answer == 9999) cout << -1;
	else cout << answer;

	return 0;
}