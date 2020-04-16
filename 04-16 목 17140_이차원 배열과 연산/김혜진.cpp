/*
function call: main -> Input -> (DoR <-> DoC ) -> main

unordered_map을 활용해 풀이
정렬을 위해서는 map을 vector로 변환
*/
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;

int r, c, k;
int map[110][110];
unordered_map<int, int> num; // 숫자, 등장횟수
int maxR = 3;
int maxC = 3;

void Input() {
	scanf("%d %d %d\n", &r, &c, &k);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			scanf("%d ", &map[i][j]);
		}
	}
}

void Print() {
	for (int i = 0; i < maxR; i++) {
		for (int j = 0; j < maxC; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

void Init() {
	num.clear();
}

bool cmp(pair<int, int> A, pair<int, int> B) {
	if (A.second == B.second) return A.first < B.first;
	return A.second < B.second;
}

void DoR() {
	for (int i = 0; i < maxR; i++) {
		Init();

		// map 만들기
		for (int j = 0; j < maxC; j++) {
			if (map[i][j] != 0) {
				if (num.count(map[i][j])) {
					num.find(map[i][j])->second++;
				}
				else {
					num.insert(make_pair(map[i][j], 1));
				}
			}
		}

		// map 출력
		/*cout << i << "번째 행의 map" << endl;
		for (auto it = num.begin(); it != num.end(); it++) {
			cout << it->first << it->second << endl;
		}*/

		// vector로 바꾸어 정렬
		vector<pair<int, int>> tmpVec;
		for (auto it = num.begin(); it != num.end(); it++) {
			tmpVec.push_back(make_pair(it->first, it->second));
			sort(tmpVec.begin(), tmpVec.end(), cmp);
		}

		// vector 출력
		/*cout << "벡터===" << endl;
		for (int j = 0; j < tmpVec.size(); j++) {
			cout << tmpVec[j].first << tmpVec[j].second << endl;
		}*/

		// maxC 갱신
		if (tmpVec.size() * 2 > maxC) maxC = tmpVec.size() * 2;

		// map 비우기
		for (int j = 0; j < maxC; j++) {
			map[i][j] = 0;
		}

		// map 채우기
		for (int j = 0; j < tmpVec.size()*2; j += 2) {
			map[i][j] = tmpVec[j/2].first;
			map[i][j + 1] = tmpVec[j/2].second;
		}
	}
}

void DoC() {
	for (int j = 0; j < maxC; j++) {
		Init();

		// map 만들기
		for (int i = 0; i < maxR; i++) {
			if (map[i][j] != 0) {
				if (num.count(map[i][j])) {
					num.find(map[i][j])->second++;
				}
				else {
					num.insert(make_pair(map[i][j], 1));
				}
			}
			
		}

		// map 출력
		/*cout << j << "번째 열의 map" << endl;
		for (auto it = num.begin(); it != num.end(); it++) {
			cout << it->first << it->second << endl;
		}*/

		// vector로 바꾸어 정렬
		vector<pair<int, int>> tmpVec;
		for (auto it = num.begin(); it != num.end(); it++) {
			tmpVec.push_back(make_pair(it->first, it->second));
			sort(tmpVec.begin(), tmpVec.end(), cmp);
		}

		// vector 출력
		/*cout << "벡터===" << endl;
		for (int i = 0; i < tmpVec.size(); i++) {
			cout << tmpVec[i].first << tmpVec[i].second << endl;
		}*/

		// maxR 갱신
		if (tmpVec.size() * 2 > maxR) maxR = tmpVec.size() * 2;

		// map 비우기
		for (int i = 0; i < maxR; i++) {
			map[i][j] = 0;
		}

		// map 채우기
		for (int i = 0; i < tmpVec.size() * 2; i += 2) {
			map[i][j] = tmpVec[i / 2].first;
			map[i + 1][j] = tmpVec[i / 2].second;
		}
	}
}

int main() {

	Input();
	// Print();

	int time = 0;

	while (1) {
		if (map[r-1][c-1] == k) {
			cout << time;
			break;
		}

		time++;
		if (time > 100) {
			cout << -1;
			break;
		}

		if (maxR >= maxC) {
			DoR();
		}
		else {
			DoC();
		}

		
	}
	
	/*cout << endl;
	Print();*/

	return 0;
}