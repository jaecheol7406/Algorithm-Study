#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int n,m;
int map[1001][1001];
int max;
int ispossible(int y, int x, int k)
{
	int cnt = 0;
	if (y + k > n || x + k > m) return 0;
	for (int i = y; i < y+k; i++)
	{
		for (int j = x; j < x+k; j++)
		{
			if(map[i][j]==1) cnt++;
		}
	}
	if (cnt == k * k)
	{
	//printf("%d %d %d %d\n", y, x, cnt,k);
		if(max <cnt) max = cnt;
		//printf("%d\n",max);
		return 1;
	}
	return 0;
}

void dfs(int y, int x)
{
	
	if (x == m)
	{
		dfs(y + 1, 0);
		return;
	}
	if (y == n)
	{
		return;
		//최대값 갱신.
	}
	if (map[y][x] == 1)
	{
		int k = (n * m) / 2;
		for (int i = 1; i <= k; i++)
		{
			ispossible(y, x, i);
		}
		dfs(y, x + 1);
		
	}
	else
	{
		dfs(y, x + 1);
	}
	return;
}
int main()
{
	scanf("%d %d",&n,&m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%1d",&map[i][j]);
		}
	}
	dfs(0, 0);
	printf("%d",max);
	return 0;
}
