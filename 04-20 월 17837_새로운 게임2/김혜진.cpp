/*
function call: main -> Input -> (DoWhite / DoRed / DoBlue / Delete) -> main

주의점
1. 벡터에서 요소를 지울 때, for문 안에서 지우면 out of range 오류가 나므로 지울 대상을 저장해두고 for문 밖에서 지워야 한다
2. DoBlue에서 방향을 바꾸고 또다시 갈 수 있는지 검사할 때도 boundary check 해야 한다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Member {
	int n;
	int d;
	int r;
	int c;
};

int map[15][15]; // 체스판 색깔
vector<vector<vector<int>>> memNums; // 특정 위치에 있는 말의 번호(순서대로)
vector<Member> memberList; // 말 정보
int N, K;

bool cmp(Member A, Member B) {
	return A.n < B.n;
}

void Print() {
	for (int i = 0; i < memNums.size(); i++) {
		for (int j = 0; j < memNums[i].size(); j++) {
			cout << "(";
			for (int k = 0; k < memNums[i][j].size(); k++) {
				cout << memNums[i][j][k]+1 << " ";
			}
			cout << ") ";
		}
		cout << endl;
	}
	cout << "================== 끝" << endl;
}


void Input() {
	scanf("%d %d\n", &N, &K);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &map[i][j]);
		}
	}

	// mems vector에 개수만큼 생성
	vector<int> voidMems;
	vector<vector<int>> voidMems2;
	for (int i = 0; i < N; i++) {
		voidMems2.push_back(voidMems);
	}
	for (int i = 0; i < N; i++) {
		memNums.push_back(voidMems2);
	}

	int r, c, dir;
	for (int i = 0; i < K; i++) {
		scanf("%d %d %d\n", &r, &c, &dir);
		// mems[r-1][c-1].push_back(Member{ i, dir, r, c });
		memNums[r - 1][c - 1].push_back(i);
		memberList.push_back(Member{ i, dir, r-1, c-1 });
	}

	// Print();
}

int dir[5][2] = { {0, 0},  {0, 1}, {0, -1}, {-1, 0}, {1, 0} };
int dirReverse[5] = { 0, 2, 1, 4, 3 };
int tmpR, tmpC;

vector<int> deleteTarget;
void Delete(int r, int c) { // 주의점 1을 해소하는 데 사용한 함수

	for (int i = 0; i < deleteTarget.size(); i++) {
		// cout << deleteTarget[i] + 1 << " 지우기: ";
		for (int j = 0; j < memNums[r][c].size(); j++) {
			if (memNums[r][c][j] == deleteTarget[i]) {
				// cout << "memNums[" << r << "][" << c << "] 에서" << j << "번째 애를 지운다" << endl;
				memNums[r][c].erase(memNums[r][c].begin() + j);
				continue;
			}
		}
	}

	deleteTarget.clear();
}

int DoRed(int idx, int tmpR, int tmpC) {
	
	Member thisMember = memberList[idx];
	int originR = thisMember.r;
	int originC = thisMember.c;

	int startIdx = 0;
	for (int i = 0; i < memNums[thisMember.r][thisMember.c].size(); i++) {
		if (memNums[thisMember.r][thisMember.c][i] == idx) {
			startIdx = i;
			break;
		}
	}

	// 뒤에서부터 startIdx까지 옮김으로써 거꾸로 순서로 넣음
	for (int i = memNums[thisMember.r][thisMember.c].size() - 1; i >= startIdx ; i--) {
		int thisNum = memNums[thisMember.r][thisMember.c][i];
		// cout << "thisNum: " << thisNum << endl;

		memberList[thisNum].r = tmpR;
		memberList[thisNum].c = tmpC;

		memNums[tmpR][tmpC].push_back(thisNum);
		deleteTarget.push_back(thisNum);
	}
	Delete(originR, originC);

	if (memNums[tmpR][tmpC].size() >= 4) return 0;
	return -1;
}

int DoWhite(int idx, int tmpR, int tmpC) {
	Member thisMember = memberList[idx];
	int originR = thisMember.r;
	int originC = thisMember.c;

	int startIdx = 0;
	for (int i = 0; i < memNums[thisMember.r][thisMember.c].size(); i++) {
		if (memNums[thisMember.r][thisMember.c][i] == idx) {
			startIdx = i;
			break;
		}
	}

	// startIdx부터 끝까지 넣음으로써 원래 순서대로 넣음
	for (int i = startIdx; i < memNums[thisMember.r][thisMember.c].size(); i++) {
		int thisNum = memNums[thisMember.r][thisMember.c][i];

		memberList[thisNum].r = tmpR;
		memberList[thisNum].c = tmpC;

		memNums[tmpR][tmpC].push_back(thisNum);
		deleteTarget.push_back(thisNum);
	}
	Delete(originR, originC);

	if (memNums[tmpR][tmpC].size() >= 4) return 0;
	return -1;
}

int DoBlue(int idx) {
	int answer = 0;

	memberList[idx].d = dirReverse[memberList[idx].d];
	Member thisMember = memberList[idx];

	tmpR = thisMember.r + dir[thisMember.d][0];
	tmpC = thisMember.c + dir[thisMember.d][1];

	if (tmpR < 0 || tmpC < 0 || N <= tmpR || N <= tmpC || map[tmpR][tmpC] == 2) { // 주의점 2를 해소하는 코드
		return -1;
	}
	
	else if (map[tmpR][tmpC] == 0)
		answer = DoWhite(idx, tmpR, tmpC);
	else if (map[tmpR][tmpC] == 1)
		answer = DoRed(idx, tmpR, tmpC);

	return answer;
}



int main() {

	int time = 0;

	Input();

	// 말을 n 기준으로 정렬
	sort(memberList.begin(), memberList.end(), cmp);

	while (1) {
		time++;
		// cout << "===============time: " << time << "===============" << endl;
		if (time > 1000) {
			cout << -1;
			return 0;
		}

		for (int i = 0; i < K; i++) {
			// cout << i+1 << "번째 말" << endl;
			Member thisMember = memberList[i]; // 이번에 움직일 말

			tmpR = thisMember.r + dir[thisMember.d][0];
			tmpC = thisMember.c + dir[thisMember.d][1];

			if (tmpR < 0 || tmpC < 0 || N <= tmpR || N <= tmpC) {
				if (DoBlue(i) == 0) {
					cout << time;
					return 0;
				}
				// Print();
				continue;
			}
			
			if (map[tmpR][tmpC] == 1) {
				if (DoRed(i, tmpR, tmpC) == 0) {
					cout << time;
					return 0;
				}
				
			}
			else if (map[tmpR][tmpC] == 0) {
				Member thisMember = memberList[i];

				if (DoWhite(i, tmpR, tmpC) == 0) {
					cout << time;
					return 0;
				}
			}
			else if (map[tmpR][tmpC] == 2) {
				if (DoBlue(i) == 0) {
					cout << time;
					return 0;
				}
			}
			// Print();
		}
		
		
		
	}

	return 0;
}