//n/2만큼 브루투포스 한다음에 1인경우 스타트팀 0인경우 링크팀으로 나눈후 i,j를 번갈아가면서 계산하면된다. 여기서 포문을 10 과 01을 같다고 보지않았기
// 때문에 오래걸렸고, min값의 갱신타이밍을 이상한곳에 두어서 생각보다 오래걸렸다.

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
using namespace std;
int n;
int map[25][25];
int check[25];
int start[25];
int link[25];
int min = 987654321;
void dfs(int i,int t)
{
	if (i > n) return;
	if (t >= n/2)
	{
		int differ = 0;
		int a = 0;
		int b = 0;
		for (int i = 0; i < n; i++)
		{
			//printf("%d ",check[i]);

			if (check[i] == 1)
			{
				start[a++] = i;
			}
			else
			{
				link[b++] = i;
			}
		}
		/*printf("\n");
		for (int i = 0; i < a; i++)
		{
			printf("%d ",start[i]);
		}
		printf("\n");*/
		//printf("\n");
		int resulta = 0;
		int resultb = 0;
		for (int i = 0; i <a; i++)
		{
			for (int j = i+1; j < a; j++)
			{
				if (i == j) continue;
				//printf("%d %d\n", start[i], start[j]);
				//printf("%d %d\n\n", link[i], link[j]);
				resulta += map[start[i]][start[j]] + map[start[j]][start[i]];
				resultb += map[link[i]][link[j]] + map[link[j]][link[i]];
				
			}
		}
		if (min > abs(resulta - resultb)) min = abs(resulta - resultb);
		//printf("\n");
		return;
	}

	check[i] = 1;
	dfs(i + 1,t+1);

	check[i] = 0;
	dfs(i + 1,t);
}

int main()
{
	scanf("%d",&n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d",&map[i][j]);
		}
	}

	dfs(0,0);
	printf("%d",min);
	return 0;
}
