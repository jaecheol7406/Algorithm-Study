/*
BOJ 16235��: ���� ����ũ

1. �ݺ����� ���� �� ĭ�� �����ϸ鼭 �ɾ��� �ִ� ������ �ִٸ�, �� ĭ�� �������� ���� ������ �����Ѵ�. 
   =>�� ������ ���̿� �� ĭ�� ����� ���ϸ鼭 ����� ���� �� �ִ� ��, ���� ������ ���ϴ��� �����Ѵ�.
   =>��� ���� ������ �����ϸ� �ӽ� ���Ϳ� �����ϰ�, ���� �������� ������ ������ ���� �����Ѵ�.
   => �� ĭ�� ��� �����鿡 ���� ���簡 ������, �� ĭ�� �����ϴ� ������ �� �����ϰ� �ӽ� ���Ϳ� ������ ����(��� ���� ����)
      �鸸 �ٽ� �߰����ش�.
   => Summer�� ����
2. �� ĭ�� �������� ���̰� 5�� �Ǵ��� ����
   ���̰� 5�� �Ǵ� ������ �ִٸ�, ������ ĭ�� ���̰� 1�� ������ �ɾ��ش�.
3. �� ĭ�� ��� �߰�
 

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N, M, K;
int land[11][11]; //�� ĭ�� ��� ��
int addLand[11][11]; //�߰��� �������� ��� 
int dx[8] = { -1,-1,-1,0,0,+1,+1,+1 };
int dy[8] = { -1,0,+1,-1,+1,-1,0,+1 };
vector<int> tree_list[11][11]; //�� ĭ�� �ɾ��� �ִ� ���� ����Ʈ
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
			sort(tree_list[i][j].begin(), tree_list[i][j].end());//���� �� ����
			vector<int> tmp_tree;
			int add = 0;
			for (int k = 0; k < tree_list[i][j].size(); k++) {
				if (tree_list[i][j][k] <= land[i][j]) { //����� ���� �� ������
					land[i][j] -= tree_list[i][j][k];
					tmp_tree.push_back(tree_list[i][j][k] + 1);
				}
				else {
					add += (tree_list[i][j][k] / 2); //���� ���� ��� ����
				}

			}
			tree_list[i][j].clear();
			for (int k = 0; k < tmp_tree.size(); k++) {  //��Ƴ��� ���� ����
				tree_list[i][j].push_back(tmp_tree[k]);
			}
			land[i][j] += add; //Summer, ���� ���� ������ �� ��ŭ ��� �߰�

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
void PrintResult() { //��� ���
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
		//��,����,����,�ܿ� ����
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