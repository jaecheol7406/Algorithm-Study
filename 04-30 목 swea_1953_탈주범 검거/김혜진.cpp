/*
이동가능하기 위해서는
   1. 현재 r,c 위치에서 갈 수 있는 파이프 방향을 계산한다
   2. 이동 후 도착할 r,c, 위치에서 받아들일 수 있는 파이프 방향인지 계산한다
*/
#include <iostream>
#include <vector>
using namespace std;

struct Pos {
	int r;
	int c;
};

int N, M, R, C, L;
int map[55][55];
int visited[55][55];
vector<Pos> pos;
vector<Pos> added;

void Input() {
	cin >> N >> M >> R >> C >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
            map[i][j] = 0;
            visited[i][j] = 0;
			cin >> map[i][j];
		}
	}
}

bool CanGo(int dir, int r, int c) {
	int value = map[r][c];

	if (value == 1) return true;

	if (dir == 0) {
		if (value == 2 || value == 4 || value == 7) return true;
		else return false;
	}
	else if (dir == 1) {
		if (value == 2 || value == 5 || value == 6) return true;
		else return false;
	}
	else if (dir == 2) {
		if (value == 3 || value == 6 || value == 7) return true;
		else return false;
	}
	else if (dir == 3) {
		if (value ==3 || value ==4 || value ==5) return true;
		else return false;
	}

	return false;
}

int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int match[6][2] = { {0, 1}, {2, 3}, {1, 2}, {0, 2}, {0, 3}, {1, 3} };
void Go(int r, int c) {
	int tmpR, tmpC;

	if (map[r][c] != 1) { // 2방향
		for (int i = 0; i < 2; i++) {
			int tmpDir = match[(map[r][c] - 2)][i];
			tmpR = r + dir[tmpDir][0];
			tmpC = c + dir[tmpDir][1];

			if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) continue;
			if (map[tmpR][tmpC] == 0) continue;
			if (visited[tmpR][tmpC] == 1) continue;
			if (!CanGo(tmpDir, tmpR, tmpC)) continue;

			visited[tmpR][tmpC] = 1;
			added.push_back(Pos{ tmpR, tmpC });
		}
	}
	else { // 4방향
		for (int i = 0; i < 4; i++) {
			tmpR = r + dir[i][0];
			tmpC = c + dir[i][1];

			if (tmpR < 0 || tmpC < 0 || N <= tmpR || M <= tmpC) continue;
			if (map[tmpR][tmpC] == 0) continue;
			if (visited[tmpR][tmpC] == 1) continue;
			if (!CanGo(i, tmpR, tmpC)) continue;

			visited[tmpR][tmpC] = 1;
			added.push_back(Pos{ tmpR, tmpC });
		}
	}
}

int main() {
    
    int tCase;
    cin >> tCase;
    
    for(int t=1; t<=tCase; t++) {
        Input();
        pos.clear();

        int time = 1;
        pos.push_back(Pos{ R, C });
        visited[R][C] = 1;

        int tmpR, tmpC;

        while (time < L) {
            // cout << "time: " << time << endl;

            int posNum = pos.size();
            for (int i = 0; i < pos.size(); i++) {
                // cout << "r: " << pos[i].r << " c: " << pos[i].c << endl;
                Go(pos[i].r, pos[i].c);
            }

            pos.erase(pos.begin(), pos.begin() + (posNum - 1));

            for (int i = 0; i < added.size(); i++) {
                pos.push_back(Pos{ added[i].r, added[i].c });
            }
            added.clear();

            time++;
        }

        int cnt = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (visited[i][j] == 1) cnt++;
                //cout << visited[i][j];
            }
            //cout << endl;
        }

        cout << "#" << t << " " << cnt << endl;
    }

	

	return 0;
}