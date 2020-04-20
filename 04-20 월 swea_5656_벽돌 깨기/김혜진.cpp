/*
function call: main -> Input -> (DFS -> Throw -> Cross -> Pull Count) -> main

DFS로 떨어뜨릴 열을 뽑고(순서있음, 중복있음) 차례로 해당 열에 공을 떨어뜨린다

주의점
1. Pull 함수를 놓는 위치
=> 블럭이 터지는 타이밍은 모두 같다. 즉 허공이 생겼을 때 아래로 떨어지는 것은 모두 터뜨린 이후에 해야 한다.
2. boundaryTmp의 존재와 map[r][c]=0 을 놓는 위치
=> 3짜리 블럭이 있으면 연쇄적으로 터질 애를 다 터뜨린 다음에 맨 처음 터지기를 유발한 걔를 0으로 바꿔야 한다.
*/
#include <iostream>
using namespace std;

int N, W, H; // N개 벽돌, W는 컬럼수, H는 로우수

int map[20][20];
int backup[20][20];

int minAnswer = 400;
int picked[5]; // DFS로 뽑은 떨어뜨릴 컬럼 번호

void Input() {

	minAnswer = 400;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			map[i][j] = 0;
			backup[i][j] = 0;
		}
	}

	scanf("%d %d %d\n", &N, &W, &H);
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			scanf("%d ", &map[i][j]);
			backup[i][j] = map[i][j];
		}
	}
}

void Print() {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			printf("%d ", map[i][j]);
		}
		cout << endl;
	}
}

int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
void Cross(int r, int c, int boundary) {
	int tmpR, tmpC;

	for (int i = 0; i < 4; i++) {
		tmpR = r;
		tmpC = c;
		for (int t = 0; t < boundary - 1; t++) {
			tmpR += dir[i][0];
			tmpC += dir[i][1];

			if (tmpR < 0 || tmpC < 0 || H <= tmpR || W <= tmpC) continue;

			int boundaryTmp = map[tmpR][tmpC];
			map[tmpR][tmpC] = 0;

			if (boundaryTmp > 1) {
				Cross(tmpR, tmpC, boundaryTmp);
				
			}

		}
	}
}

void Pull() { // 허공에 떠 있는 애들 땡기기
	for (int j = 0; j < W; j++) {
		int startRow = -1;
		for (int i = 0; i < H; i++) {
			if (map[i][j] != 0 && startRow == -1) startRow = i;
			if (map[i][j] == 0 && startRow >= 0) { // 밑으로 땡겨줘야 하는 경우
				for (int k = i; k > startRow; k--) {
					map[k][j] = map[k - 1][j];
				}
				map[startRow][j] = 0;
				startRow++;
			}
		}
	}
}

void Throw(int c) { // 0행 r열부터 탐색해서 제일 먼저 만나는 블럭을 깬다
	
	for (int i = 0; i < H; i++) {
		if (map[i][c] > 1) { // 제일 먼저 만난 블럭
			int boundaryTmp = map[i][c];
			map[i][c] = 0;
			Cross(i, c, boundaryTmp); // map[i][c]에서 반경(map[i][c])만큼 깨준다
			
			break;
		}
		else if (map[i][c] == 1) {
			map[i][c] = 0;
			break;
		}
	}
}

void Init() {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			map[i][j] = backup[i][j];
		}
	}
}

int Count() {
	int answer = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (map[i][j] != 0) answer++;
		}
	}
	return answer;
}


void DFS(int cnt) {
	if (cnt >= N) {
		Init();

		/*for (int i = 0; i < cnt; i++) {
			cout << picked[i] << " ";
		}
		cout << endl;*/

		for (int i = 0; i < cnt; i++) {
			Throw(picked[i]);
			Pull();
		}

		// 남은 거 세기
		int tmp = Count();
		if (tmp < minAnswer) minAnswer = tmp;
		return;
	}

	for (int i = 0; i < W; i++) {
		picked[cnt] = i;
		DFS(cnt + 1);
	}
}

int main() {

	int T;
	scanf("%d", &T);

	for (int i = 1; i <= T; i++) {
		cout << "#" << i << " ";
		Input();

		// 0~(W-1)의 숫자 중에 N개를 고른다. 중복 가능하고 순서 의미 있다.
		DFS(0);

		cout << minAnswer << endl;
	}

	return 0;
}