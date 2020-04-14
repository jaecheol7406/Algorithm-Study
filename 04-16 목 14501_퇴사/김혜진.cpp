/*
function call: main -> Input -> DFS -> main

���Ʈ������ ������ ��� ��¥�� ������ ����, price�� ���Ѵ�.
    - ��¥�� �ϳ� �� �Ŀ���, (�� ��¥ + �ɸ��� �Ⱓ)° �� ��¥���� ��� �����ϴ�.
	  (��: �����Է�1���� 1��° ���(3��¥��)�� ����, (1+3)=4��° ��� ���ĺ��� �� �� �ִ�.)
    - �� (�������� �� ��� ���۳�¥ + �ɸ��� �Ⱓ) <= N+1 �� �͸� �� �� �ִ� ���̴�.
*/
#include <iostream>
#include <vector>
using namespace std;

struct Cns {
	int t;
	int p;
};

int N;
Cns cns[20];
int maxPrice = 0;
vector<int> picked;

void Input() {
	scanf("%d\n", &N);

	int t, p;
	for (int i = 1; i <= N; i++) {
		scanf("%d %d\n", &t, &p);
		cns[i] = Cns{ t, p };
	}
}

void DFS(int pre) {

	for (int i = pre; i <= N; i++) {
		if (i + cns[i].t <= N+1) {
			picked.push_back(i);
			DFS(i + cns[i].t);
			picked.pop_back();
		}
	}

	// pre == N+1 �Ǵ� ���̻� push�� ���� ���� DFSȣ�� ���� ��
	/*cout << "completed: ";
	for (int i = 0; i < picked.size(); i++) {
		cout << picked[i] << " ";
	}
	cout << endl;*/
	int sumValue = 0;
	for (int i = 0; i < picked.size(); i++) {
		sumValue += cns[picked[i]].p;
	}
	if (sumValue > maxPrice) maxPrice = sumValue;
	return;
}

int main() {
	Input();

	DFS(1);

	cout << maxPrice;

	return 0;
}