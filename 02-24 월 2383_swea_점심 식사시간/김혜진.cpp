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


vector<Pos> ppl; // ������� ��ġ
vector<Pos> str; // ��� ��ġ �� ���� ����

vector<int> dist1; // ���1���� ���� �Ÿ�
vector<int> dist2;
vector<int> str1; // ���1�� �������� ����� ���� ��� ��
vector<int> str2;
vector<int> trash; // ����� �� �������� ������ �ϴ� �ε���

int t; // �ʰ��� �ð�
int finish; // finish�� ����� ���� ��ġ�ؾ� ����
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
	cout << "��� ��: " << ppl.size();
	cout << " ��� ����: ";
	for (int i = 0; i < str.size(); i++) {
		cout << str[i].len << " ";
	}
	cout << endl;
}

void Go() {
	

	while (t > -1) {
		t++; // 1�� ���
		if (MIN < t) return;
		// cout << endl << t << "�� =======" << endl;

		// cout << "   ���1 �������� ====" << endl;
		// ����� �������� ��� ���
		for (int i = 0; i < str1.size(); i++) { // ��� 1�� �������� ���

			if (str1[i] == 0) {
				finish++; // ��� �� ������
				// cout << str1[i] << ": " << "��� �� ������" << endl;
				trash.push_back(i);
			}
			else if (str1[i] > 0) {
				str1[i]--;
				// cout << str1[i] << ": ��� 1ĭ ������" << endl;
			}
		}
		for (int i = trash.size()-1; i >=0 ; i--) {
			str1.erase(str1.begin() + trash[i]);
		}
		trash.clear();
		// cout << "   ���2 �������� ====" << endl;
		for (int i = 0; i < str2.size(); i++) { // ��� 2�� �������� ���

			if (str2[i] == 0) {
				finish++; // ��� �� ������
				// cout << str2[i] << ": " << "��� �� ������" << endl;
				trash.push_back(i);
			}
			else if (str2[i] > 0) {
				str2[i]--;
				// cout << str2[i] << ": ��� 1ĭ ������" << endl;
			}
		}
		for (int i = trash.size() - 1; i >= 0; i--) {
			str2.erase(str2.begin() + trash[i]);
		}
		trash.clear();

		if (finish == ppl.size()) { // �Ϸ� ����
			break;
		}

		// cout << "   ���1�� ���ϱ� ==" << endl;
		for (int i = 0; i < dist1.size(); i++) {
			if (dist1[i] == 1) { // ��� �Ա��� �����ϸ�
				// cout << "��� ����" << endl;
				if (str1.size() < 3) { // ��ܿ� ������ �� ������
					str1.push_back(str[0].len);
					dist1[i] = -1;
				}
				else {
					dist1[i]--;
				}
			}
			else if (dist1[i] == 0) { // ������ �����ߴµ� ������ ���ϴ� ��
				if (str1.size() < 3) {
					str1.push_back(str[0].len - 1);
					dist1[i]--;
				}
			}
			else if(dist1[i] > 1){
				dist1[i]--;
				// cout << dist1[i] << "����" << endl;
			}
		}
		// cout << "   ���2�� ���ϱ� ==" << endl;
		for (int i = 0; i < dist2.size(); i++) {
			if (dist2[i] == 1) { // ��� �Ա��� �����ϸ�
				// cout << "��� ����" << endl;
				if (str2.size() < 3) { // ��ܿ� ������ �� ������
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
				// cout << dist2[i] << "����" << endl;
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
	if (cnt >= ppl.size()) { // ���� ����
		dist1.clear();
		dist2.clear();
		str1.clear();
		str2.clear();
		t = 0;
		finish = 0;

		for (int i = 0; i < ppl.size(); i++) { // ��ܰ� �� ��� ���� ���� �Ÿ� ���
			if (selected[i] == 1) {
				int distance = abs(ppl[i].r - str[0].r) + abs(ppl[i].c - str[0].c);
				dist1.push_back(distance);
			}
			else {
				int distance = abs(ppl[i].r - str[1].r) + abs(ppl[i].c - str[1].c);
				dist2.push_back(distance);
			}
		}
		/*cout << "���� ���: ";
		for (int i = 0; i < ppl.size(); i++) {
			cout << selected[i] << " ";
		}
		cout << endl;

		cout << "���̽� ���� ==============" << endl;
		cout << "dist1 �����Ÿ�: ";
		for (int i = 0; i < dist1.size(); i++) {
			cout << dist1[i] << " ";
		}
		cout << endl;
		cout << "dist2 �����Ÿ�: ";
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

		Select(0); // dist1, dist2 ���͸� �ϼ���Ų��.

		cout << " " << MIN << endl;
	}

	return 0;
 }