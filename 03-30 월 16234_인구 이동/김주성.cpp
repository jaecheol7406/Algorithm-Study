#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <queue>
#include <algorithm>
#include <math.h>
using namespace std;
int n, l, r;
int visit[101][101];
int map[101][101];
int back[101][101];
int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};
int flag = 0;
int result = 0;
int bfs(int y,int x)
{
	
	int cnt = 0;
	queue<pair<int, int>>q;
	q.push(make_pair(y, x));
	visit[y][x] = 1;
	cnt = 1;
	result = back[y][x];
	while (!q.empty())
	{
		int qsize = q.size();
		for (int i = 0; i < qsize; i++)
		{
			int cy = q.front().first;
			int cx = q.front().second;
			printf("%d %d\n",cy,cx);
			
			
			q.pop();
			for (int i = 0; i < 4; i++)
			{
				int ny = cy + dy[i];
				int nx = cx + dx[i];
				int val = abs(back[ny][nx] - back[cy][cx]);
				
				if (val >= l && val <= r &&  ny>= 0 && nx>=0 && ny<n && nx<n && visit[ny][nx]==0)
				{
					
					printf("val %d\n",val);
					result += back[ny][nx];
					cnt++;
					flag = 1;
					q.push(make_pair(ny, nx));
					visit[ny][nx] = 1;
				}
			}
		}
	}
	printf("%d %d\n",result ,cnt);
	result = result / cnt;
	return flag;
}
void backup()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			back[i][j] = map[i][j];
		}
	}
}
void visit_init()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			visit[i][j] = 0;
		}
	}
}
void print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ",map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void calcul()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (visit[i][j] == 1)
			{
				map[i][j] = result;
			}
		}
	}
}
int main()
{
	scanf("%d %d %d",&n,&l,&r);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d",&map[i][j]);
		}
	}
	
	int div = 0;
	int result = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			flag = 0;
			backup();
			if (visit[i][j] == 0)
			{
				if (bfs(i, j) == 1)
				{
					printf("insert \n");
					calcul();
					result++;
					print();
					visit_init();
				}
				
			}
		}
	}
	printf("%d",result);
	return 0;
}
