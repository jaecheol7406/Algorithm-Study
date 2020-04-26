//m일때만 따로 처리해주고 조건대로 
// cnt가 0일때 리턴하여 불필요한 연산을 줄여줌.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstring>
using namespace std;
int n, m, t;
int map[60][60];
int tempmap[60][60];
int check[60][60];
int x, d, k;
int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };
int result;
void right(int *a)
{
	//printf("\n");
	int temp = *(a + m - 1);
	//printf("temp %d\n",temp);
	//printf("%d\n",temp);
	for(int i = m - 1; i >= 1; i--)
	{
		*(a + i) = *(a + i - 1);
		//printf("%d ", *(a + i));
	}
	*(a) = temp;


	for (int i = 0; i < m; i++)
	{
		//printf("%d ", *(a + i));
	}
	//printf("%d", *a);
	//printf("\n");
}
void left(int *a)
{
	//printf("\n");
	int temp = *a;
	for (int i = 0; i < m-1; i++)
	{
		*(a+i) = *(a+i+1);
		//printf("%d ", *(a + i));
	}
	*(a + m - 1) = temp;

	for (int i = 0; i < m; i++)
	{
		//printf("%d ", *(a + i));
	}

	//printf("\n");
}
void checktoremove()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (check[i][j] == 1)
			{
				map[i][j] = 0;
			}
		}
	}
}
int remove()
{
	int flag = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (tempmap[i][j] != 0)
			{
				if (j == m)
				{
					if (tempmap[i][1] == tempmap[i][m])
					{
						//printf("%d %d\n",ny,1);
						//printf("%d %d\n", ny, m);
						flag = 1;
						map[i][1] = 0;
						map[i][m] = 0;
					}
					if (tempmap[i][m - 1] == tempmap[i][m])
					{
						flag = 1;
						map[i][m-1] = 0;
						map[i][m] = 0;
					}
					if (tempmap[i][m] == tempmap[i+1][m])
					{
						flag = 1;
						map[i][m] = 0;
						map[i+1][m] = 0;
					}
					if (tempmap[i][m] == tempmap[i-1][m])
					{
						flag = 1;
						map[i][m] = 0;
						map[i-1][m] = 0;
					}
				}
				else
				{
					for (int q = 0; q < 4; q++)
					{
						int ny = i + dy[q];
						int nx = j + dx[q];
						if (ny <= 0 || nx <= 0 || ny > n || nx > m || tempmap[ny][nx] == 0) continue;
						if (tempmap[ny][nx] == tempmap[i][j])
						{
							flag = 1;
							map[i][j] = 0;
							map[ny][nx] = 0;
						}

					}
				}
				
				
			}
			
		}
		
	}
	
	//printf("flag 값 %d\n",flag);
	return flag;
}
void print()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			printf("%d ",map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void calcul()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (map[i][j] != 0)
			{
				result+=map[i][j];
			}
		}
	}
}
void remove2()
{
	double total=0;
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (map[i][j] != 0)
			{
				total += map[i][j];
				cnt++;
			}
		}
	}
	if (cnt == 0) return;
	total = double(total /cnt);
	//printf("total %d\n", total);
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (map[i][j] != 0)
				{
					if (map[i][j] > total)
					{
						map[i][j] -= 1;
					}
					else if (map[i][j] < total)
					{
						map[i][j] += 1;
					}
				}
			}
		}
	
}
void dfs(int c,int x,int d,int k)
{
	
	if (c > n)
	{
		return;
	}
	//printf("x %d\n",c);
	//print();
	for (int i = 0; i < k; i++)
	{
		//printf("%d번째\n", x);
		if (d == 0)
		{
			int *temp = &map[c][1];
			right(temp);
		}
		else
		{
			int *temp = &map[c][1];
			left(temp);
		}
		
	}
	dfs(c + x,x,d,k);
	return;
}
int main()
{
	scanf("%d %d %d",&n,&m,&t);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d",&map[i][j]);
		}
	}
	for (int i = 0; i < t; i++)
	{
		//memset(tempmap, 0, sizeof(map));
		scanf("%d %d %d",&x,&d,&k);
		
		dfs(x,x,d,k);
		//print();
		memcpy(tempmap, map, sizeof(map));
		memset(check, 0, sizeof(check));
		if (remove() == 0)
		{
			remove2();
		}
		//print();
	}
	
	//print();
	calcul();

	printf("%d\n",result);
	return 0;
}
