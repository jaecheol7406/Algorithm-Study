/*
DFS, 시간초과
*/
#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<int> xarr;
vector<int> yarr;
int Start, End;
int thisStair;

vector<vector<int>> ev; // ev[0]은 0번 엘리베이터가 갈 수 있는 층 정보
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

	if (thisStair == End) { // 종료 조건

		/*cout << "===종료:" << cnt << " ";
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
		if ((thisStair - xarr[i]) % yarr[i] != 0) continue;  // i번 엘리베이터를 탈 수 없는 경우
		if (i == lastEv) continue;


		// i번 엘리베이터를 탄다. 어디서 내릴 것인지 결정
		lastEv = i;
		// cout << i << "번 엘리베이터 타기" << endl;

		for (int j = 0; xarr[i] + yarr[i] * j <= N; j++) {
			if (xarr[i] + yarr[i] * j == thisStair) {
				visited[i][j] = 1;
				continue;
			}

			if (visited[i][j] == 0) {
				visited[i][j] = 1;
				selected.push_back(i);
				thisStair = xarr[i] + yarr[i] * j;
				// cout << thisStair << "에서 내리기" << endl;

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