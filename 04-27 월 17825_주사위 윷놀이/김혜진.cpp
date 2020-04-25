#include <iostream>
using namespace std;

int cube[10]; // 주사위 던져 나온 숫자
int horse[4]; // 각 말의 위치(몇 번 점수를 밟고 있는지)

// 0열은 점수판, 1열은 말의 점유 여부
int redmap[2][20]; // 인덱스를 넘어가려고 하면 '도착'
int bluemap1[2][3]; // 인덱스를 넘어가려고 하면 bluemap4으로 간다
int bluemap2[2][2]; // 인덱스를 넘어가려고 하면 bluemap4으로 간다
int bluemap3[2][3]; // 인덱스를 넘어가려고 하면 bluemap4으로 간다
int bluemap4[2][2]; // 인덱스를 넘어가려고 하면 redmap[19]로 간다

void DFS(int cnt) {
	if (cnt >= 10) {

		return;
	}

	for (int i = 0; i < 4; i++) { // cnt번 턴에는 i번 말이 움직인다
		if (horse[i] == 10) {

		}
		else if (horse[i] == 20) {
			
		}
		else if (horse[i] == 30) {

		}
		else if (horse[i] == 25) {

		}
		else { // 그냥 redmap 이용하면 됨
			// cube[cnt] 만큼 이동해야 됨

		}
	}
}

int main() {

	for (int i = 0; i < 10; i++) {
		scanf("%d ", &cube[i]);
	}
	
	// 점수판 만들기
	for (int i = 0; i < 20; i++) {
		redmap[0][i] = (i + 1) * 2;
	}
	for (int i = 0; i < 3; i++) {
		bluemap1[0][i] = 13 + (3 * i);
		bluemap3[0][i] = 28 - i;
	}
	for (int i = 0; i < 2; i++) {
		bluemap2[0][i] = 22 + (2 * i);
		bluemap4[0][i] = 30 + (5 * i);
	}

	DFS(0);

	return 0;
}