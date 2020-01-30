#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Pos {
	int r;
	int c;
	int cnt=0;
};
vector<Pos> cand;

int N, M;
int map[60][60];
int backup[60][60];
int visited[60][60];

int time;
int total;
vector<int> pick;
int Select[15];
int Min = 99999999;

int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int actNum;

void Input() {
	scanf("%d %d\n", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &map[i][j]);
			backup[i][j] = map[i][j];

			if (map[i][j] == 2) {
				cand.push_back(Pos{ i, j, 0 });
			}

			if (map[i][j] == 0) {
				total++;
			}
		}
	}
}

void Init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = backup[i][j];
			visited[i][j] = 0;
		}
	}
	time = 0;
	actNum = 0;
}

void Print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void PrintVector() {
	for (int i = 0; i < cand.size(); i++) {
		printf("%d, %d  ", cand[i].r, cand[i].c);
	}
}



queue<Pos> q;
void BFS() {
	int tmp = 0;
	while (actNum != total) {
		if (q.empty()) {
			tmp = -1;
			break;
		}
		Pos thisTurn = q.front();
		tmp = thisTurn.cnt;
		q.pop();
		// printf("tmp: %d\n", tmp);

		int r = thisTurn.r;
		int c = thisTurn.c;

		int rtmp, ctmp;
		for (int i = 0; i < 4; i++) {
			rtmp = r + dir[i][0];
			ctmp = c + dir[i][1];

			if (rtmp < 0 || N <= rtmp || ctmp < 0 || N <= ctmp) continue;
			if (visited[rtmp][ctmp] == 1 || map[rtmp][ctmp] == 1) continue;
			visited[rtmp][ctmp] = 1;

			if(map[rtmp][ctmp] == 0)
				actNum++;

			map[rtmp][ctmp] = 3;
			
			q.push(Pos{ rtmp, ctmp, thisTurn.cnt + 1 });
		}
		/*printf("걸린 시간: %d\n", thisTurn.cnt+1);
		Print();*/
	}
	//printf("%d초 총 걸림=============\n", tmp + 1);
	
	while (!q.empty()) {
		q.pop();
	}

	if (tmp == 0 && Min > tmp) {
		Min = tmp;
	}
	else if (tmp != -1 && Min > (tmp + 1)) {
		Min = tmp + 1;
	}
}


void Go() { // 활성화된 바이러스 자리를 확정하고 DFS 호출

	for (int i = 0; i < pick.size(); i++) {
		Pos thisPick = Pos{ cand[pick[i]].r, cand[pick[i]].c, 0 };
		map[thisPick.r][thisPick.c] = 3; // 3이 활성화된 바이러스

		visited[thisPick.r][thisPick.c] = 1;
		q.push(thisPick);
	}
	//Print();
	BFS();
}



void Pick(int pos) {

	if (pick.size() >= M) { // 활성화 바이러스를 뽑으면

		/*for (int i = 0; i < pick.size(); i++) {
			printf("%d ", pick[i]);
		}
		printf("\n");*/
		Go();
		// Print();

		Init();

		return;
	}

	for (int i = pos; i < cand.size(); i++) {
		if (Select[i] == 1) continue;
		pick.push_back(i);
		Select[i] = 1;
		
		Pick(i + 1);

		Select[i] = 0;
		pick.pop_back();
	}
}

int main() {

	Input();
	/*Print();
	PrintVector();*/
	Pick(0);

	if (Min == 99999999) 
		printf("-1");
	else
		printf("%d", Min);

	return 0;
}