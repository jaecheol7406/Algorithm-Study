/*
function call: main -> Input main
벡터를 순회하면서, (나보다 덩치가 큰 사람의 수+1)을 출력한다
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