#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>
using namespace std;

struct Pos {
	int r;
	int c;
	int len = 0;
};

int N;
int map[15][15];


vector<Pos> ppl; // 사람들의 위치
vector<Pos> str; // 계단 위치 및 길이 정보

vector<int> dist1; // 계단1까지 남은 거리
vector<int> dist2;
vector<int> str1; // 계단1을 내려가는 사람의 남은 계단 수
vector<int> str2;
vector<int> trash; // 계단을 다 내려가서 지워야 하는 인덱스

int t; // 초과한 시간
int finish; // finish가 사람들 수와 일치해야 종료
int MIN = 99999999;

void Init() {
	for (int i = 0; i < N; i++) {
		memset(map[i], 0, 15);
	}
	ppl.clear();
	str.clear();
	dist1.clear();
	dist2.clear();
	str1.clear();
	str2.clear();

	t = 0;
	finish = 0;
	MIN = 99999999;
}

void Input() {
	Init();

	scanf("%d\n", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d ", &map[i][j]);
			Pos pos;
			pos.r = i; pos.c = j;
			if (map[i][j] == 1) {
				ppl.push_back(pos);
			}
			else if(map[i][j] != 0) {
				pos.len = map[i][j];
				str.push_back(pos);
			}
		}
	}
}

void Print() {
	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", map[i][j]);
			
		}
		printf("\n");
	}*/
	cout << "사람 수: " << ppl.size();
	cout << " 계단 길이: ";
	for (int i = 0; i < str.size(); i++) {
		cout << str[i].len << " ";
	}
	cout << endl;
}

void Go() {
	

	while (t > -1) {
		t++; // 1초 경과
		if (MIN < t) return;
		// cout << endl << t << "초 =======" << endl;

		// cout << "   계단1 내려가기 ====" << endl;
		// 계단을 내려가는 사람 계산
		for (int i = 0; i < str1.size(); i++) { // 계단 1을 내려가는 사람

			if (str1[i] == 0) {
				finish++; // 계단 다 내려감
				// cout << str1[i] << ": " << "계단 다 내려감" << endl;
				trash.push_back(i);
			}
			else if (str1[i] > 0) {
				str1[i]--;
				// cout << str1[i] << ": 계단 1칸 내려감" << endl;
			}
		}
		for (int i = trash.size()-1; i >=0 ; i--) {
			str1.erase(str1.begin() + trash[i]);
		}
		trash.clear();
		// cout << "   계단2 내려가기 ====" << endl;
		for (int i = 0; i < str2.size(); i++) { // 계단 2를 내려가는 사람

			if (str2[i] == 0) {
				finish++; // 계단 다 내려감
				// cout << str2[i] << ": " << "계단 다 내려감" << endl;
				trash.push_back(i);
			}
			else if (str2[i] > 0) {
				str2[i]--;
				// cout << str2[i] << ": 계단 1칸 내려감" << endl;
			}
		}
		for (int i = trash.size() - 1; i >= 0; i--) {
			str2.erase(str2.begin() + trash[i]);
		}
		trash.clear();

		if (finish == ppl.size()) { // 완료 조건
			break;
		}

		// cout << "   계단1로 향하기 ==" << endl;
		for (int i = 0; i < dist1.size(); i++) {
			if (dist1[i] == 1) { // 계단 입구에 도착하면
				// cout << "계단 진입" << endl;
				if (str1.size() < 3) { // 계단에 진입할 수 있으면
					str1.push_back(str[0].len);
					dist1[i] = -1;
				}
				else {
					dist1[i]--;
				}
			}
			else if (dist1[i] == 0) { // 예전에 도착했는데 진입을 못하던 애
				if (str1.size() < 3) {
					str1.push_back(str[0].len - 1);
					dist1[i]--;
				}
			}
			else if(dist1[i] > 1){
				dist1[i]--;
				// cout << dist1[i] << "남음" << endl;
			}
		}
		// cout << "   계단2로 향하기 ==" << endl;
		for (int i = 0; i < dist2.size(); i++) {
			if (dist2[i] == 1) { // 계단 입구에 도착하면
				// cout << "계단 진입" << endl;
				if (str2.size() < 3) { // 계단에 진입할 수 있으면
					str2.push_back(str[1].len);
					dist2[i] = -1;
				}
				else {
					dist2[i]--;
				}
			}
			else if (dist2[i] == 0) {
				if (str2.size() < 3) {
					str2.push_back(str[1].len - 1);
					dist2[i]--;
				}
			}
			else if (dist2[i] > 1) {
				dist2[i]--;
				// cout << dist2[i] << "남음" << endl;
			}
		}


	}
	
	if (MIN > t) {
		MIN = t;
	}
	// cout << "MIN: " << MIN << " t: " << t << endl;
}

int selected[15];
void Select(int cnt) {
	if (cnt >= ppl.size()) { // 종료 조건
		dist1.clear();
		dist2.clear();
		str1.clear();
		str2.clear();
		t = 0;
		finish = 0;

		for (int i = 0; i < ppl.size(); i++) { // 계단과 그 사람 간의 남은 거리 계산
			if (selected[i] == 1) {
				int distance = abs(ppl[i].r - str[0].r) + abs(ppl[i].c - str[0].c);
				dist1.push_back(distance);
			}
			else {
				int distance = abs(ppl[i].r - str[1].r) + abs(ppl[i].c - str[1].c);
				dist2.push_back(distance);
			}
		}
		/*cout << "뽑힌 경우: ";
		for (int i = 0; i < ppl.size(); i++) {
			cout << selected[i] << " ";
		}
		cout << endl;

		cout << "케이스 시작 ==============" << endl;
		cout << "dist1 남은거리: ";
		for (int i = 0; i < dist1.size(); i++) {
			cout << dist1[i] << " ";
		}
		cout << endl;
		cout << "dist2 남은거리: ";
		for (int i = 0; i < dist2.size(); i++) {
			cout << dist2[i] << " ";
		}
		cout << endl;*/
		
		Go();

		return;
	}

	for (int i = 1; i < 3; i++) {
		selected[cnt] = i;

		Select(cnt + 1);
	}

}

int main() {
	int T;
	scanf("%d\n", &T);

	for (int t_case = 1; t_case <= T; t_case++) {
		cout << "#" << t_case;

		Input();

		Select(0); // dist1, dist2 벡터를 완성시킨다.

		cout << " " << MIN << endl;
	}

	return 0;
 }