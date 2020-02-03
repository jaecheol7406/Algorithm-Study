/*
 * 20% 틀렸습니다 
 * 반례
1 1 1 1 1 1 1 0 0 0
1 1 1 1 1 1 1 0 0 0
1 1 1 1 1 1 1 0 0 0
1 1 1 1 1 1 1 0 0 0
1 1 1 1 1 1 1 0 0 0
1 1 1 1 1 0 0 0 0 0
1 1 1 1 1 0 0 0 0 0
1 1 1 1 1 0 0 0 0 0
1 1 1 1 1 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
*/

#include <iostream>
#include <vector>
using namespace std;

struct Point {
	int r;
	int c;
};

int map[10][10];
int visited[10][10];
vector<int> sizes;
vector<Point> cands;

void Input() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			scanf("%d ", &map[i][j]);
			if (map[i][j] == 1) cands.push_back(Point{i, j});
		}
	}
}

void Print() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}

void CheckSize(int r, int c) {
	cout << "r: " << r << " c: " << c << endl;
	int stdR, stdC;
	int nums = 0;

	// 모든 좌표에 대해 1 ~ 5 사이즈 검사하는 코드
	/*for (int n = 1; n < 5; n++) { // 길이가 2인지부터 5인지까지 4번 확인한다
		
		stdR = r + n;
		stdC = c + n;
		// cout << "stdR: " << stdR << " stdC: " << stdC << endl;
		if (10 <= stdR || 10 <= stdC) {
			sizes.push_back(n);
			return;
		}
		
		for (int i = r; i <= stdR; i++) {
			for (int j = c; j <= stdC; j++) {
				if (map[i][j] == 1 && visited[i][j] != 1) {
					nums++;
					visited[i][j] = 1;
				}
			}
		}
		// cout << "nums: " << nums << endl;
		
		if (nums != (n+1) * (n+1)) {
			sizes.push_back(n);
			// cout << "push " << n << endl;

			for (int i = c; i <= stdC; i++) {
				visited[stdR][i] = 0;
			}
			for (int i = r; i <= stdR; i++) {
				visited[i][stdC] = 0;
			}

			return;
		}
		
	}
	// 길이가 5짜리
	sizes.push_back(5);*/

	// 모든 좌표에 대해 사이즈 5~1 검사하는 코드
	for (int n = 4; n >= 0; n--) {
		nums = 0;
		stdR = r + n;
		stdC = c + n;
		// cout << "stdR: " << stdR << " stdC: " << stdC << endl;

		if (10 <= stdR || 10 <= stdC) {
			continue;
		}

		for (int i = r; i <= stdR; i++) {
			for (int j = c; j <= stdC; j++) {
				if (map[i][j] == 1 && visited[i][j] != 1) {
					nums++;
					// visited[i][j] = 1;
				}
			}
		}
		cout << nums << endl;

		if (nums == (n + 1) * (n + 1)) {
			sizes.push_back(n + 1);

			for (int i = r; i <= stdR; i++) {
				for (int j = c; j <= stdC; j++) {
					visited[i][j] = 1;
				}
			}
			return;
		}
	}
	
}

void Check(int r, int c, int len) {
	int stdR = r + len;
	int stdC = c + len;

	int num = 0;
	for (int i = r; i < stdR; i++) {
		for (int j = c; j < stdC; j++) {
			if(map[i][j] == 1 && visited[i][j] == 0)
				num++;
		}
	}

	if (num == len * len) {
		sizes.push_back(len);
		for (int i = r; i < stdR; i++) {
			for (int j = c; j < stdC; j++) {
				visited[i][j] = 1;
			}
		}
	}
}

int main() {
	Input();

	/*for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (map[i][j] == 1 && visited[i][j] != 1) {
				CheckSize(i, j);
			}
		}
	}*/

	/*for (int i = 0; i < cands.size(); i++) {
		Check(cands[i].r, cands[i].c, 5);
	}*/

	for (int n = 5; n >= 1; n--) {
		for (int i = 0; i < cands.size(); i++) {
			Check(cands[i].r, cands[i].c, n);
		}
	}

	// 필요 색종이 리스트
	for (int i = 0; i < sizes.size(); i++) {
		cout << sizes[i] << " ";
	}
	cout << endl;

	int rems[6] = {0, 5, 5, 5, 5, 5};

	// 사용 전
	/*for (int i = 1; i < 6; i++) {
		cout << rems[i] << " ";
	}
	cout << endl;*/

	int used = 0;
	for (int i = 0; i < sizes.size(); i++) {
		rems[sizes[i]]--;
		used++;
	}

	// 사용 후
	/*for (int i = 1; i < 6; i++) {
		cout << rems[i] << " ";
	}
	cout << endl;*/

	for (int i = 1; i < 6; i++) {
		if (rems[i] < 0) {
			cout << "-1";
			return 0;
		}
		
	}

	cout << used;

	return 0;
}