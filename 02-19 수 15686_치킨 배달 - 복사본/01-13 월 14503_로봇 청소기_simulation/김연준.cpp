#include <iostream>

using namespace std;

int map[52][52];
int dx[4] = { -1, 0, 1, 0 }; //0 북,1 동, 2 남, 3서
int dy[4] = { 0, 1,0,-1 };
int main() {
	int N, M, now_r,now_c,now_d;
	int result = 0;
	cin >> N >> M;
	cin >> now_r >> now_c >> now_d;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	bool check=true;
	while (check) {
		if (map[now_r][now_c] == 0)
			result++;
		map[now_r][now_c] = 2; //청소
		for (int i = 0; i < 5; i++) {
			if (i == 4) {
				int nd= (now_d + 2) % 4;
				now_r = now_r + dx[nd];
				now_c = now_c + dy[nd];
				if(map[now_r][now_c]==1){
					
					check = false;
				}
				break;
			}
			int nr, nc;
			now_d = (now_d + 3) % 4;
			nr = now_r + dx[now_d];
			nc = now_c + dy[now_d];
			if (map[nr][nc] == 0) {
				now_r = nr;
				now_c = nc;
				break;
			}


		}

	}
	cout << result << endl;


	return 0;
}