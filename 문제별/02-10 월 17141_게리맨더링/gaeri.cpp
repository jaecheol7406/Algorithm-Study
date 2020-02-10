#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <algorithm>
int n;
int map[11];
int visit[11];
int connect[11][11];
int a[11];
int b[11];
int min = 987654321;
int iscona(int cnta)
{
	//printf("%d\n", cnta);
	if (cnta == 0 || cnta == 6) return 0;
	//printf("%d\n",cnta);
	int flag = 0;
	for (int i = 1; i <= cnta; i++)
	{
		int aval = a[i];
		for (int j = i+1; j <= cnta; j++)
		{
			int avalj = a[j];
			if (connect[aval][avalj] != 1) flag = 1;
		}
	}
	if (flag == 0) return 1;
	return 0;
}
int isconb(int cntb)
{
	//printf("%d\n", cntb);
	if (cntb == 0 || cntb == 6) return 0;
	//printf("%d\n", cntb);
	int flag = 0;
	for (int i = 1; i <= cntb; i++)
	{
		int aval = b[i];
		for (int j = i + 1; j <= cntb; j++)
		{
			int avalj = b[j];
			if (connect[aval][avalj] != 1) flag = 1;
		}
	}
	if (flag == 0) return 1;
	return 0;
}
int calculation()
{
	int a=0,b=0;
	for (int i = 1; i <= n; i++)
	{
		if (visit[i] == 1) a += map[i];
		else b += map[i];
	}
	int summ = abs(a - b);
	return summ;
}
int dfs(int cur)
{
	if (cur >= 1)
	{
		int cnta=1,cntb = 1;
		for (int i = 1; i <= n; i++)
		{
			if (visit[i] == 1) a[cnta++] = i;
			else b[cntb++] = i;
		}
		/*for (int i = 1; i < cnta; i++)
		{
			printf("%d",a[i]);
		}
		printf("\n");
		for (int i = 1; i < cntb; i++)
		{
			printf("%d", b[i]);
		}
		printf("\n");*/

		if (iscona(cnta-1))
		{
			int submin=calculation();
			if (min > submin) min = submin;

			//printf("hi");
		}
		//for (int i = 1; i <= n; i++)
		//{
		//	printf("%d",visit[i]);
		//}
		//printf("\n");
	}

	for (int i = 1; i <= n; i++)
	{
		if (visit[i] == 0)
		{
			if (a[cur+1] > i) continue;
			visit[i] = 1;
			a[cur+1]=i;
			dfs(cur+1);
			visit[i] = 0;
		}
	}
	return 0;
}

int main()
{
	scanf("%d",&n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d",&map[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		int num=0;
		scanf("%d",&num);
		for (int j = 0; j < num; j++)
		{
			int nearcon = 0;
			scanf("%d", &nearcon);
			connect[i][nearcon] = 1;
			connect[nearcon][i] = 1;
		}
	}
	dfs(0);
	//DFS(1, 0);
	printf("%d",min);
	return 0;
}
