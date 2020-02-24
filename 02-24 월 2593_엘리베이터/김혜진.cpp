/*
DFS, �ð��ʰ�
*/
#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<int> xarr;
vector<int> yarr;
int Start, End;
int thisStair;

vector<vector<int>> ev; // ev[0]�� 0�� ���������Ͱ� �� �� �ִ� �� ����
int maxStair = 1;

void Input() {
	scanf("%d %d\n", &N, &M);
	int x, y;
	for (int i = 0; i < M; i++) {
		scanf("%d %d\n", &x, &y);
		xarr.push_back(x);
		yarr.push_back(y);
	}
	scanf("%d %d", &Start, &End);
	thisStair = Start;

}

void Print() {
	cout << N << " " << M << endl;

	for (int i = 0; i < M; i++) {
		cout << xarr[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < M; i++) {
		cout << yarr[i] << " ";
	}
	cout << endl;

	cout << Start << " " << End << endl;

}
int MIN = 999999;

int lastEv = 9999;
vector<int> selected;
int visited[110][100100];

vector<int> sequence;
void DFS(int cnt) {
	if (cnt >= MIN) return;
	/*cout << endl << "DFS" << cnt << endl;
	cout << thisStair << "==" << End << endl;*/

	if (thisStair == End) { // ���� ����

		/*cout << "===����:" << cnt << " ";
		for (int i = 0; i < selected.size(); i++) {
			cout << selected[i]+1;
		}
		cout << endl;*/

		if (MIN > cnt) {
			MIN = cnt;
			sequence.clear();
			for (int i = 0; i < selected.size(); i++) {
				sequence.push_back(selected[i]);
			}
		}
		thisStair = Start;
		return;
	}


	for (int i = 0; i < M; i++) {
		if ((thisStair - xarr[i]) % yarr[i] != 0) continue;  // i�� ���������͸� Ż �� ���� ���
		if (i == lastEv) continue;


		// i�� ���������͸� ź��. ��� ���� ������ ����
		lastEv = i;
		// cout << i << "�� ���������� Ÿ��" << endl;

		for (int j = 0; xarr[i] + yarr[i] * j <= N; j++) {
			if (xarr[i] + yarr[i] * j == thisStair) {
				visited[i][j] = 1;
				continue;
			}

			if (visited[i][j] == 0) {
				visited[i][j] = 1;
				selected.push_back(i);
				thisStair = xarr[i] + yarr[i] * j;
				// cout << thisStair << "���� ������" << endl;

				DFS(cnt + 1);

				visited[i][j] = 0;
				selected.pop_back();
			}
		}

		return;

	}
}

int main() {

	Input();
	// Print();
	DFS(0);

	if (MIN == 999999) {
		cout << -1;
	}
	else {
		cout << MIN << endl;
		for (int i = 0; i < sequence.size(); i++) {
			cout << sequence[i] + 1 << endl;
		}
	}


	return 0;
}