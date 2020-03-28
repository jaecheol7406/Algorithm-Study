/* function call: main -> Input() -> main
수열을 vector에 넣어두고, X보다 작으면 출력한다.
*/
#include <iostream>
#include <vector>
using namespace std;

int N, X;
vector<int> arr;

void Input() {
	scanf("%d %d\n", &N, &X);
	int tmp;
	for (int i = 0; i < N; i++) {
		scanf("%d ", &tmp);
		arr.push_back(tmp);
	}
}

int main() {

	Input();

	for (int i = 0; i < arr.size(); i++) {
		if(arr[i] < X)
			printf("%d ", arr[i]);
	}

	return 0;
}