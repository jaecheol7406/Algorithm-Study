#define _CRT_SECURE_NO_WARNINGS
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
