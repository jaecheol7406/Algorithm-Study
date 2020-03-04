#include <iostream>
#include <vector>
using namespace std;

int N, M, T;

int map[55][55];
vector<int> xi;
vector<int> di;
vector<int> ki;

void Input() {
	scanf("%d %d %d\n", &N, &M, &T);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d ", &map[i][j]);
		}
	}

	int x, d, k;
	for (int t = 0; t < T; t++) {
		scanf("%d %d %d", &x, &d, &k);
		xi.push_back(x);
		di.push_back(d);
		ki.push_back(k);
	}
}

void Print() {
	cout << "==========" << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			printf("%d ", map[i][j]);
		}
		cout << endl;
	}

	for (int t = 0; t < T; t++) {
		cout << xi[t] << "," << di[t] << "," << ki[t] << endl;
	}
}

void Check() {
	// ������ ���� ã�´�
	bool changeFlag = false;
	bool changeFlag1 = false;
	bool changeFlag2 = false;
	// 1.���� ���� ������
	int right, left;
	for (int i = 1; i <= N; i++) {
		cout << i << "��° ���� ��===========" << endl;
		for (int j = 2; j <= M-1; j++) {
			left = j - 1;
			right = j + 1;

			if (map[i][j] != 0 && map[i][j] == map[i][left]) {
				cout << "map[" << i << "][" << j << "] = map[" << i << "][" << left << "] (" << map[i][j] << endl;
				map[i][left] = 0;
				changeFlag1 = true;
			}
			if (map[i][j] != 0 && map[i][j] == map[i][right]) {
				cout << "map[" << i << "][" << j << "] = map[" << i << "][" << right << "] (" << map[i][j] << endl;
				map[i][right] = 0;
				changeFlag1 = true;
			}
			if (changeFlag1) {
				map[i][j] = 0;
				changeFlag = true;
			}
			changeFlag1 = false;

		}
	}

	// 2.�ٸ� ���� ��
	int top, bottom;
	for (int j = 1; j <= M; j++) {
		cout << j << "�� �� ��===========" << endl;
		for (int i = 2; i <= N - 1; i++) {
			top = i + 1;
			bottom = i - 1;

			if (map[i][j] != 0 && map[i][j] == map[top][j]) {
				cout << "map[" << i << "][" << j << "] = map[" << top << "][" << j << "] (" << map[i][j] << endl;
				map[top][j] = 0;
				changeFlag2 = true;
			}
			if (map[i][j] != 0 && map[i][j] == map[bottom][j]) {
				cout << "map[" << i << "][" << j << "] = map[" << bottom << "][" << j << "] (" << map[i][j] << endl;
				map[bottom][j] = 0;
				changeFlag2 = true;
			}
			if (changeFlag2) {
				cout << "map[" << i << "][" << j << "]= 0" << endl;
				map[i][j] = 0;
				changeFlag = true;
			}
			changeFlag2 = false;
		}
	}

	if (changeFlag == false) { // �����ϸ鼭 ���� ���� ���� ���� ��쿡�� ���ǿ� ���� ���� ����� ���ϰ�, ��պ��� ū ������ 1�� ����, ���� ������ 1�� ���Ѵ�.
		cout << "flag = false" << endl;
		int cnt = 0;
		float mean = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (map[i][j] == 0) continue;
				mean += map[i][j];
				cnt++;
			}
		}

		mean /= cnt;
		cout << "mean: " << mean << endl;

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (map[i][j] == 0) continue;
				if (map[i][j] > mean) {
					cout << "map[" << i << "][" << j << "] > " << mean << endl;
					map[i][j]--;
				}
				else if (map[i][j] < mean) {
					cout << "map[" << i << "][" << j << "] < " << mean << endl;
					map[i][j]++;
				}
			}
		}
	}
}

void Turn(int x, int d, int k) {
	if (d == 0) { // �ð� ����
		int backup;
		for (int hoe = 0; hoe < k; hoe++) {
			backup = map[x][M];
			for (int k = M - 1; k >= 1; k--) {
				// cout << "map[" << x << "][" << k + 1 << "]= " << map[x][k] << endl;
				map[x][k + 1] = map[x][k];
			}
			map[x][1] = backup;
		}
	}
	else { // �ݽð� ����
		for (int hoe = 0; hoe < k; hoe++) {
			for (int k = 0; k < M; k++) {
				map[x][k] = map[x][k + 1];
				// cout << "map[" << x << "][" << k << "]= " << map[x][k+1] << endl;
			}
			map[x][M] = map[x][0];
			map[x][0] = 0;
		}
	}

}



int main() {

	Input();

	int thisx, thisd, thisk;
	for (int t = 0; t < xi.size(); t++) {
		thisx = xi[t];
		thisd = di[t];
		thisk = ki[t];

		Print();
		for (int r = 1; r <= N; r++) { // r: ���� ��ȣ
			if (r % thisx != 0) continue; // ��ȣ�� xi�� ����� ������ �ƴϸ� �ǳʶڴ�
			Turn(r, thisd, thisk); // di�������� kiĭ ȸ����Ų��.
		}
		Print();
		Check();
		Print();
	}
	int sum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			sum += map[i][j];
		}
	}


	cout << sum;

	return 0;
}