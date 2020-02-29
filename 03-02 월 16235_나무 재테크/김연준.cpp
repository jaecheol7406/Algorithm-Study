/*
BOJ 16235번: 나무 재테크

1. 반복문을 통해 각 칸을 조사하면서 심어져 있는 나무가 있다면, 그 칸의 나무들을 나이 순으로 정렬한다. 
   =>각 나무의 나이와 그 칸의 양분을 비교하면서 양분을 먹을 수 있는 지, 죽은 나무로 변하는지 조사한다.
   =>살아 남은 나무가 존재하면 임시 벡터에 저장하고, 죽은 나무들의 나이의 절반을 합을 저장한다.
   => 그 칸의 모든 나무들에 대한 조사가 끝나면, 그 칸에 존재하는 나무를 다 삭제하고 임시 벡터에 저장해 놓은(살아 남은 나무)
      들만 다시 추가해준다.
   => Summer를 진행
2. 각 칸의 나무들의 나이가 5가 되는지 조사
   나이가 5가 되는 나무가 있다면, 인접한 칸에 나이가 1인 나무를 심어준다.
3. 각 칸의 양분 추가
 

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N, M, K;
int land[11][11]; //각 칸의 양분 양
int addLand[11][11]; //추가로 더해지는 양분 
int dx[8] = { -1,-1,-1,0,0,+1,+1,+1 };
int dy[8] = { -1,0,+1,-1,+1,-1,0,+1 };
vector<int> tree_list[11][11]; //각 칸에 심어져 있는 나무 리스트
void Input() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> addLand[i][j];
			land[i][j] = 5;
		}
	}
	int x, y,z;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> z;
		tree_list[x][y].push_back(z);
	}
}
void SpringToSummer() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (tree_list[i][j].size() == 0)
				continue;
			sort(tree_list[i][j].begin(), tree_list[i][j].end());//나이 순 정렬
			vector<int> tmp_tree;
			int add = 0;
			for (int k = 0; k < tree_list[i][j].size(); k++) {
				if (tree_list[i][j][k] <= land[i][j]) { //양분을 먹을 수 있으면
					land[i][j] -= tree_list[i][j][k];
					tmp_tree.push_back(tree_list[i][j][k] + 1);
				}
				else {
					add += (tree_list[i][j][k] / 2); //죽은 나무 양분 조사
				}

			}
			tree_list[i][j].clear();
			for (int k = 0; k < tmp_tree.size(); k++) {  //살아남은 나무 갱신
				tree_list[i][j].push_back(tmp_tree[k]);
			}
			land[i][j] += add; //Summer, 죽은 나무 나이의 반 만큼 양분 추가

		}
	}
}
void Fall() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (tree_list[i][j].size() == 0)
				continue;
			for (int k = 0; k < tree_list[i][j].size(); k++) {
				if (tree_list[i][j][k]%5==0) {
					for (int l = 0; l < 8; l++) {
						int nx = i + dx[l];
						int ny = j + dy[l];
						if (nx<1 || nx>N || ny<1 || ny>N) {
							continue;
						}
						tree_list[nx][ny].push_back(1);
					}
				}
			}
		}
	}

}
void Winter() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			land[i][j] += addLand[i][j];
		}
	}
}
void PrintResult() { //결과 출력
	int result = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			result += tree_list[i][j].size();
		}
	}
	cout << result << endl;
}
void Solution() {
	for (int i = 1; i <= K; i++) {
		//봄,여름,가을,겨울 돌고
		SpringToSummer();
		Fall();
		Winter();
	}
	PrintResult();
}
void Solve() {
	Input();
	Solution();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();

	return 0;
}