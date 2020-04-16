// dfs함수에서 현재 day와 현재day에갈수있는데이를 넣고 브루투포스했음. p는 현재까지의 이익임
// 가지치기 가능 만약에 브루투포스할때 n이 7일이라면 현재까지의 day가 7이하만 브루투포스 하면됨으로 가지치기가 가능하지만 나중에 해봄
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int n;
int day[20];
int power[20];
int check[20];
int max = 0;
void dfs(int d,int p)
{
	if (d >= n+1)
	{
		//printf("%d\n",p);
		int sum=0;
		for (int i = 1; i <= n; i++)
		{
			if (check[i] == 1)
			{
					sum = i + day[i];
			}
		}
		//printf("\n%d \n",sum);
		if (sum <= n+1)
		{
			/*for (int i = 1; i <= n; i++)
			{
				printf("%d ",check[i]);
			}*/

			//printf("%d\n",p);
			if (max < p) max = p;
			return;
		}
		else
		{
			return;
		}


		/*for (int i = 1; i <= n; i++)
		{
			printf("%d ",check[i]);
		}
		printf("\n");*/
		
	}
	
	check[d]=1;
	dfs(d + day[d], p+power[d]);
	check[d] = 0;
	//p = p-power[d];
	dfs(d + 1, p);

}

int main()
{
	scanf("%d",&n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d",&day[i],&power[i]);
	}

	dfs(1, 0);
	printf("%d",max);
	return 0;
}
