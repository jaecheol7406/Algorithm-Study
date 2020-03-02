/*
int map[110][110];		높이 배열
int visited[110][110];	경사로를 놓았는지 여부

1. 모든 행 조사
모든 열에 대하여
  이미 경사로가 생성되어 있는 경우, 다음 열을 조사
  이번높이 != 이전높이 인 경우
    1) 이번높이 > 이전높이일 때에는 이전높이 이전 L개에 대하여 조사
	   높이 차가 1인지, 범위를 벗어나지 않는지, 이미 경사로가 놓여있지 않은지
	   => 조건을 만족하는 경우, 경사로 생성
	2) 이번높이 < 이전높이일 때에는 이번높이 이후 L개에 대하여 조사
	   높이 차가 1인지, 범위를 벗어나지 않는지, 이미 경사로가 놓여있지 않은지
	   => 조건을 만족하는 경우, 경사로 생성

마지막 열까지 조사를 마쳤을 경우, 카운터를 하나 더한다.

2. 경사로 배열을 초기화
3. 모든 열 조사: 1번과 유사하게 진행
*/
#include <iostream>
#include <stdlib.h>
using namespace std;

int map[110][110];
int visited[110][110];
int N,L;

int cnt = 0;	// 갈 수 있는 길의 개수
int before;		// 직전번 높이

void Input() {
	scanf("%d %d\n", &N, &L);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", map[i][j]);
		}
		cout << endl;
	}
}


void SearchRow() {
	for (int i = 0; i < N; i++) {
		before = map[i][0];								// 직전번 높이 초기화
		for (int j = 0; j < N; j++) {
			if (visited[i][j] == 1) {			// 경사로를 놓기로 한 곳(높이 모두 같음이 이미 검증됨)
				if (j == N - 1) {				// 마지막 위치에 경사로를 놓았을 경우 cnt++ 를 거치지 못하는 일을 방지
					cnt++;
				}
				continue;
			}
			if (map[i][j] != before) {					// 높이가 다르면
				if (abs(before - map[i][j]) != 1)break;	// 차이가 1이 아니면 조사 종료
				if (map[i][j] > before) {				// 높아졌다. (예: 2 2 3)
					if (j - L < 0) break;					// 경사로가 범위를 벗어나는 경우 행 조사 종료
					int breakFlag = 0;
					for (int t = j - L; t < j; t++) {
						if (map[i][t] != before) breakFlag = 1;		// 높이가 달라 경사로를 높을 수 없는 경우 행 조사 종료
						if (visited[i][t] != 0) breakFlag = 1;		// 이미 해당 위치에 경사로를 놓은 경우 행 조사 종료
					}
					if (breakFlag == 1) break;
					for (int t = j - L; t < j; t++) {		// 경사로를 놓는다
						visited[i][t] = 1;
					}
				}
				else if (map[i][j] < before) {			// 낮아졌다 (예: 3 2 2)
					if (j + L > N) break;					// 경사로가 범위를 벗어나는 경우 행 조사 종료
					
					int breakFlag = 0;
					for (int t = j; t < j + L; t++) {
						if (map[i][t] != map[i][j]) breakFlag=1;	// 높이가 달라 경사로를 높을 수 없는 경우 행 조사 종료
						if (visited[i][t] != 0) breakFlag=1;		// 이미 해당 위치에 경사로를 놓은 경우 행 조사 종료
					}
					if (breakFlag == 1) break;
					for (int t = j; t < j + L; t++) {		// 경사로를 놓는다
						visited[i][t] = 1;
					}
				}
			}
			before = map[i][j];
			if (j == N - 1) {
				cnt++;
			}
		}
	}
}

void SearchColumn() {
	for (int j = 0; j < N; j++) {
		before = map[0][j];								// 직전번 높이 초기화
		for (int i = 0; i < N; i++) {
			if (visited[i][j] == 1) {			// 경사로를 놓기로 한 곳(높이 모두 같음이 이미 검증됨)
				if (i == N - 1) {				// 마지막 위치에 경사로를 놓았을 경우 cnt++ 를 거치지 못하는 일을 방지
					cnt++;
					
				}
				continue;
			}
			if (map[i][j] != before) {
				if (abs(before - map[i][j]) != 1)break;	// 차이가 1이 아니면 조사 종료
				if (map[i][j] > before) {				// 높아졌다. (예: 2 2 3)
					if (i - L < 0) break;					// 경사로가 범위를 벗어나는 경우 열 조사 종료
					int breakFlag = 0;
					for (int t = i - L; t < i; t++) {
						if (map[t][j] != before) breakFlag=1;		// 높이가 달라 경사로를 높을 수 없는 경우 열 조사 종료
						if (visited[t][j] != 0) breakFlag=1;		// 이미 해당 위치에 경사로를 놓은 경우 열 조사 종료
					}
					if (breakFlag == 1) break;
					for (int t = i - L; t < i; t++) {
						visited[t][j] = 1;
					}
				}
				else if (map[i][j] < before) {				// 낮아졌다 (예: 3 2 2)
					if (i + L > N) break;					// 경사로가 범위를 벗어나는 경우 열 조사 종료
					int breakFlag = 0;
					for (int t = i; t < i + L; t++) {
						if (map[t][j] != map[i][j]) breakFlag = 1;	// 높이가 달라 경사로를 높을 수 없는 경우 열 조사 종료
						if (visited[t][j] != 0) breakFlag = 1;		// 이미 해당 위치에 경사로를 놓은 경우 열 조사 종료
					}
					if (breakFlag == 1) break;
					for (int t = i; t < i + L; t++) {
						visited[t][j] = 1;
					}
				}
			}
			before = map[i][j];
			if (i == N - 1) {
				cnt++;
			}
		}
	}
}

int main(){

	Input();

	SearchRow();

	// 경사로를 놓은 위치 리셋
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[i][j] = 0;
		}
	}

	SearchColumn();

	cout << cnt;
	return 0;
}