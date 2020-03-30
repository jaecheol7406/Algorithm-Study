/*
BOJ 1924번: 2007년
function call : main()
문제 풀이 : 1. 1월 1일부터 입력받은 날짜와의 차이를 구한다.
			2. 1에서 구한 값에서 7로나눈 나머지를 사용해서 요일을 구함.
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