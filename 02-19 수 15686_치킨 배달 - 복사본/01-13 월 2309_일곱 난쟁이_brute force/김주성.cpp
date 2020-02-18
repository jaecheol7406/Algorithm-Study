#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int map[10];
int check[10];
int lastmap[10];
int flag = 0;
int dfs(int d ,int sum,int cnt)
{
	if (d == 9 || sum<0)
	{
		//printf("%d",cnt);
		if (sum == 0 && cnt==7)
		{
			int a=0;
			for (int i = 0; i < 9; i++)
			{
				if (check[i] == 1)
				{
					lastmap[a] = map[i];
					//printf("%d\n", map[i]);
					a++;
				}
			}

			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					if (i == j) continue;
					if (lastmap[i] < lastmap[j])
					{
						int temp = lastmap[j];
						lastmap[j] = lastmap[i];
						lastmap[i] = temp;
					}
				}
			}
			flag = 1;
			

			return 0;
		}
		return 0;
	}
	check[d] = 0;
	dfs(d + 1, sum,cnt);
	check[d] = 1;
	dfs(d + 1, sum - map[d],cnt+1);
	return 0;
}
int main()
{
	for (int i = 0; i < 9; i++)
	{
		scanf("%d", &map[i]);
	}
	//printf("\n");
	dfs(0,100,0);
	if (flag == 1)
	{
		for (int i = 0; i < 7; i++)
		{
			printf("%d\n", lastmap[i]);

		}
	}
	return 0;
}