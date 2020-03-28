/* function call: main
{
3을 0개 쓰고 나머지를 5로 채우는 경우
3을 1개 쓰고 나머지를 5로 채우는 경우
...
}
각 경우에서 완성이 가능하면 Min과 비교해 최소값을 구한다
*/
#include <iostream>
using namespace std;

int main() {

	int N;
	scanf("%d", &N);

	int three = 0; // 3kg 주머니 개수
	int five = 0; // 5kg 주머니 개수
	int Min = 5000;

	while (3 * three <= N) {
		if ((N - (three * 3)) % 5 == 0) {
			five = (N - (three * 3)) / 5;
			if (Min > (five + three)) Min = (five + three);
		}
		three++;
	}

	if (Min == 5000) cout << -1;
	else cout << Min;

	return 0;
}