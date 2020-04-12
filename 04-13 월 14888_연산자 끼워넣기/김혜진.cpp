/*
function call: main -> (DFS <-> Calculate) -> main

순열(순서가 있도록 뽑기)로 연산자를 골라낸다.
연산자를 골랐으면 '남은 연산자 수'를 -- 해 주어 정해진 개수만큼의 연산자만 사용한다
연산자를 N-1개 다 골랐으면, 앞에서부터 차례로 연산한다.
*/
#include <iostream>
using namespace std;

int N; // 연산자의 개수는 N-1개
int nums[15];
int ops[4];
int picked[15];
int maxNum = -1000000000;
int minNum = 1000000000;

void Input() {
	scanf("%d\n", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d ", &nums[i]);
	}

	for (int i = 0; i < 4; i++) {
		scanf("%d ", &ops[i]);
	}
}

int Calculate() {
	int sum = 0;

	if (picked[0] == 0) {
		sum = nums[0] + nums[1];
	}
	else if (picked[0] == 1) {
		sum = nums[0] - nums[1];
	}
	else if (picked[0] == 2) {
		sum = nums[0] * nums[1];
	}
	else if (picked[0] == 3) {
		sum = nums[0] / nums[1];
	}

	for (int i = 2; i < N; i++) {
		if (picked[i-1] == 0) {
			sum += nums[i];
		}
		else if (picked[i-1] == 1) {
			sum -= nums[i];
		}
		else if (picked[i-1] == 2) {
			sum *= nums[i];
		}
		else if (picked[i-1] == 3) {
			sum /= nums[i];
		}
		
	}
	return sum;
}


void DFS(int cnt) {
	if (cnt >= N - 1) {
		/*for (int i = 0; i < cnt; i++) {
			cout << picked[i];
		}
		cout << endl;*/

		int tmp = Calculate();
		if (maxNum < tmp) maxNum = tmp;
		if (minNum > tmp) minNum = tmp;

		// cout << "result: "<< tmp << endl;

		return;
	}

	for (int i = 0; i < 4; i++) {
		if (ops[i] <= 0) {
			continue;
		}

		picked[cnt] = i;
		ops[i]--;
		DFS(cnt + 1);
		ops[i]++;
	}
}

int main() {

	Input();

	DFS(0);

	cout << maxNum << endl;
	cout << minNum;

	return 0;
}