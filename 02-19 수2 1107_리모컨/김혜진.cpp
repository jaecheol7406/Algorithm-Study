/*
5457
3
6 7 8
��: 6

100
5
0 1 2 3 4
��: 0

500000
8
0 2 3 4 6 7 8 9
��: 11117*/
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;
int N;
int Nlen;
int n;
int nums[15]; // 0 ~ 9���� �� ��밡���ϸ� 0, �Ұ����ϸ� 1

int cands[10][2]; // ��: ������ �ڸ���. 0��: �׺��� �������� �ִ�. 1��: �׺��� ū���� �ּڰ�
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
	// cout << "Ÿ�� �ѹ�: " << N <<  "(����" << Nlen << ")" << endl; // 2^Nlen ���� ����� ��
	for (int i = 0; i < Nlen; i++) {
		cout << npart[i];
	}
	cout << endl;
	cout << "��� ������ ����: ";
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
	cout << "����: " << tmp << endl;
	// (!!) �� ���ڷ� ���� �ּڰ� ���ϱ� (100���� +- �� ���� �ְ� <-> ���ڸ� �� ������ �� ���� �ְ�)

	int min = Nlen + abs(N - tmp);
	if (MIN > min) {
		MIN = min;
	}
	cout << "MIN: " << MIN << " �̹� min: " << min << endl;
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
	for (int i = 0; i < Nlen; i++) { // Nlen�� �ڸ����� ���� �̱�
		// �������� �ִ�
		for (int j = npart[i]; j >= 0; j--) {
			if (nums[j] == 0) {
				cands[i][0] = j;
				break;
			}
		}

		// ū ���� �ּڰ�
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
			cout << cands[i][j] << " "; // i��° �ڸ������� ������ ���� ����
		}
		cout << endl;
	}

	Permutation(0);

	// 1010 �̷������� ���� ���ؼ�, 1�̸� �׺��� ū �ּڰ��̰� 0�̸� �׺��� ���� �ִ��� �ɷ�.
	cout << MIN;

	return 0;
}