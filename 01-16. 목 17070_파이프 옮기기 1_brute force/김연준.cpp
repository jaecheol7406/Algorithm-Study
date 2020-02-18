#include <iostream>
#include <queue>
#define endl "\n"

struct Pipe {
	int x;
	int y;
	int status; //0 가로, 1 세로, 2 대각
};

using namespace std;
int N;
int MAP[20][20];
int result = 0;
Pipe start_pipe;
queue<Pipe> Pipe_list;
void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> MAP[i][j];
		}
	}
	start_pipe.x = 1;
	start_pipe.y = 2;
	start_pipe.status = 0;
}
void move_horizontal(Pipe pipe) {
	Pipe tmp;
	tmp.x = pipe.x;
	tmp.y = pipe.y + 1;
	tmp.status = 0;
	if (MAP[tmp.x][tmp.y] == 0 && tmp.y<= N) {
		Pipe_list.push(tmp);
	}
}

void move_vertical(Pipe pipe) {
	Pipe tmp;
	tmp.x = pipe.x+1;
	tmp.y = pipe.y;
	tmp.status = 1;
	if (MAP[tmp.x][tmp.y] == 0 && tmp.x <= N) {
		Pipe_list.push(tmp);
	}
}
void move_diagonal(Pipe pipe) {
	Pipe tmp;
	tmp.x = pipe.x;
	tmp.y = pipe.y;
	tmp.status = 2;
	if (tmp.y + 1 <= N && tmp.x + 1 <= N) {
		if (MAP[tmp.x+1][tmp.y] == 0 && MAP[tmp.x][tmp.y+1] == 0 && MAP[tmp.x + 1][tmp.y+1] == 0) {
			tmp.x = tmp.x + 1;
			tmp.y = tmp.y + 1;
			Pipe_list.push(tmp);
		}
	}

}
void solution() {
	Pipe_list.push(start_pipe);
	while (!Pipe_list.empty()) {
		Pipe temp = Pipe_list.front();
		Pipe_list.pop();
		if (temp.x == N && temp.y == N) {
			result++;
			continue;
		}

		if (temp.status == 0) {
			move_horizontal(temp);
			move_diagonal(temp);
		}
		else if (temp.status == 1) {
			move_vertical(temp);
			move_diagonal(temp);
		}
		else {
			move_horizontal(temp);
			move_vertical(temp);
			move_diagonal(temp);
		}

	}
	cout << result << endl;
}
void solve() {
	input();
	solution();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();
}