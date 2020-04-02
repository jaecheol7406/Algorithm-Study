/*
function call: main -> Input main
���͸� ��ȸ�ϸ鼭, (������ ��ġ�� ū ����� ��+1)�� ����Ѵ�
*/
#include <iostream>
#include <vector>
using namespace std;

struct Size {
	int kg;
	int cm;
};

int N;
vector<Size> people;

void Input() {
	scanf("%d\n", &N);
	int kg, cm;
	for (int i = 0; i < N; i++) {
		scanf("%d %d\n", &kg, &cm);
		people.push_back(Size{ kg, cm });
	}
}

int main() {

	Input();

	for (int i = 0; i < N; i++) {
		int rank = 1;
		for (int j = 0; j < N; j++) {
			if (i == j) continue;

			if (people[i].cm < people[j].cm&& people[i].kg < people[j].kg)
				rank++;
		}
		cout << rank << " ";
	}

	return 0;
}