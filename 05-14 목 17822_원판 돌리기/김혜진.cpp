/*
function call: main -> Input -> (Round -> Check -> Remove/Replace) -> Calculate

������
1. ���� ���� ������ 1��° ���� 4��° ���� ������ ������ ����
2. ������ ���� ���� ���� DFS�� ����ؾ� ���߸��� �ʴ´�
3. x�� ��� ������ ����ϱ� ���� �ε����� 1���� �����ߴٸ� �򰥸� �� �ִ�
*/
#include <iostream>
#include <vector>
using namespace std;

struct Info {
	int x; // ��ȣ�� x�� ����� ������
	int d; // 0:�ð� 1:�ݽð� ��������
	int k; // kĭ ȸ����Ų��
};

int N, M, T; // ���ǰ���, ���ڰ���, ȸ��Ƚ��
vector<vector<int>> map(51, vector<int>(51, 0)); // �ε����� 1�����̱⶧���� 50�� Ŀ���ϱ� ���� 51����
vector<vector<int>> visited(51, vector<int>(51, 0));
vector<vector<int>> emptyVector(51, vector<int>(51, 0));
vector<Info> Infos;

float num; // map�� ���� ���� (num/num => ������ �������⿡ �ϳ��� float������)
int numSum; // map�� ���� ��

void Input() {
	cin >> N >> M >> T;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}

	int x, d, k;
	for (int i = 0; i < T; i++) {
		cin >> x >> d >> k;
		Infos.push_back(Info{ x, d, k });
	}
}

void Move(int n, int d) { // ok
	if (d == 0) { // �ð�
		int tmp = map[n][M];
		for (int i = M; i >= 1; i--) {
			map[n][i] = map[n][i - 1];
		}
		map[n][1] = tmp;
	}
	else { // �ݽð�
		int tmp = map[n][1];
		for (int i = 2; i <= M; i++) {
			map[n][i - 1] = map[n][i];
		}
		map[n][M] = tmp;
	}
}

void Round(int x, int d, int k) {
	for (int n = 1; n <= N; n++) {
		// x�� ����� �������� �˻�
		if (n / x < 1) continue;
		if (n % x != 0) continue;
		
		for (int i = 0; i < k; i++) { // k�� ������
			Move(n, d);
		}
	}
}

void Print() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int tmpR, tmpC;

void RemoveDfs(int r, int c, int num) { // ������ �ֵ鳢�� �� ������ �ϹǷ� DFS (�ܼ� 4�������� �ؼ� ��� �ָ� ���������� ������ �ְ� ���� �ȵ�)
	map[r][c] = 0;

	for (int t = 0; t < 4; t++) {
		tmpR = r + dir[t][0];
		tmpC = c + dir[t][1];

		if (tmpR < 1 || N + 1 <= tmpR) continue;
		if (tmpC == 0) tmpC = M;					// ���� ���� �������� circular
		if (tmpC == M + 1) tmpC = 1;
		if (visited[tmpR][tmpC] == 1) continue;
		if (num != map[tmpR][tmpC])  continue;

		visited[tmpR][tmpC] = 1;
		RemoveDfs(tmpR, tmpC, num);
	}
}

void Remove() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (map[i][j] == 0) continue;

			bool removed = false;
			for (int t = 0; t < 4; t++) {
				tmpR = i + dir[t][0];
				tmpC = j + dir[t][1];

				if (tmpC == 0) tmpC = M;		// ���� ���� �������� circular
				if (tmpC == M + 1) tmpC = 1;
				if (tmpR < 1 || N + 1 <= tmpR) continue;
				
				if (map[i][j] != map[tmpR][tmpC])  continue;
				//cout << i << "," << j << "(" << map[i][j] << ") ?= " << tmpR << "," << tmpC << "(" << map[tmpR][tmpC] << ")" << endl;
				removed = true;
			}
			if (removed) {
				visited[i][j] = 1;
				RemoveDfs(i, j, map[i][j]);
			}
			
		}
	}
}

void Replace() {
	float numMean = numSum / num;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (map[i][j] == 0) continue;
			if (map[i][j] > numMean) map[i][j]--;
			else if (map[i][j] < numMean) map[i][j]++;
		}
	}
}


bool Check() {
	// Replace�� ���� ���� �ʱ�ȭ
	num = 0;
	numSum = 0;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (map[i][j] == 0) continue;
			num++;
			numSum += map[i][j];
			
			for (int t = 0; t < 4; t++) {
				tmpR = i + dir[t][0];
				tmpC = j + dir[t][1];

				if (tmpR < 1 || tmpC < 1 || tmpR >= N+1 || tmpC >= M+1) continue;
				if (map[i][j] == map[tmpR][tmpC]) {
					// cout << i << "," << j << " = " << tmpR << "," << tmpC << endl;
					return true;
				}
			}
		}
	}
	return false;
}

int Calculate() {
	int answer = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			answer += map[i][j];
		}
	}
	return answer;
}

int main() {

	Input();

	for (int t = 0; t < T; t++) {
		Info thisInfo = Infos[t];
		Round(thisInfo.x, thisInfo.d, thisInfo.k);
		//Print();
		if (Check()) { // �����ϸ鼭 ���� ���ڰ� �ִ�
			//cout << "remove" << endl;
			visited = emptyVector; // DFS�� ����� visited �ʱ�ȭ
			Remove();
		}
		else { // �����ϸ鼭 ���� ���ڰ� ����
			//cout << "Replace" << endl;
			Replace();
		}
		/*Print();
		cout << Calculate() << endl;*/
	}

	cout << Calculate();

	return 0;
}