// 변수를 계속 바꾸어서 맞는지 확인했다. 주의해야할것은 줄이 바뀌면 맨 마지막 값이 처음값이 되어야 함으로 플래그로 확인해줌
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int n, m;
char map[51][51];
char visit[51][51];
int result = 987654321;
void print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d",map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void reset(int y,int x)
{
	for (int i = y+0; i < y+8; i++)
	{
		for (int j = x+0; j < x+8; j++)
		{
			visit[i][j] = 0;
		}
	}
}
void check(int y,int x)
{
	//print();
	int invcnt = 0;
	int start = 0;
	int boo = 1;
	int temp = 0;
	int flag = 0;
	for (int i = 0 + y; i < 8 + y; i++)
	{
		for (int j = 0 + x; j < 8 + x; j++)
		{
				start = boo + start;
				boo = boo*-1;
				if (flag == 1)
				{
					start = temp;
					boo *= -1;
					flag = 0;
				}
				//printf("%d ", start);
				//printf("%d ",start);
				if (map[i][j] != start)
				{
					invcnt++;
				}
				temp = start;
		}
		//printf("\n");
		flag = 1;
	}
	if (result > invcnt) result =invcnt;
	int invcnt2 = 0;
	int start2 = 1;
	int boo2 = 1;
	int temp2 = 0;
	int flag2 = 0;
	//printf("s2 ");
	for (int i = 0 + y; i < 8 + y; i++)
	{
		for (int j = 0 + x; j < 8 + x; j++)
		{
				boo2 *= -1;
				//printf("%d ",boo2);
				start2 = boo2 +start2;
				if (flag2 == 1)
				{
					start2 = temp2;
					boo2 *= -1;
					flag2= 0;
				}
				//printf("%d ",start2);
				//printf("%d %d\n",map[i][j], start2);
				if (map[i][j] != start2)
				{
					//printf("++%d %d\n",i,j);
					invcnt2++;
				}
				temp2 = start2;
		}
		flag2 = 1;
		//printf("\n");
		
	}
	//printf("%d",invcnt2);
	if (result > invcnt2) result = invcnt2;
	//for (int i = 0 + y; i < 8 + y; i++)
	//{
	//	for (int j = 0 + x; j < 8 + x; j++)
	//	{
	//		visit[i][j] = 1;
	//	}
	//}
}
int main()
{
	scanf("%d %d",&n,&m);
	for (int i = 0; i < n; i++)
	{
			scanf("%s",&map[i]);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == 'W') map[i][j] = 0;
			else map[i][j] = 1;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (visit[i][j] == 0 && i+7 <n && j+7<m)
			{
				//reset(i, j);
				visit[i][j] = 1;
				check(i, j);
				//printf("call\n");
			}
		}
	}
	printf("%d",result);
	return 0;
}
