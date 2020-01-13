#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
using namespace std;

int map[1010];
int correct(int a,int b)
{
	if (a != b)
	{
		return 1;
	}
	else return 0;
}
int main()
{
	int a;
	scanf("%d",&a);
	int sum = 0;
	for (int i = 1; i <= a; i++)
	{
		int cnt = 0;
		int b = 0;
		int v = i;
		while (1)
		{
			if (v == 0) break;
			v = v / 10;
			b = b % 10;
			map[cnt] = b;
			cnt++;
		}
		if (cnt > 2)
		{ 
			for (int i = 0; i < cnt-1; i++)
			{
				if (correct(map[i], map[i] + 1) == 0)
					sum++;
				else break;
				

			}
		}
		else if(cnt<3)
		{
			//printf("%d ", i);
			sum++;
		}
	}
	printf("%d", sum);
	return 0;
}