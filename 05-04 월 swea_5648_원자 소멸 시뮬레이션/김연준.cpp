/*
SWEA 5648번: 원자 소멸 시뮬레이션
문제 유형 : 시뮬레이션

1. atom struct는 좌표,방향,에너지,소멸상태를 의미
2. 입력 좌표가 -1000~1000이므로 입력받은 좌표값에 +1000을 해줘서 맵에 표시 가능하게 한다.
3. 맵의 각 좌표에 존재하는 원자의 수를 board에 표시한다.
4. (원자들이 움직이고(move) -> 소멸하는지 확인(CheckMeet) -> 모든 원소가 소멸했으면 종료)를 반복한다.
5. 움직일 때, 원자의 위치가 맵을 벗어나면 소멸처리(다른 원자와 만날 수 없음)
6. CheckMeet
    (1) 원자들이 정 위치가 아닌 중간에(ex) 1.5초)에서 만나는지 확인을 먼저 하고 만나면 소멸
        -> 확인하려는 원자의 이전 위치에 원자가 있고, 그 원자의 방향과 현재 확인하려는 원자의 방향이 반대 방향(OpDir)이면 
            중간에서 만난 원자이므로 소멸시킴.
    (2) 정 위치에서 만나는지 확인하고 만나면 소멸
        -> 확인하려는 원자의 위치에 원자들이 2개 이상이면 만난 것이므로 소멸시킴.

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
    }//(y,x)로 접근.
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
    for (int i = 0; i < atom_list.size(); i++) { //중간에 만나서 소멸하는 경우
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
    for (int i = 0; i < atom_list.size(); i++) { //정 위치에서 만나서 소멸하는 경우
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