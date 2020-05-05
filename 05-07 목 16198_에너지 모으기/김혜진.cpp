/*
function call: main -> Input -> DFS -> main

1. 1 ~ N-2 �� 1���� ����. �̹� �� ���Ҵ� visited�� ���� �ٽ� ���� �ʵ��� �Ѵ�.
2. ���� �ٷ� Wx-1 �� Wx+1�� ����� �׾Ƶд�. visited�� ���� �̹� ��� ������ ���Ҵ� �Ÿ���.
3. �� �� ������ N-2���� �ɶ����� �ݺ��Ѵ�.
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
		
		// �������� ���� i-1 ã��
		for (int j = i - 1; j >= 0; j--) {
			if (visited[j] == 0) {
				a = j;
				break;
			}
		}

		// �������� ���� i+1 ã��
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