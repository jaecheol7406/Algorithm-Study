#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#define endl "\n"
using namespace std;

struct Cell {
	int x;
	int y;
	int life;
	bool status; //0�̸� die,1 �̸� (��)Ȱ��ȭ
	int active_time;
	int die_time;
	int born_time;
};

bool compare(Cell a, Cell b) {
	if (a.life > b.life)
		return true;
	else
		return false;
}
int MAP[350][350]; //���� �����ϰ�, ���� ���Ÿ� ���� 350*350�� ���� ����
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
int N, M, K, ans;
vector<Cell> Cells;
void Initialize() {
	memset(MAP, 0, sizeof(MAP));
	Cells.clear();
}
void Input() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int input;
			cin >> input;
			if (input == 0)
				continue;
			MAP[i + 150][j + 150] = input; //150,150 -> 0,0���� ����
			Cell cell;
			cell.x = i + 150;
			cell.y = j + 150;
			cell.life = input;
			cell.active_time = input;
			cell.die_time = input * 2;
			cell.born_time = 0;
			cell.status = true;
			Cells.push_back(cell);
		}
	}
}
void Active_check(int time) {
	vector<Cell> tmp_cells;
	for (int i = 0; i < Cells.size(); i++) {
		if (Cells[i].status == false)
			continue;
		if (Cells[i].active_time == time) { //Ȱ��ȭ �Ǵϱ� ����
			for (int j = 0; j < 4; j++) {
				int nx = Cells[i].x + dx[j];
				int ny = Cells[i].y + dy[j];

				if (MAP[nx][ny] == 0) {
					Cell cell;
					cell.x = nx;
					cell.y = ny;
					cell.life = Cells[i].life;
					cell.born_time = time + 1;
					cell.active_time = cell.born_time + cell.life;
					cell.die_time = cell.active_time + cell.life;
					cell.status = true;
					tmp_cells.push_back(cell);
				}
			}
		}
	}
	sort(tmp_cells.begin(), tmp_cells.end(), compare); //�ӽ� ���� ���� (����� �� ����)
	for (int i = 0; i < tmp_cells.size(); i++) { //���ÿ� �����ϴ� ��� ���� ū �͸� �����ϱ� ���� �ݺ���
		if (MAP[tmp_cells[i].x][tmp_cells[i].y] != 0) {
			continue;
		}
		MAP[tmp_cells[i].x][tmp_cells[i].y] = tmp_cells[i].life;
		Cells.push_back(tmp_cells[i]);
	}
}
void die_check(int time) {
	for (int i = 0; i < Cells.size(); i++) {
		if (Cells[i].die_time == time) {
			Cells[i].status = false;
		}
	}
}
void Solution() {
	for (int i = 0; i <= K; i++) {
		//0�϶��� �ʱ����
		//1�϶��� life�� 1�� �ֵ��� Ȱ�����°� ��.
		//Ȱ�����°� �Ǹ� 1�ð� ���� ������ �Ѵ�.
		//1�϶� Ȱ���ǰ� �������� ����(���Ϳ� �־��ش�?)��
		//2�϶� 1�ϋ� Ȱ��ȭ�� �ֵ��� ����. life2�� Ȱ��ȭ��.
		//Ȱ��-> ����->����
		Active_check(i);
		die_check(i);
	}
	ans = 0;
	for (int i = 0; i < Cells.size(); i++) {
		if (Cells[i].status == true) {
			//cout << Cells[i].x - 150 << " " << Cells[i].y - 150 << endl;
			if(Cells[i].born_time!=K+1)
				ans++;
			
		}
	}
}
void Solve() {
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		Initialize();
		Input();
		Solution();
		cout << "#" << i << " " << ans << endl;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Solve();
	return 0;
}