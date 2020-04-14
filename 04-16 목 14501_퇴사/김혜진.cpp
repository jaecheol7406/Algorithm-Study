/*
function call: main -> Input -> DFS -> main

브루트포스로 가능한 모든 날짜의 조합을 구해, price를 더한다.
    - 날짜를 하나 고른 후에는, (그 날짜 + 걸리는 기간)째 번 날짜부터 고려 가능하다.
	  (예: 예제입력1에서 1일째 상담(3일짜리)을 고르면, (1+3)=4일째 상담 이후부터 고를 수 있다.)
    - 즉 (이전번에 고른 상담 시작날짜 + 걸리는 기간) <= N+1 인 것만 고를 수 있는 것이다.
*/
#include <iostream>
#include <vector>
using namespace std;

struct Cns {
	int t;
	int p;
};

int N;
Cns cns[20];
int maxPrice = 0;
vector<int> picked;

void Input() {
	scanf("%d\n", &N);

	int t, p;
	for (int i = 1; i <= N; i++) {
		scanf("%d %d\n", &t, &p);
		cns[i] = Cns{ t, p };
	}
}

void DFS(int pre) {

	for (int i = pre; i <= N; i++) {
		if (i + cns[i].t <= N+1) {
			picked.push_back(i);
			DFS(i + cns[i].t);
			picked.pop_back();
		}
	}

	// pre == N+1 또는 더이상 push할 것이 없어 DFS호출 안한 때
	/*cout << "completed: ";
	for (int i = 0; i < picked.size(); i++) {
		cout << picked[i] << " ";
	}
	cout << endl;*/
	int sumValue = 0;
	for (int i = 0; i < picked.size(); i++) {
		sumValue += cns[picked[i]].p;
	}
	if (sumValue > maxPrice) maxPrice = sumValue;
	return;
}

int main() {
	Input();

	DFS(1);

	cout << maxPrice;

	return 0;
}