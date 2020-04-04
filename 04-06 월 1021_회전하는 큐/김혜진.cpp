/*
function call: main 함수 하나

모든 찾아야 하는 숫자에 대해, (예시: 현재 위치가 2이고, 4를 찾아가야 한다면)
1. 2번 연산으로 숫자를 찾아가는 경우 => step: 3
○●●●○ 
2. 3번 연산으로 숫자를 찾아가는 경우 => step: 4
●●○●●
위 두 경우 중 step 수가 더 적은 것을 고르기

주의사항
1. 이미 찾아내서 큐에서 사라진 원소를 잘 고려하기
2. 원소를 찾아낸 후 그 오른쪽에 있는 원소에서 다음 round가 시작됨
*/
#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int targets[60]; // 찾아야 하는 수
int found[60]; // 이미 찾은 숫자의 값:1

int main() {

	scanf("%d %d\n", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d ", &targets[i]);
	}

	int nowNum = 1;
	int targetNum = 0;

	int sum1 = 0;
	int sum2 = 0;

	int startNum = 1;
	int endNum = 1;

	int answer = 0;

	for (int i = 0; i < M; i++) {
		targetNum = targets[i];
		sum1 = 0;
		sum2 = 0;

		// 2번 연산
		if (nowNum < targetNum) { // 현재 위치와 target 위치의 대소 비교
			startNum = nowNum;
			endNum = targetNum;
		}
		else {
			startNum = targetNum;
			endNum = nowNum;
		}

		sum1 = endNum - startNum;

		for (int j = startNum + 1; j < endNum; j++) { // 이미 찾아내서 사라진 원소는 step에서 제외
			if (found[j] == 1) {
				sum1--;
			}
		}

		// 3번 연산
		if (nowNum < targetNum) { // 현재 위치와 target 위치의 대소 비교
			startNum = targetNum;
			endNum = nowNum;
		}
		else {
			startNum = nowNum;
			endNum = targetNum;
		}
		
		sum2 = endNum + (N - startNum);
		for (int j = 1; j < endNum; j++) { // 이미 찾아내서 사라진 원소는 step에서 제외
			if (found[j] == 1) {
				sum2--;
			}
		}
		for (int j = startNum + 1; j <= N; j++) {
			if (found[j] == 1) {
				sum2--;
			}
		}

		// cout << "현재 " << nowNum << " 목표: " << targetNum << " sum1: " << sum1 << " sum2: " << sum2 << endl;
		if (sum1 <= sum2) {
			answer += sum1;
		}
		else {
			answer += sum2;
		}
		found[targetNum] = 1;

		for (int j = 1; j <= N; j++) { // 다음 시작 위치 셋팅 (targetNum 보다 오른쪽에 있는 사라지지 않고 남아 있는 원소)
			if (found[(targetNum + j) % (N + 1)] != 1 && (targetNum + j) % (N + 1) != 0) {
				nowNum = (targetNum + j) % (N + 1);
				break;
			}
		}
		// cout << "nowNum: " << nowNum << endl;

	}

	cout << answer;

	return 0;
}