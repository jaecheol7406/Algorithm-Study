/*
BOJ 17141 낚시왕

 고려사항 1. 낚시 시 가장 가까운 상어
 고려사항 2. 상어가 움직이고 난 후 같은 공간에 있다면 큰 상어가 작은 상어를 잡아먹는다.

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
		for (int j = 0; j < shark_list.size(); j++) {//잡아먹을 상어가 있는지 체크

			//1. 제일 가까운 상어인지?
			if (king.c == shark_list[j].c) {
				if (r_min > shark_list[j].r) {
					r_min = shark_list[j].r;
					min_index = j;
				}
			}
		}
		if (min_index != -1) { //잡아먹을게 있는 경우
			result += shark_list[min_index].z;
			shark_list.erase(shark_list.begin() + min_index);
		}
		int board[102][102] = { 0, };
		for (int j = 0; j < shark_list.size(); j++) { //상어 이동
			int nr, nc, ndir,ns; //상어 이동을 위한 임시 변수
			nr = shark_list[j].r;
			nc = shark_list[j].c;
			ndir = shark_list[j].d;
			ns = shark_list[j].s;
			if (ndir == 1 || ndir == 2) { //이동거리 최소화
				ns = ns % ((R - 1) * 2);
			}
			else if(ndir == 3 || ndir==4){
				ns = ns % ((C - 1) * 2);
			}
			for (int k = 0; k < ns; k++) { //이동 시 격자판이면 방향 반대 속력 유지
				if (((nr == 1) && ndir == 1) || ((nc == C) && ndir == 3)) { //격자점 체크
					ndir += 1;
				}
				else if (((nr == R) && ndir == 2) || ((nc == 1) && ndir == 4)) { //격자점 체크
					ndir -= 1;
				}
				nr = nr + dx[ndir]; //움직임
				nc = nc + dy[ndir];
			}

			shark_list[j].r = nr; //이동 후 상어의 status
			shark_list[j].c = nc;
			shark_list[j].d = ndir;

			if (board[shark_list[j].r][shark_list[j].c] == 0) { //움직인 후 해당 좌표에 상어 있는지 체크
				board[shark_list[j].r][shark_list[j].c] = 1;
			}
			else {
				for (int k = 0; k < j; k++) { //해당 좌표에 상어가 있다면 기존의 상어를 찾아서 새로 이동한 상어와 비교
					if (shark_list[j].r == shark_list[k].r && shark_list[j].c == shark_list[k].c) {
						if (shark_list[j].z > shark_list[k].z) {
							shark_list.erase(shark_list.begin() + k);
						}
						else{
							shark_list.erase(shark_list.begin() + j);
							
						}
						j--; //vector를 erase하면 한칸씩 당겨지므로 반복문의 변수를 감소시켜야 함.
						break;
					}
				}
			}
		}
	}
	cout << result;
	return 0;
}