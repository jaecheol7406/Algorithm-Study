/*
function call: main -> Input -> (Round -> Check -> Remove/Replace) -> Calculate

주의점
1. 같은 원판 내에서 1번째 수와 4번째 수도 인접한 것으로 본다
2. 인접한 수를 지울 때는 DFS를 사용해야 빠뜨리지 않는다
3. x의 배수 원판을 계산하기 위해 인덱스를 1부터 시작했다면 헷갈릴 수 있다
*/
#include <iostream>
#include <vector>
using namespace std;

struct Info {
	int x; // 번호가 x의 배수인 원판을
	int d; // 0:시계 1:반시계 방향으로
	int k; // k칸 회전시킨다
};

int N, M, T; // 원판개수, 숫자개수, 회전횟수
vector<vector<int>> map(51, vector<int>(51, 0)); // 인덱스가 1부터이기때문에 50개 커버하기 위해 51까지
vector<vector<int>> visited(51, vector<int>(51, 0));
vector<vector<int>> emptyVector(51, vector<int>(51, 0));
vector<Info> Infos;

float num; // map의 원소 개수 (num/num => 정수몫만 취해지기에 하나는 float형으로)
int numSum; // map의 원소 합

void Input() {
	cin >> N >> M >> T;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}

	int x, d, k;
	for (int i = 0; i < T; i++) {
		cin >> x >> d >> k;
		Infos.push_back(Info{ x, d, k });
	}
}

void Move(int n, int d) { // ok
	if (d == 0) { // 시계
		int tmp = map[n][M];
		for (int i = M; i >= 1; i--) {
			map[n][i] = map[n][i - 1];
		}
		map[n][1] = tmp;
	}
	else { // 반시계
		int tmp = map[n][1];
		for (int i = 2; i <= M; i++) {
			map[n][i - 1] = map[n][i];
		}
		map[n][M] = tmp;
	}
}

void Round(int x, int d, int k) {
	for (int n = 1; n <= N; n++) {
		// x의 배수인 원판인지 검사
		if (n / x < 1) continue;
		if (n % x != 0) continue;
		
		for (int i = 0; i < k; i++) { // k번 돌린다
			Move(n, d);
		}
	}
}

void Print() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int tmpR, tmpC;

void RemoveDfs(int r, int c, int num) { // 인접한 애들끼리 다 지워야 하므로 DFS (단순 4방향으로 해서 가운데 애를 지워버리면 인접한 애가 포함 안됨)
	map[r][c] = 0;

	for (int t = 0; t < 4; t++) {
		tmpR = r + dir[t][0];
		tmpC = c + dir[t][1];

		if (tmpR < 1 || N + 1 <= tmpR) continue;
		if (tmpC == 0) tmpC = M;					// 같은 원판 내에서는 circular
		if (tmpC == M + 1) tmpC = 1;
		if (visited[tmpR][tmpC] == 1) continue;
		if (num != map[tmpR][tmpC])  continue;

		visited[tmpR][tmpC] = 1;
		RemoveDfs(tmpR, tmpC, num);
	}
}

void Remove() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (map[i][j] == 0) continue;

			bool removed = false;
			for (int t = 0; t < 4; t++) {
				tmpR = i + dir[t][0];
				tmpC = j + dir[t][1];

				if (tmpC == 0) tmpC = M;		// 같은 원판 내에서는 circular
				if (tmpC == M + 1) tmpC = 1;
				if (tmpR < 1 || N + 1 <= tmpR) continue;
				
				if (map[i][j] != map[tmpR][tmpC])  continue;
				//cout << i << "," << j << "(" << map[i][j] << ") ?= " << tmpR << "," << tmpC << "(" << map[tmpR][tmpC] << ")" << endl;
				removed = true;
			}
			if (removed) {
				visited[i][j] = 1;
				RemoveDfs(i, j, map[i][j]);
			}
			
		}
	}
}

void Replace() {
	float numMean = numSum / num;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (map[i][j] == 0) continue;
			if (map[i][j] > numMean) map[i][j]--;
			else if (map[i][j] < numMean) map[i][j]++;
		}
	}
}


bool Check() {
	// Replace에 쓰일 변수 초기화
	num = 0;
	numSum = 0;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (map[i][j] == 0) continue;
			num++;
			numSum += map[i][j];
			
			for (int t = 0; t < 4; t++) {
				tmpR = i + dir[t][0];
				tmpC = j + dir[t][1];

				if (tmpR < 1 || tmpC < 1 || tmpR >= N+1 || tmpC >= M+1) continue;
				if (map[i][j] == map[tmpR][tmpC]) {
					// cout << i << "," << j << " = " << tmpR << "," << tmpC << endl;
					return true;
				}
			}
		}
	}
	return false;
}

int Calculate() {
	int answer = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			answer += map[i][j];
		}
	}
	return answer;
}

int main() {

	Input();

	for (int t = 0; t < T; t++) {
		Info thisInfo = Infos[t];
		Round(thisInfo.x, thisInfo.d, thisInfo.k);
		//Print();
		if (Check()) { // 인접하면서 같은 숫자가 있다
			//cout << "remove" << endl;
			visited = emptyVector; // DFS에 사용할 visited 초기화
			Remove();
		}
		else { // 인접하면서 같은 숫자가 없다
			//cout << "Replace" << endl;
			Replace();
		}
		/*Print();
		cout << Calculate() << endl;*/
	}

	cout << Calculate();

	return 0;
}