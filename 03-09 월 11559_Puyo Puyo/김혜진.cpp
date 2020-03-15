/*
1. DFS로 같은 것들끼리 붙은 그룹을 파악한다.
   같은 그룹은 dfs 배열에 같은 숫자로 적히게 된다. 예: 1 1
                                                       0 2
2. dfs 배열에서 그룹 및 그룹별 개수를 파악해 alreadyInGroup 배열에 넣는다.
   예: alreadyInGroup[1] = 2 / alreadyInGroup[2] = 1;

3. alreadyInGroup[i] >= 4 라면 터뜨리고 중력을 적용한다.
   1) 터뜨리기: map[i][j] = '.'
   2) 중력 적용하기: 방금 터뜨린 열(j열)에 대해서, 11번째 행부터 차례로 검사를 한다.
                     
					 btm 변수는 그 열에서 뿌요가 위치해야 하는 행 번호로,
					 최초에는 11이고 뿌요가 발견되면 -- 시킨다. (뿌요 1개 발견시, 그 다음에 발견되는 뿌요는 10번 행에 위치해야 함.)

					 11번째 행부터 검사를 하는데 뿌요가 발견됐을 경우,
					 현재 i행 != btm 이라면 그 뿌요의 아래에 공백이 있다는 것이므로,
					 i행은 비우고 btm행에 그 뿌요를 이동시킨다.

4. 이번 map 상태에서 터뜨리는 행위가 일어났다면 ctn를 true로 바꾸어 while문이 계속되게 한다.
   터뜨리는 행위가 일어나지 않았다면, while문을 탈출해 실행을 종료하게 된다.
	   
*/
#include <iostream>
using namespace std;
	
char map[15][15];										// .와 R 로 표기되는 뿌요 상태
int dfs[15][15];										// 뿌요 그룹을 나누고 위치별로 그룹 이름을 표기
int alreadyInGroup[100];								// 각 뿌요 그룹별 소속 뿌요 개수

int groupNum = 0;										// 그룹 이름을 붙일 때 사용되는 변수
bool ctn = true;										// 한 판 터뜨린 다음, 또 터뜨릴 게 있는지 검사할지 말지 결정
int boomNum = 0;										// 몇 판 돌았는지.

void Input() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			cin >> map[i][j];
		}
	}
}

void Print() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			printf("%c", map[i][j]);
		}
		cout << endl;
	}
	
}

int dir[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
void DFS(int x, int y, int cnt) {
	dfs[x][y] = groupNum;
	int tmpx, tmpy;

	for (int i = 0; i < 4; i++) {
		tmpx = x + dir[i][0];
		tmpy = y + dir[i][1];

		if (tmpx < 0 || tmpy < 0 || 12 <= tmpx || 6 <= tmpy) continue;
		if (map[tmpx][tmpy] == map[x][y] && dfs[tmpx][tmpy] == 0) {
			dfs[tmpx][tmpy] = dfs[x][y];
			DFS(tmpx, tmpy, cnt + 1);
		}
	}
}


void Init() {

	ctn = false;

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			dfs[i][j] = 0;
		}
	}

	for (int i = 0; i < groupNum; i++) {
		alreadyInGroup[i] = 0;
	}

	groupNum = 0;

}

void Down(int y) {
	int btm = 11; // 요소가 존재하는 가장 아래
	for (int i = 11; i >= 0; i--) {
		if (map[i][y] != '.') {
			if (i != btm) { // 중력을 적용해서 아래로 떨어져야 한다
				map[btm][y] = map[i][y];
				map[i][y] = '.';
			}
			btm--;
		}
	}
}


void Boom(int groupName) {
	
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			if (dfs[i][j] == groupName) {
				map[i][j] = '.'; // dfs[i][j] == groupName인 애들을 map에서 지우기

				/*cout << "중력 적용 전 =====" << endl;
				Print();*/
				
				Down(j); // j 열에 대하여 중력 적용

				/*cout << "중력 적용 후 =====" << endl;
				Print();*/
			}
		}
	}
}

int main() {

	Input();

	while (ctn) {

		Init();

		// DFS로 그룹을 나눈다
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 6; j++) {
				if (map[i][j] != '.' && dfs[i][j] == 0) {
					groupNum++;
					DFS(i, j, 0);
				}
			}
		}
		/*for (int i = 0; i < 12; i++) {        // 나눈 그룹을 확인하는 코드
			for (int j = 0; j < 6; j++) {
				cout << dfs[i][j];
			}
			cout << endl;
		}*/


		// 만들어진 그룹 파악하기
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 6; j++) {
				if (dfs[i][j] != 0) {
					alreadyInGroup[dfs[i][j]]++;
				}
			}
		}


		for (int i = 1; i <= groupNum; i++) {
			// cout << i << "번 그룹 개수: " << alreadyInGroup[i] << endl;

			// 개수가 4 이상인 그룹 터뜨리고 아래로 떨어뜨리기
			if (alreadyInGroup[i] >= 4) {
				Boom(i);
				ctn = true;									// 터진 게 있다는 표시
			}
		}
		// Print();

		if (ctn) {											// 이번 판에서 터진 게 있다면, boomNum++
			boomNum++;
		}

	}

	cout << boomNum;

	return 0;
}