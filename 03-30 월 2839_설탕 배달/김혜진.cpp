/* function call: main
{
3�� 0�� ���� �������� 5�� ä��� ���
3�� 1�� ���� �������� 5�� ä��� ���
...
}
�� ��쿡�� �ϼ��� �����ϸ� Min�� ���� �ּҰ��� ���Ѵ�
*/
#include <iostream>
using namespace std;

int main() {

	int N;
	scanf("%d", &N);

	int three = 0; // 3kg �ָӴ� ����
	int five = 0; // 5kg �ָӴ� ����
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