#include <iostream>
#include <vector>
#define endl '\n'
#define MAX 20
using namespace std;
int board[22][22];
int move_board[22][22];
int N;
int Select[5];
int result = 0;
void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
}

void move_left() {
	for (int i = 0; i < N; i++) {
		int index = 0;
		for (int j = 0; j < N; j++) {
			if (move_board[i][j] == 0)
				continue;
			if (j == N - 1) {
				if (index == j) {
					move_board[i][index++] = move_board[i][j];
				}
				else {
					move_board[i][index++] = move_board[i][j];
					move_board[i][j] = 0;

				}
				break;
			}
			for (int k = j + 1; k < N; k++) {
				if (move_board[i][k] == 0) {
					if (k == N - 1) {
						if (j == index) {
							move_board[i][index++] = move_board[i][j];
						}
						else {
							move_board[i][index++] = move_board[i][j];
							move_board[i][j] = 0;
						}
					}
					continue;
				}
				else {
					if (move_board[i][j] == move_board[i][k]) {
						if (index == j) {
							move_board[i][index++] = move_board[i][j] * 2;
							move_board[i][k] = 0;
						}
						else {
							move_board[i][index++] = move_board[i][j] * 2;
							move_board[i][k] = 0;
							move_board[i][j] = 0;
						}
						
					}
					else {
						if (index == j) {
							move_board[i][index++] = move_board[i][j];
						}
						else {
							move_board[i][index++] = move_board[i][j];
							move_board[i][j] = 0;
						}
					}
					break;
				}
			}
		}
	}
}
void move_right() {
	for (int i = 0; i < N; i++) {
		int index = N-1;
		for (int j = N-1; j >= 0; j--) {
			if (move_board[i][j] == 0)
				continue;
			if (j == 0) {
				if (index == j) {
					move_board[i][index--] = move_board[i][j];
				}
				else {
					move_board[i][index--] = move_board[i][j];
					move_board[i][j] = 0;

				}
				break;
			}
			for (int k = j -1 ; k >= 0; k--) {
				if (move_board[i][k] == 0) {
					if (k == 0) {
						if (j == index) {
							move_board[i][index--] = move_board[i][j];
						}
						else {
							move_board[i][index--] = move_board[i][j];
							move_board[i][j] = 0;
						}
					}
					continue;
				}
				else {
					if (move_board[i][j] == move_board[i][k]) {
						if (index == j) {
							move_board[i][index--] = move_board[i][j] * 2;
							move_board[i][k] = 0;
						}
						else {
							move_board[i][index--] = move_board[i][j] * 2;
							move_board[i][k] = 0;
							move_board[i][j] = 0;
						}

					}
					else {
						if (index == j) {
							move_board[i][index--] = move_board[i][j];
						}
						else {
							move_board[i][index--] = move_board[i][j];
							move_board[i][j] = 0;
						}
					}
					break;
				}
			}
		}
	}
}
void move_up() {
	for (int i = 0; i < N; i++) {
		int index = 0;
		for (int j = 0; j < N; j++) {
			if (move_board[j][i] == 0)
				continue;
			if (j == N - 1) {
				if (index == j) {
					move_board[index++][i] = move_board[j][i];
				}
				else {
					move_board[index++][i] = move_board[j][i];
					move_board[j][i] = 0;

				}
				break;
			}
			for (int k = j + 1; k < N; k++) {
				if (move_board[k][i] == 0) { ////
					if (k == N - 1) {
						if (j == index) {
							move_board[index++][i] = move_board[j][i];
						}
						else {
							move_board[index++][i] = move_board[j][i];
							move_board[j][i] = 0;
						}
					}
					continue;
				}
				else {
					if (move_board[j][i] == move_board[k][i]) {
						if (index == j) {
							move_board[index++][i] = move_board[j][i] * 2;
							move_board[k][i] = 0;
						}
						else {
							move_board[index++][i] = move_board[j][i] * 2;
							move_board[k][i] = 0;
							move_board[j][i] = 0;
						}

					}
					else {
						if (index == j) {
							move_board[index++][i] = move_board[j][i];
						}
						else {
							move_board[index++][i] = move_board[j][i];
							move_board[j][i] = 0;
						}
					}
					break;
				}
			}
		}
	}
}
void move_down() {
	for (int i = 0; i < N; i++) {
		int index = N-1;
		for (int j = N-1; j >= 0; j--) {
			if (move_board[j][i] == 0)
				continue;
			if (j == 0) {
				if (index == j) {
					move_board[index--][i] = move_board[j][i];
				}
				else {
					move_board[index--][i] = move_board[j][i];
					move_board[j][i] = 0;

				}
				break;
			}
			for (int k = j -1; k>=0; k--) {

				if (move_board[k][i] == 0) { ////
					if (k == 0) {
						if (j == index) {
							move_board[index--][i] = move_board[j][i];
						}
						else {
							move_board[index--][i] = move_board[j][i];
							move_board[j][i] = 0;
						}
					}
					continue;
				}
				else {
					if (move_board[j][i] == move_board[k][i]) {
						if (index == j) {
							move_board[index--][i] = move_board[j][i] * 2;
							move_board[k][i] = 0;
						}
						else {
							move_board[index--][i] = move_board[j][i] * 2;
							move_board[k][i] = 0;
							move_board[j][i] = 0;
						}

					}
					else {
						if (index == j) {
							move_board[index--][i] = move_board[j][i];
						}
						else {
							move_board[index--][i] = move_board[j][i];
							move_board[j][i] = 0;
						}
					}
					break;
				}
			}
		}
	}
}
void print() {
	cout << "------------------------" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << move_board[i][j] << " ";
		}
		cout << endl;
	}
	cout << "------------------------" << endl;
}
int Find_Max() {
	int max = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (move_board[i][j] > max) {
				max = move_board[i][j];
			}
		}

	}
	return max;
}
void move() {
	
	for (int i = 0; i < 5; i++) {
		
		int m = Select[i];
		if (m == 0)
			move_up();
		else if (m == 1)
			move_down();
		else if (m == 2)
			move_right();
		else if (m == 3)
			move_left();
	}
	if (Find_Max() > result)
		result = Find_Max();

}
void dfs(int Cnt) {
	if (Cnt == 5) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				move_board[i][j] = board[i][j];
			}
		}
		move();
		return;
	}
	for (int i = 0; i < 4; i++) {
		Select[Cnt] = i;
		dfs(Cnt + 1);
	}
}
void solve() {
	input();
	dfs(0);
	cout << result << endl;
}
int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();

	return 0;
}