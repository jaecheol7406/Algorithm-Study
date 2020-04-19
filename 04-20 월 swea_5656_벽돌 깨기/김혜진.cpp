/*
디버깅중
function call: main -> Input -> (DFS -> Throw -> Cross -> Count) -> main

DFS로 떨어뜨릴 열을 뽑는다.
*/
#include <iostream>
using namespace std;

int N, W, H; // N개 벽돌, W는 컬럼수, H는 로우수
int map[20][20];
int backup[20][20];
int visited[20][20];

void Input() {
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
	cout << r << "," << c << " 에서 " << boundary << "만큼 깨기" << endl;
	map[r][c] = 0;
	// visited[r][c] = 1;
	int tmpR, tmpC;

	for (int i = 0; i < 4; i++) {
		tmpR = r;
		tmpC = c;
		for (int t = 0; t < boundary - 1; t++) {
			tmpR += dir[i][0];
			tmpC += dir[i][1];

			if (tmpR < 0 || tmpC < 0 || H <= tmpR || W <= tmpC) continue;
			if (map[tmpR][tmpC] == 0) continue;
			
			if (map[tmpR][tmpC] == 1) {
				map[tmpR][tmpC] = 0;
			}
			else {
				Cross(tmpR, tmpC, map[tmpR][tmpC]);
				map[tmpR][tmpC] = 0;
			}

			/*Cross(tmpR, tmpC, map[tmpR][tmpC]);
			map[tmpR][tmpC] = 0;*/
			
		}
	}
	// cout << "땡기기 전====" << endl;
	// Print();

	// 허공에 떠 있는 애들 땡기기
	for (int j = 0; j < W; j++) {
		int startRow = -1;
		for (int i = 0; i < H; i++) {
			if (map[i][j] != 0 && startRow == -1) startRow = i;
			if (map[i][j] == 0 && startRow >= 0) { // 밑으로 땡겨줘야 하는 경우
				// cout << i << " " << j << " 땡겨줘야 함, startRow: " << startRow << endl;
				for (int k = i; k > startRow; k--) {
					map[k][j] = map[k - 1][j];
				}
				map[startRow][j] = 0;
				startRow++;
			}
		}
	}
	// cout << "땡긴 후====" << endl;
	// Print();
}

void Throw(int c) {
	// 0행부터 탐색해서 제일 먼저 만나는 블럭을 깬다
	for (int i = 0; i < H; i++) {
		if (map[i][c] != 0) { // 제일 먼저 만난 블럭
			// cout << "i: " << i << " c: " << c  << " =" << map[i][c]<< endl;
			Cross(i, c, map[i][c]); // map[i][c]에서 반경(map[i][c])만큼 깨준다

			return;
		}
	}
}

void Init() {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			map[i][j] = backup[i][j];
			visited[i][j] = 0;
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

int minAnswer = 400;
int picked[5];
void DFS(int cnt) {
	if (cnt >= N) {
		Init();

		for (int i = 0; i < cnt; i++) {
			cout << picked[i] << " ";
		}
		cout << endl;

		for (int i = 0; i < cnt; i++) {
			Throw(picked[i]);
			Print();
		}

		// 남은 거 세기
		int tmp = Count();
		
		cout << "남은 수: " << tmp << endl;
		if (tmp < minAnswer) minAnswer = tmp;
		return;
	}

	for (int i = 0; i < W; i++) {
		picked[cnt] = i;
		DFS(cnt + 1);
	}
}

int main() {

	Input();
	// Print();
	

	// 0번 컬럼에서 돌을 떨어뜨려본다
	// Throw(1);

	// 0~(W-1)의 숫자 중에 N개를 고른다. 중복 가능하고 순서 의미 있다.
	DFS(0);

	cout << minAnswer;

	return 0;
}