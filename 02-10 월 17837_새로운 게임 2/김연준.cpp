/*
A�� ���� �̵��Ϸ��� ĭ�� ���
-> �״�� ��ĭ���� �̵�, �����ִ� �� �ٰ��� �̵� ������ �״��
->A,B,C�� D,E�� �̵��Ϸ��� ��쿡�� D,E,A,B,C

�̵��Ϸ��� ĭ�� ������
->�׿��ִ°� �ݴ�� �ٲ� 
->A,D,F,G�� E,C,B�� �̵��ϴ� ��� E,C,B,G,F,D,A
�̵��Ϸ��� ĭ�� �Ķ���  OR ���
->�̵� ���� �ݴ� ��ĭ
   ->�� ĭ�� �� �Ķ����̶�� �̵����� �ʰ� ���⸸ �ݴ�
�̵��ϴ� 

*/

//3->1->2->4
//4->2->1->3
//���� ĭ�� �÷��ִ� �ֵ���
//�ű涧 ���� �ִ� �ֵ��� ���� �Űܾ���
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct piece {
	int x;
	int y;
	int dir;
};
int N, K;
int answer = 0;
int board[12][12];
vector<int> board2[12][12];
int dx[5] = { 0,0,0,-1,1 };
int dy[5] = { 0,1,-1,0,0 };
vector<piece> piece_list;

void Input() {

	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 0; i < K; i++) {
		int x, y, dir;
		cin >> x >> y >> dir;
		//input.up_piece.push_back(i);
		piece_list.push_back(piece{x-1,y-1,dir});
		board2[x-1][y-1].push_back(i);
	}

}
bool IsRange(int x,int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}
int reverse_dir(int dir) {
	if (dir == 1) return 2;
	else if (dir == 2)return 1;
	else if (dir == 3) return 4;
	else return 3;
	
}

int Find_Index(int pieceNum) { //�ش� ĭ���� ���� ��ġ�� ��� ° ���� ��ȯ���ִ� �Լ�
	piece cur = piece_list[pieceNum];
	for (int i = 0; i < board2[cur.x][cur.y].size(); i++) {
		if (board2[cur.x][cur.y][i] == pieceNum) {
			return i;
		}
	}
}
void Move_Piece(int pieceNum,int find_index, int nx, int ny) {
	piece cur = piece_list[pieceNum];
	for (int i = find_index; i < board2[cur.x][cur.y].size(); i++) { //�ش��ϴ� ���� �� ���� ������ ���� ĭ�� �ű�� �ݺ���
		board2[nx][ny].push_back(board2[cur.x][cur.y][i]);
		piece_list[board2[cur.x][cur.y][i]].x = nx;
		piece_list[board2[cur.x][cur.y][i]].y = ny;
	}

	int size = board2[cur.x][cur.y].size();

	for (int i = find_index; i < size; i++) { //���� ĭ�� �����ϴ� ���� �� ���� ������ �����ϴ� �ݺ���
		board2[cur.x][cur.y].erase(board2[cur.x][cur.y].begin() + find_index);
	}
}
bool IsFinish(int nx,int ny) {
	return board2[nx][ny].size() >= 4;

}
void Solution() {
	while (true) {
		if (++answer > 1000)
			return;
		for (int i = 0; i < piece_list.size(); i++) {

			piece cur = piece_list[i];
			int ndir = cur.dir;
			int nx = cur.x + dx[ndir];
			int ny = cur.y + dy[ndir];
			if (!IsRange(nx,ny) || board[nx][ny] == 2) { //�Ķ���
				ndir = reverse_dir(ndir);
				nx = cur.x + dx[ndir];
				ny = cur.y + dy[ndir];
				piece_list[i].dir = ndir;
				if (board[nx][ny] == 2 ||!IsRange(nx,ny)) { //�� �Ķ���
					continue;
				}
				else if (board[nx][ny] == 0) { // �Ķ���->���
					int find_index  = Find_Index(i);
					Move_Piece(i, find_index, nx, ny);
				}
				else if (board[nx][ny] == 1) { //�Ķ���->����
					int find_index = Find_Index(i);
					reverse(board2[cur.x][cur.y].begin() + find_index, board2[cur.x][cur.y].end());
					Move_Piece(i, find_index, nx, ny);
				}
			}
			else {
				if (board[nx][ny] == 0) { //���
					int find_index = Find_Index(i);
					Move_Piece(i, find_index, nx, ny);
				}
				else if (board[nx][ny] == 1) { //������
					int find_index = Find_Index(i);
					reverse(board2[cur.x][cur.y].begin() + find_index, board2[cur.x][cur.y].end());
					Move_Piece(i, find_index, nx, ny);
				}
			}
			if (IsFinish(nx, ny)) 
				return;
		}
	}
}
void Solve() {
	Input();
	Solution();
	if (answer > 1000)
		cout << "-1" << endl;
	else
		cout << answer << endl;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();

	return 0;
}