/*
BOJ 17141 ���ÿ�

 ������� 1. ���� �� ���� ����� ���
 ������� 2. �� �����̰� �� �� ���� ������ �ִٸ� ū �� ���� �� ��ƸԴ´�.

*/
#include <iostream>
#include <vector>
using namespace std;
int dx[5] = { 0,-1,+1,0,0 };
int dy[5] = { 0,0,0,+1,-1 };
struct shark {
	int r;
	int c;
	int s;
	int d;
	int z;
};
struct king_struct {
	int c;
};
int main() {
	int R, C, M;
	cin >> R >> C >> M;
	vector<shark> shark_list;
	for (int i = 0; i < M; i++) {
		shark input;
		cin >> input.r >> input.c >> input.s >> input.d >> input.z;
		shark_list.push_back(input);

	}

	king_struct king;
	king.c = 0;
	int result = 0;
	for (int i = 0; i < C; i++) {
		king.c++;
		int r_min = R + 1;
		int min_index = -1;
		for (int j = 0; j < shark_list.size(); j++) {//��Ƹ��� �� �ִ��� üũ

			//1. ���� ����� �������?
			if (king.c == shark_list[j].c) {
				if (r_min > shark_list[j].r) {
					r_min = shark_list[j].r;
					min_index = j;
				}
			}
		}
		if (min_index != -1) { //��Ƹ����� �ִ� ���
			result += shark_list[min_index].z;
			shark_list.erase(shark_list.begin() + min_index);
		}
		int board[102][102] = { 0, };
		for (int j = 0; j < shark_list.size(); j++) { //��� �̵�
			int nr, nc, ndir,ns; //��� �̵��� ���� �ӽ� ����
			nr = shark_list[j].r;
			nc = shark_list[j].c;
			ndir = shark_list[j].d;
			ns = shark_list[j].s;
			if (ndir == 1 || ndir == 2) { //�̵��Ÿ� �ּ�ȭ
				ns = ns % ((R - 1) * 2);
			}
			else if(ndir == 3 || ndir==4){
				ns = ns % ((C - 1) * 2);
			}
			for (int k = 0; k < ns; k++) { //�̵� �� �������̸� ���� �ݴ� �ӷ� ����
				if (((nr == 1) && ndir == 1) || ((nc == C) && ndir == 3)) { //������ üũ
					ndir += 1;
				}
				else if (((nr == R) && ndir == 2) || ((nc == 1) && ndir == 4)) { //������ üũ
					ndir -= 1;
				}
				nr = nr + dx[ndir]; //������
				nc = nc + dy[ndir];
			}

			shark_list[j].r = nr; //�̵� �� ����� status
			shark_list[j].c = nc;
			shark_list[j].d = ndir;

			if (board[shark_list[j].r][shark_list[j].c] == 0) { //������ �� �ش� ��ǥ�� ��� �ִ��� üũ
				board[shark_list[j].r][shark_list[j].c] = 1;
			}
			else {
				for (int k = 0; k < j; k++) { //�ش� ��ǥ�� �� �ִٸ� ������ �� ã�Ƽ� ���� �̵��� ���� ��
					if (shark_list[j].r == shark_list[k].r && shark_list[j].c == shark_list[k].c) {
						if (shark_list[j].z > shark_list[k].z) {
							shark_list.erase(shark_list.begin() + k);
						}
						else{
							shark_list.erase(shark_list.begin() + j);
							
						}
						j--; //vector�� erase�ϸ� ��ĭ�� ������Ƿ� �ݺ����� ������ ���ҽ��Ѿ� ��.
						break;
					}
				}
			}
		}
	}
	cout << result;
	return 0;
}