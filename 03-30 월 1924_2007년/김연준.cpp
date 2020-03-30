/*
BOJ 1924��: 2007��
function call : main()
���� Ǯ�� : 1. 1�� 1�Ϻ��� �Է¹��� ��¥���� ���̸� ���Ѵ�.
			2. 1���� ���� ������ 7�γ��� �������� ����ؼ� ������ ����.
*/

#include <iostream>
#include <string>
using namespace std;
int days[12] = {0, 31,28,31,30,31,30,31,31,30,31,30 };
string day[7] = {"MON","TUE","WED","THU","FRI","SAT","SUN" };
int main() {

	int x, y;
	cin >> x >> y;
	int result = 0;
	for (int i = 0; i <x ; i++) {
		result += days[i];
	}
	result += y;
	cout << day[(result-1) % 7] << endl;

	return 0;
}