/*
BOJ 14888��: ������ �����ֱ�
���� ���� : ���Ʈ ����
function call : main() -> solve() -> input() ->Solution() -> DFS�ݺ�
���� Ǯ�� :
			 1. DFS�� Ȱ���� ������ �����ڸ� �����ؼ� v���Ϳ� ����
			 2. N-1���� ������ ������ ������ ����Ͽ� max,min�� ��


*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N;
int arr[11];
int com[4];
bool visit[11];
vector<int> v;
int maxAnswer = -1000000000;
int minAnswer = 1000000000;
int kk = 0;
void Input() {
	cin >> N;
	int num;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	for (int i = 0; i < 4; i++) {
		cin >> com[i];
	}
}
void DFS(int cnt) {
	if (cnt==N-1) {
		int answer = arr[0];
		int idx = 1;
		for (int i = 0; i < v.size(); i++) {
			//cout << "h: " << v[i] << endl;
			if (v[i] == 0) {
				answer += arr[idx++];
			}
			else if (v[i] == 1) {
				answer -= arr[idx++];
			}
			else if (v[i] == 2) {
				answer *= arr[idx++];
			}
			else {
				answer /= arr[idx++];
			}
		}
		minAnswer = min(minAnswer, answer);
		maxAnswer = max(maxAnswer, answer);

		return;
	}
	for (int i = 0; i < 4; i++) {
		if (com[i] == 0)
			continue;
		com[i]--;
		v.push_back(i);
		DFS(cnt+1);
		v.pop_back();
		com[i]++;
	}

}
void Solution() {
	DFS(0);
	cout << maxAnswer << endl;
	cout << minAnswer << endl;
}
void Solve() {
	Input();
	Solution();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();

	return 0;
}