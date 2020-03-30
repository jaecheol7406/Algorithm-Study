// 1.달마다 일수를 계산한다. 
// 2. 요일의 순서를 저장한다.
// 3. 달의 일수를 더하고 일의 일수를 더한후 요일의 갯수를 나눠준후 출력
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <string.h>
using namespace std;
int day[15] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
//string yoil[7] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
char yoil[7][4] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
int main()
{
	int x, y;
	scanf("%d %d",&x,&y);
	int sum = 0;
	for (int i = 0; i < x; i++)
	{
		sum += day[i];
	}
	sum += y;
	sum = sum % 7;
	printf("%s\n",yoil[sum]);
	return 0;
}
