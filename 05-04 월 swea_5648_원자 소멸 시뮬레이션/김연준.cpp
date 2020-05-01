/*
SWEA 5648��: ���� �Ҹ� �ùķ��̼�
���� ���� : �ùķ��̼�

1. atom struct�� ��ǥ,����,������,�Ҹ���¸� �ǹ�
2. �Է� ��ǥ�� -1000~1000�̹Ƿ� �Է¹��� ��ǥ���� +1000�� ���༭ �ʿ� ǥ�� �����ϰ� �Ѵ�.
3. ���� �� ��ǥ�� �����ϴ� ������ ���� board�� ǥ���Ѵ�.
4. (���ڵ��� �����̰�(move) -> �Ҹ��ϴ��� Ȯ��(CheckMeet) -> ��� ���Ұ� �Ҹ������� ����)�� �ݺ��Ѵ�.
5. ������ ��, ������ ��ġ�� ���� ����� �Ҹ�ó��(�ٸ� ���ڿ� ���� �� ����)
6. CheckMeet
    (1) ���ڵ��� �� ��ġ�� �ƴ� �߰���(ex) 1.5��)���� �������� Ȯ���� ���� �ϰ� ������ �Ҹ�
        -> Ȯ���Ϸ��� ������ ���� ��ġ�� ���ڰ� �ְ�, �� ������ ����� ���� Ȯ���Ϸ��� ������ ������ �ݴ� ����(OpDir)�̸� 
            �߰����� ���� �����̹Ƿ� �Ҹ��Ŵ.
    (2) �� ��ġ���� �������� Ȯ���ϰ� ������ �Ҹ�
        -> Ȯ���Ϸ��� ������ ��ġ�� ���ڵ��� 2�� �̻��̸� ���� ���̹Ƿ� �Ҹ��Ŵ.

*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
struct atom {
    int x;
    int y;
    int dir;
    int k;
    bool live;
};
int N;
vector<atom> atom_list;
int board[2001][2001];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };
int result;
void Input() {
    cin >> N;
    int x, y, dir, k;
    for (int i = 0; i < N; i++) {
        cin >> x >> y >> dir >> k;
        x += 1000;
        y += 1000;
        atom_list.push_back({ x,y,dir,k,true });
        board[x][y] = 1;
    }//(y,x)�� ����.
}
void Initialize() {
    atom_list.clear();
    memset(board, 0, sizeof(board));
    result = 0;
}
bool IsFinish() {
    for (int i = 0; i < atom_list.size(); i++) {
        if (atom_list[i].live == true)
            return false;
    }
    return true;
}
void Move() {
    for (int i = 0; i < atom_list.size(); i++) {
        atom cur = atom_list[i];
        if (cur.live == false)
            continue;
        int nx = cur.x + dx[cur.dir];
        int ny = cur.y + dy[cur.dir];
        if (nx < 0 || ny < 0 || nx>2000 || ny>2000) {
            board[cur.x][cur.y]--;
            cur.live = false;
        }
        else {
            board[cur.x][cur.y]--;
            cur.x = nx;
            cur.y = ny;
            board[cur.x][cur.y]++;
        }
        atom_list[i] = cur;
    }
}
bool OpDir(int& d, int& d2) {
    if (d == 0 || d == 2) {
        if (d2 == d + 1)
            return true;
    }
    else if (d == 1 || d == 3) {
        if (d2 == d - 1)
            return true;
    }
    return false;
}
void CheckMeet() {
    for (int i = 0; i < atom_list.size(); i++) { //�߰��� ������ �Ҹ��ϴ� ���
        atom cur = atom_list[i];
        if (!cur.live)
            continue;
        if (board[cur.x - dx[cur.dir]][cur.y - dy[cur.dir]] > 0) {
            for (int j = 0; j < atom_list.size(); j++) {
                if (i == j || !atom_list[j].live)
                    continue;
                if (atom_list[j].x == cur.x - dx[cur.dir] && atom_list[j].y == cur.y - dy[cur.dir]) {
                    if (OpDir(cur.dir, atom_list[j].dir)) {
                        result += atom_list[i].k + atom_list[j].k;
                        atom_list[i].live = false;
                        atom_list[j].live = false;
                        board[atom_list[i].x][atom_list[i].y]--;
                        board[atom_list[j].x][atom_list[j].y]--;
                        break;
                    }
                }
            }
        }
    }
    for (int i = 0; i < atom_list.size(); i++) { //�� ��ġ���� ������ �Ҹ��ϴ� ���
        atom cur = atom_list[i];
        if (!cur.live)
            continue;
        if (board[cur.x][cur.y] >= 2) {
            for (int j = 0; j < atom_list.size(); j++) {
                if (i == j || !atom_list[j].live)
                    continue;
                if (atom_list[j].x == cur.x && atom_list[j].y == cur.y) {
                    board[atom_list[j].x][atom_list[j].y]--;
                    atom_list[j].live = false;
                    result += atom_list[j].k;
                }
            }
            atom_list[i].live = false;
            board[atom_list[i].x][atom_list[i].y]--;
            result += atom_list[i].k;
        }
    }
}
void Solution() {
    while (true) {
        if (IsFinish()) {
            break;
        }
        Move();
        CheckMeet();
    }
}
void Solve() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        Initialize();
        Input();
        Solution();
        cout << "#" << i << " " << result << endl;
    }
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}