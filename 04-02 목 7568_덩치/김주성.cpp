#define _CRT_SECURE_NO_WARNINGS
//2중포문으로 tall값과 weight값 둘다 크다면 cnt를 증가하여 나보다 큰덩치를 구할수있다.
#include <stdio.h>
using namespace std;
int n;
int tall[51];
int weight[51];
int main()
{
	scanf("%d",&n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d",&tall[i],&weight[i]);
	}
	
	for (int i = 0; i < n; i++)
	{
		int cnt = 1;
		for (int j = 0; j < n; j++)
		{
			if (i == j) continue;
			if (tall[i] < tall[j] && weight[i] < weight[j])
			{
				cnt++;
			}
		}
		printf("%d ",cnt);
	}
	return 0;
}
