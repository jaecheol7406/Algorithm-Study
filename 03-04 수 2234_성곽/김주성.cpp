// 함수순서 
// 이중포문후 bfs()를 구해서 1,2번을 구함
// 3중 포문후 bfs를 구해서 3번을 구함.

// 1,2번 방문하지 않으면 bfs로 들어가는데 상하좌우 검사를 비트마스킹을 이용해서 하나씩 쉬프트 시키면서 검사하면서 bfs하였다.
// 3. 비트마스킹으로 상하좌우 다 하나씩 뚫은후 bfs를 돌렸다. 


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<queue>
#include <algorithm>
#include <string.h>
using namespace std;
int n, m;
int map[51][51];
int visit[51][51];
int val[51][51];
int room;
int maxnum;
int deltemax;
int dy[5] = { 0,-1,0,1 };
int dx[5] = { -1,0,1,0 };
void print()
{
	printf("\n");
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ",visit[i][j]);
		}
		printf("\n");
	}
}
void bfs(int y, int x)
{
	queue<pair<int, int>>q;
	q.push(make_pair(y, x));
	int cnt=0;
	cnt++;
	while (!q.empty())
	{
		int cy = q.front().first;
		int cx = q.front().second;
		//printf("cy %d cx %d\n", cy, cx);
		visit[cy][cx] = 1;
		int dir = map[cy][cx];
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			//printf("%d %d\n", dir, (1 << i));
			if ((dir & (1 << i)) ==0)
			{
				int ny = cy + dy[i];
				int nx = cx + dx[i];
				//printf("in %d %d\n", dir, (1 << i));
				
				if (ny < 0 || nx < 0 || ny >= m || nx >= n || visit[ny][nx] == 1) continue;
				cnt++;
				visit[ny][nx] = 1;
				q.push(make_pair(ny, nx));
			}
		}
		
	}
	maxnum < cnt ? maxnum = cnt : maxnum = maxnum;

	//print();
	
}
int main()
{
	scanf("%d %d",&n,&m);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d",&map[i][j]);
		}
	}
	// 1,2번결과를 내기 위한 이중포문
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (visit[i][j] == 1) continue;
			bfs(i, j);
			room++;
		}
	}
	printf("%d\n",room);
	printf("%d\n",maxnum);

	//3번의 결과를 내기 위한 3중 포문
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			
			for (int k = 0; k < 4; k++)
			{
				int dir = map[i][j];
				if ((dir & (1 << k)) == 1)
				{
					memset(visit, 0, sizeof(visit));
					map[i][j] = map[i][j] - (1 << k);
					//printf("%d %d %d\n",i,j,map[i][j]);
					bfs(i, j);
					map[i][j] = map[i][j] + (1 << k);
				}
			}
		}
	}
	printf("%d\n",maxnum);
	return 0;
}
