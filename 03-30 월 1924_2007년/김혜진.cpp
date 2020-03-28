/*
function call: main

x�� y���� ������ ���ϰ� ���� ���,
(x-1) �������� ��(day) �� + y���� ���� ��
�̸� 7�� ���������� �Ͽ� ������ ������ ����Ѵ�
*/
#include <iostream>
#include <string>
using namespace std;

int x, y;
int days[15] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
string name[7] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

int main() {

	scanf("%d %d", &x, &y);
	int sum = 0;
	for (int i = 0; i < x; i++) {
		sum += days[i];
	}
	sum += y;

	cout << name[sum % 7];

	return 0;
}