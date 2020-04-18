/*
BOJ 17140: 이차원 배열과 연산
------------------------------------------------------------------------
3x3 배열 A
R 연산 : 배열 A의 모든 행에 대해서 정렬 수행. 행 개수>= 열 개수인 경우 적용
C 연산 : 배열 A의 모든 열에 대해서 정렬 수행. 행 개수 < 열 개수인 경우 적용
등장 횟수 순으로 정렬 등장 횟수가 같으면 수의 크기 순으로 정렬
-----------------------------------------------------------------------------
연산 시 행 또는 열에 대한 값과 등장횟수를 저장하는 자료구조로 vector<num>을 사용하였다.
처음에 hashmap을 사용해서 하려했는데 정렬이 안되는 이슈로 vector<num>으로 변경. num의 struct는 값과 등장횟수를 저장.

연산 : 1.  각 행또는 열에 대해서 nums벡터에 값과 그 값의 등장횟수를 저장한다.
       2.  nums배열의 원소들을 정렬하는데, 등장횟수가 같으면 값에 대해 정렬 아니라면 등장횟수에 대해 정렬
	   2.  nums.size()*2 가 100을 넘는지 아닌지 비교한다. (nums.size()*2는 nums한 원소가 한 행이 값과 등장횟수를 저장하므로 size는 곱하기 2를 해준다.)
	   3.  기존의 배열을 0으로 세팅한 후 연산 후 값을 배열에 넣어준다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int result;
int r, c, k;
int row_num = 3;
int col_num = 3;
int   arr[101][101];
struct num {
	int val; //값
	int cnt;//등장횟수
};

vector<num> nums; //행or열 탐색 중에 각 행or열의 값과 등장횟수를 저장
				  //해시맵 느낌
bool cmp(num a, num b) {
	if (a.cnt == b.cnt)
		return a.val < b.val;
	return a.cnt < b.cnt;
}
void Input() {
	memset(arr, 0, sizeof(arr));
	cin >> r >> c >> k;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> arr[i][j];
		}
	}
}
void rCalc() {
	int flag;
	int max_col = 0;
	for (int i = 1; i <= row_num; i++) {
		nums.clear();
		for (int j = 1; j <= col_num; j++) {
			if (arr[i][j] == 0) //배열의 값이 0이면 무시
				continue;
			flag = 0;
			for (int k = 0; k < nums.size(); k++) { //nums벡터에 그 행의 값이 존재하는지 탐색 
				if (nums[k].val == arr[i][j]) {     //존재하면 등장횟수 증가
					nums[k].cnt++;
					flag = 1;
					break;
				}
			}

			if (flag == 0) {  //존재하지 않으면 그 값과 등장횟수 1을 벡터에 추가
				nums.push_back(num{ arr[i][j], 1 });
			}
		}
		sort(nums.begin(), nums.end(), cmp); //등장횟수가 같으면 값에 대해 정렬 아니라면 등장횟수에 대해 정렬

		int nums_iter = 0;
		for (int j = 1; j <= 100; j++) { //값 0으로 초기화
			arr[i][j] = 0;
		}
		if (nums.size() * 2 > 100) { //행 또는 열의 크기가 100을 넘어가는 경우
			if (max_col < 100) {
				max_col = 100;
			}
			for (int j = 1; j <= 100; j++) { //연산 후 값 세팅

				if (j % 2 == 1) { //j가 홀수면 값
					arr[i][j] = nums[nums_iter].val;
				}
				else { //j가 짝수면 등장횟수
					arr[i][j] = nums[nums_iter++].cnt;
				}
			}
		}
		else {
			if (max_col < nums.size() * 2) {
				max_col = nums.size() * 2;
			}
			for (int j = 1; j <= nums.size() * 2; j++) { //값 다시 넣기

				if (j % 2 == 1) {
					arr[i][j] = nums[nums_iter].val;
				}
				else {
					arr[i][j] = nums[nums_iter++].cnt;
				}
			}
		}
	}
	col_num = max_col; //함수가 끝날때마다 행 또는 열의 값을 최대값으로 세팅

}
void cCalc() {
	int flag;
	int max_row = 0;
	for (int i = 1; i <= col_num; i++) {
		nums.clear();

		for (int j = 1; j <= row_num; j++) {
			if (arr[j][i] == 0)
				continue;
			flag = 0;
			for (int k = 0; k < nums.size(); k++) {
				if (nums[k].val == arr[j][i]) {
					nums[k].cnt++;
					flag = 1;
					break;
				}
			}
			if (flag == 0) {
				nums.push_back(num{ arr[j][i], 1 });
			}
		}
		sort(nums.begin(), nums.end(), cmp);
		int nums_iter = 0;
		for (int j = 1; j <= 100; j++) { //값 0으로 초기화
			arr[j][i] = 0;
		}
		if (nums.size() * 2 > 100) {
			if (max_row < 100) {
				max_row = 100;
			}
			for (int j = 1; j <= 100; j++) { //값 다시 넣기

				if (j % 2 == 1) {
					arr[j][i] = nums[nums_iter].val;
				}
				else {
					arr[j][i] = nums[nums_iter++].cnt;
				}
			}
		}
		else {
			if (max_row < nums.size() * 2) {
				max_row = nums.size() * 2;
			}
			for (int j = 1; j <= nums.size() * 2; j++) { //값 다시 넣기

				if (j % 2 == 1) {
					arr[j][i] = nums[nums_iter].val;
				}
				else {
					arr[j][i] = nums[nums_iter++].cnt;
				}
			}
		}
	}
	row_num = max_row;

}
void Solution() {
	int time = 0;
	while (true) {
		if (time > 100) {
			cout << "-1" << endl;
			return;
		}
		if (arr[r][c] == k) {
			cout << time << endl;
			return;
		}

		if (row_num >= col_num) {
			rCalc();
		}
		else {
			cCalc();
		}

		time++;
	}
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