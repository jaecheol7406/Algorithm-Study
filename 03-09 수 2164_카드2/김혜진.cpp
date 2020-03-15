/*
�ܼ� ����,
vector ���� �ð��ʰ� / queue ���� ���
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
			// cout << card.front() << " �׳� �����" << endl;
			card.pop();
		}
		else {
			// cout << card.front() << " �����ϰ� �����" << endl;
			card.push(card.front());
			card.pop();
		}
		copyErase = !copyErase;
		
	}
	cout << card.front();

	return 0;
}