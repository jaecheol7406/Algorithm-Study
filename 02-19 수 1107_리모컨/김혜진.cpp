/*
5457
3
6 7 8
답: 6

100
5
0 1 2 3 4
답: 0

500000
8
0 2 3 4 6 7 8 9
답: 11117*/
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;
int N;
int Nlen;
int n;
int nums[15]; // 0 ~ 9까지 중 사용가능하면 0, 불가능하면 1

int cands[10][2]; // 행: 숫자의 자리수. 0열: 그보다 작은수중 최댓값. 1열: 그보다 큰수중 최솟값
vector<int> npart;
int selected[10];

int MIN = 99999999;

void Input() {
	scanf("%d\n", &N);
	Nlen = to_string(N).length();
	string nstring = to_string(N);
	
	int backup = N;
	for (int i = 0; i < Nlen; i++) {
		npart.push_back(backup % 10);
		backup /= 10;
	}

	scanf("%d\n", &n);
	int tmp;

	for (int i = 0; i < n; i++) {
		scanf("%d ", &tmp);
		nums[tmp] = 1;
	}
}

void Print() {
	// cout << "타겟 넘버: " << N <<  "(길이" << Nlen << ")" << endl; // 2^Nlen 개의 경우의 수
	for (int i = 0; i < Nlen; i++) {
		cout << npart[i];
	}
	cout << endl;
	cout << "사용 가능한 숫자: ";
	for (int i = 0; i < 10; i++) {
		// if (nums[i] == 0) continue;
		cout << nums[i] << " ";
	}
	cout << endl;
}

void GetNumber() {
	int tmp = 0;
	int bojeong = 1;
	for (int i = Nlen - 1; i >= 0; i--) {
		// cout << cands[i][selected[i]];
		tmp += bojeong * cands[i][selected[i]];
		bojeong *= 10;
	}
	cout << "숫자: " << tmp << endl;
	// (!!) 이 숫자로 가는 최솟값 구하기 (100에서 +- 할 수도 있고 <-> 숫자를 다 눌러서 갈 수도 있고)

	int min = Nlen + abs(N - tmp);
	if (MIN > min) {
		MIN = min;
	}
	cout << "MIN: " << MIN << " 이번 min: " << min << endl;
}


void Permutation(int cnt) {
	if (cnt >= Nlen) {
		/*for (int i = 0; i < Nlen; i++) {
			cout << cands[i][selected[i]];
		}
		cout << endl;*/
		
		GetNumber();
		return;
	}

	for (int i = 0; i < 2; i++) {
		selected[cnt] = i;
		Permutation(cnt + 1);
	}
}

void PickCands() {
	for (int i = 0; i < Nlen; i++) { // Nlen개 자릿수에 대해 뽑기
		// 작은수중 최댓값
		for (int j = npart[i]; j >= 0; j--) {
			if (nums[j] == 0) {
				cands[i][0] = j;
				break;
			}
		}

		// 큰 수중 최솟값
		for (int j = npart[i]; j < 10; j++) {
			if (nums[j] == 0) {
				cands[i][1] = j;
				break;
			}
		}
			
	}
}

int main() {
	Input();
	// Print();

	PickCands();
	for (int i = 0; i < Nlen; i++) {
		for (int j = 0; j < 2; j++) {
			cout << cands[i][j] << " "; // i번째 자리수에서 가능한 숫자 조합
		}
		cout << endl;
	}

	Permutation(0);

	// 1010 이런식으로 순열 구해서, 1이면 그보다 큰 최솟값이고 0이면 그보다 작은 최댓값인 걸로.
	cout << MIN;

	return 0;
}