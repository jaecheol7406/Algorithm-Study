/*
function call: main

x월 y일의 요일을 구하고 싶은 경우,
(x-1) 월까지의 일(day) 수 + y일을 구한 뒤
이를 7로 나머지연산 하여 적절한 요일을 출력한다
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