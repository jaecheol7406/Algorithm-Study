/*
단순 구현,
vector 사용시 시간초과 / queue 사용시 통과
*/
#include <iostream>
#include <queue>
using namespace std;

int N;
queue<int> card;

int main() {

	scanf("%d", &N);

	bool copyErase = false;

	for (int i = 1; i <= N; i++) {
		card.push(i);
	}

	while (card.size() != 1) {
			
		if (!copyErase) {
			// cout << card.front() << " 그냥 지우기" << endl;
			card.pop();
		}
		else {
			// cout << card.front() << " 복사하고 지우기" << endl;
			card.push(card.front());
			card.pop();
		}
		copyErase = !copyErase;
		
	}
	cout << card.front();

	return 0;
}