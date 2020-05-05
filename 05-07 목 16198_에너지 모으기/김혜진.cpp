/*
function call: main -> Input -> DFS -> main

1. 1 ~ N-2 중 1개를 고른다. 이미 고른 원소는 visited를 통해 다시 고르지 않도록 한다.
2. 고르면 바로 Wx-1 × Wx+1를 계산해 쌓아둔다. visited를 통해 이미 골라서 삭제한 원소는 거른다.
3. 총 고른 개수가 N-2개가 될때까지 반복한다.
*/
#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> weights;

void Input() {
	cin >> N;

	int tmp;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		weights.push_back(tmp);
	}
}

int tmpAnswer = 0;
int answer = 0;

int a;
int b;

int visited[10];
void DFS(int cnt) {
	if (cnt + 2 == N) {
		if (tmpAnswer > answer) answer = tmpAnswer;

		return;
	}

	for (int i = 1; i <= N - 2; i++) {
		if (visited[i] == 1) continue;
		visited[i] = 1;
		
		// 삭제되지 않은 i-1 찾기
		for (int j = i - 1; j >= 0; j--) {
			if (visited[j] == 0) {
				a = j;
				break;
			}
		}

		// 삭제되지 않은 i+1 찾기
		for (int j = i + 1; j < N; j++) {
			if (visited[j] == 0) {
				b = j;
				break;
			}
		}

		int value = weights[a] * weights[b];
		tmpAnswer += value;

		DFS(cnt + 1);

		visited[i] = 0;
		tmpAnswer -= value;
	}
}

int main() {

	Input();

	DFS(0);

	cout << answer;

	return 0;
}