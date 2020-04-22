/*
function call: main -> Input -> (Start -> Check) -> main

Brute Force
1. 맨 위 꼭지점(시작점 r,c) 를 고른다
2. 시작점 내부에서 d1, d2를 고른다
3. 고른 시작점, d1, d2 정보를 가지고 경계선을 5로 그어준다
4. 각 구역별로 시작점을 달리하면서 유권자 수를 구한다.
(경계선 5를 만나기 전까지 + 특정 범위 이전까지) 를 제한사항으로 준다.
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;
int map[25][25];
int visited[25][25];
// int numbers[6];
vector<int> numbers;
int r1, r2, r3, r4, c1, c2, c3, c4;
int allSum = 0;
int minAnswer = 99999999; // 최솟값의 max는 4000 (20*20)*100

void Input() {
	scanf("%d\n", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &map[i][j]);
			allSum += map[i][j];
		}
	}
}

void Init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[i][j] = 0;
		}
	}

	numbers.clear();
}

void Check(int r, int c, int d1, int d2) {
	Init();

	// 경계 표시
	for (int i = 1; i < d1; i++) {
		visited[r + i][c - i] = 5;
	}
	for (int i = 0; i <= d2-1; i++) {
		visited[r + d1 + i][c - d1 + i] = 5;
	}
	for (int i = 0; i <= d1-1; i++) {
		visited[r + d1 + d2 - i][c - d1 + d2 + i] = 5;
	}
	for (int i = 0; i <= d2; i++) {
		visited[r + d2 - i][c + d2 - i] = 5;
	}

	r1 = r;
	c1 = c;
	r2 = r + d1;
	c2 = c - d1;
	r3 = r2 + d2;
	c3 = c2 + d2;
	r4 = r3 - d1;
	c4 = c3 + d1;

	// 선거구 합 더하기
	int number = 0;
	// 1번 선거구를 0,0 에서부터 찾는다
	for (int i = 0; i < N; i++) {
		if (i >= r2) break;

		for (int j = 0; j < N; j++) {
			if (j > c1) break;
			if (visited[i][j] != 0) break; // 5로 표시된 애들을 감지
			number += map[i][j];
			// visited[i][j] = 1; // 답에는 필요 없으나 디버깅에 유용
		}
	}
	numbers.push_back(number);

	// 2번 선거구를 0, N-1 에서부터 찾는다
	number = 0;
	for (int i = 0; i < N; i++) {
		if (i > r4) break;
		for (int j = N - 1; j >= 0; j--) {
			if (j <= c1) break;
			if (visited[i][j] != 0) break;
			number += map[i][j];
			// visited[i][j] = 2;

		}
	}
	numbers.push_back(number);

	// 3번 선거구를 (c2, 0)에서부터 찾는다
	number = 0;
	for (int i = c2; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i][j] != 0) break;
			if (j >= c3) break;
			number += map[i][j];
			// visited[i][j] = 3;
		}
	}
	numbers.push_back(number);

	// 4번 선거구를 (r4+1, N-1 에서부터 찾는다)
	number = 0;
	for (int i = r4 + 1; i < N; i++) {
		for (int j = N - 1; j >= 0; j--) {
			if (visited[i][j] != 0) break;
			if (j < c3) break;
			number += map[i][j];
			// visited[i][j] = 4;
		}
	}
	numbers.push_back(number);

	// 5번 선거구
	number = allSum;
	for (int i = 0; i<numbers.size(); i++) {
		number -= numbers[i];
	}
	numbers.push_back(number);

	// 구역별로 잘 나뉘었는지 확인 가능
	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << visited[i][j] << " ";
		}
		cout << endl;
	}
	cout << "====================" << endl;*/

	// 구역별 유권자 수
	/*for (int i = 0; i < numbers.size(); i++) {
		cout << numbers[i] << " ";
	}
	cout << endl;*/

	// 정렬
	sort(numbers.begin(), numbers.end());

	int tmpMin = numbers[4] - numbers[0];
	// cout << "tmpMin: " << tmpMin << endl;
	if (tmpMin < minAnswer) minAnswer = tmpMin;
	
}

void Start(int r, int c) {
	int d1 = 1;
	while (r + d1 < N - 1 && c - d1 >= 0) {
		
		int d2 = 1;
		while (r + d1 + d2 < N && c - d1 + d2 < N - 1) {

			// d1, d2 구해 구역별 유권자 수 구하기
			Check(r, c, d1, d2);
			d2++;
		}

		d1++;
	}
}

int main() {

	Input();

	// 시작점 구하기
	for (int i = 0; i < N - 2; i++) {
		for (int j = 1; j < N - 1; j++) {
			Start(i, j);
		}
	}

	cout << minAnswer;

	return 0;
}