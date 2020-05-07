//5 5 5
//1 1 1 1 1
//1 1 1 1 1
//1 1 1 1 1
//1 1 1 1 1
//1 1 1 1 1
//이예제가 잘이해안감 이예제에선 사정거리가 5이므로 23이나와야 된다는 생각을 가지고있는데 왜 15가 나오는지 모르겠음.
// 펑션콜 순서 main - dfs -move
// 문제이해가 안되서 설계실패
// 조합까지는 잘구했으나. 예제 4번부터 잘안나와서 문제이해의도움을 받아야될것같다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<cstring>
int visit[20];
int map[20][20];
int temp[20];
int n,m,d;
int result[20];
int maxx;
int real;
void print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ",map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void move(int y,int *cur)
{
	if (d > 1)
	{
		for (int i = 0; i < 3; i++)
		{
			//printf("%d번째 뽑음",i);
			//왼쪽 갯수세기
			for (int j = 0; j < d; j++)
			{
				int val = cur[i] - j;
				printf("왼 %d %d %d\n",y, val, map[y][val]);
				if (map[y][val])
				{
					result[val] = 1;
				}
			}

			//오른쪽 갯수세기
			for (int j = 1; j < d+1; j++)
			{
				printf("오 %d %d %d\n", y, cur[i] + j, map[y][cur[i] + j]);
				if (map[y][cur[i]+j])
				{
					result[cur[i] + j] = 1;
				}

			}
			
		}
		printf("\n");
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			//printf("%d %d\n",y,cur[i]);
			if (map[y][cur[i]])
			{
				result[map[y][cur[i]]]=1;
			}
		}
	}
}
void dfs(int cur,int st)
{
	if (cur == 3)
	{
		printf("\n");
		maxx = 0;
		
		for (int i = 0; i < 3; i++)
		{
			printf("%d",temp[i]);
		}
		printf("\n");
		for (int i = 0; i < n; i++)
		{
			
			memset(result, 0, sizeof(result));
			move(i,temp);
			for (int i = 0; i < 20; i++)
			{
				printf("%d ",result[i]);
				if (result[i])
					maxx++;
			}
			printf("\n");
			
		}
		if (maxx > real) real = maxx;
		printf("result %d\n", maxx);
	}

	for (int i = st; i < m; i++)
	{
		if (!visit[i])
		{
			visit[i] = 1;
			temp[cur] = i;
			dfs(cur + 1,i); // 조합시 i값을 넣어라. 
			temp[cur] = 0;
			visit[i] = 0;
		}
	}
}
int main()
{
	scanf("%d %d %d",&n,&m,&d);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d",&map[i][j]);
		}
	}
	print();
	dfs(0,0);
	printf("%d",real);
	return 0;
}
